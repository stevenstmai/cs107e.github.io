/* Stack-sampling profiler.
   Can't release publicly since it's a mashup of backtrace and gprof.

   Author: Omar Rizwan <osnr@stanford.edu>

   Date: June 1, 2017
*/

#include "backtrace.h"
#include "malloc.h"
#include "timer.h"
#include "armtimer.h"
#include "assert.h"
#include "gpio_interrupts.h"
#include "printf.h"
#include "stackprof.h"

void stackprof_handler(unsigned pc, void *aux);

static unsigned start_time;

static struct sample *samples;
static int sample_num;

static int max_samples;

void stackprof_init(unsigned interval_us, int max_samp) {
    start_time = timer_get_ticks();

    max_samples = max_samp;

    armtimer_init(interval_us);

    interrupts_init();
    armtimer_enable();
    interrupts_global_enable();
    interrupts_enable_source(INTERRUPTS_BASIC_ARM_TIMER_IRQ);
    armtimer_init(interval_us);
    armtimer_enable();             // enable timer itself
    armtimer_enable_interrupts();  // receive timer events as interrupts
    interrupts_register_handler(INTERRUPTS_BASIC_ARM_TIMER_IRQ, stackprof_handler, NULL);
}

void stackprof_on() {
    if (samples != 0) free(samples);
    samples = malloc(sizeof(struct sample) * max_samples);
    assert(samples != 0);

    sample_num = 0;

    armtimer_enable_interrupts();
}

void stackprof_off() {
    armtimer_disable_interrupts();
}

// Backtrace interface isn't useful while in interrupt context...
// so have to pull this out.
#define MAGIC_MASK 0xff000000

static void print_trace(frame_t f[], int n) {
    for (int i = 0; i < n; i++) {
        uintptr_t magic = f[i].resume_addr - f[i].resume_offset - 4;     // addr of word preceding function
        unsigned int magic_val = *(unsigned int *)magic;
        char *name = "???";
        if ((magic_val & MAGIC_MASK) == MAGIC_MASK) { // if function name present, has 0xff in upper byte of word
            int name_len = magic_val & ~MAGIC_MASK;
            name = (char *)magic - name_len;
        }

        // Guess module name from what's before the _.
        // Useful to colorize charts.
        char filename[50] = "unknown";
        int j;
        for (j = 0; name[j] != '\0' && name[j] != '_'; j++) {
            filename[j] = name[j];
        }
        if (j > 0) filename[j] = '\0';

        // Linux perf-like stack frame.
        printf("    %x %s %s:0 ([unknown])\n",
               f[i].resume_addr, name, filename);
    }
    printf("\n");
}

static void print_sample(struct sample *sample) {
    double timestamp = (double) sample->time / 1000000; // in s.
    unsigned timestamp_whole = (unsigned) timestamp;
    unsigned timestamp_decimal = (unsigned) (timestamp * 1000000) % 1000000;
    printf("main 0 %d.%06d: cpu-clock:u:\n", timestamp_whole, timestamp_decimal);
    print_trace(sample->frames, sample->num_frames);
}

void stackprof_dump() {
    // Emit Linux perf-style output -- can be parsed by external visualizer
    // (flame chart, flame graph, etc).
    for (int i = 0; i < sample_num; i++) {
        print_sample(&samples[i]);
    }
    timer_delay(2);

    printf("%c", 4); // EOT
    while(1) {}
}

struct apcs {
    uintptr_t fp;   // not to base of caller frame, to top!
    uintptr_t ip;   // this field not used
    uintptr_t lr;
    uintptr_t pc;
};

void stackprof_handler(unsigned pc, void *aux) {
    if (armtimer_check_and_clear_interrupt()) {

        struct sample *sample = &samples[sample_num++];
        // Die when we reach the sampling limit.
        assert(sample_num < max_samples);

        sample->time = timer_get_ticks() - start_time;

        uintptr_t *cur_fp;
        __asm__("mov %0, fp" : "=r" (cur_fp));
        struct apcs *prev = (struct apcs *)(cur_fp - 4);
        // printf("%p\n%x\n%x\n%x\n%x\n\n", cur_fp, prev->fp, prev->ip, prev->lr, prev->pc);

        // Save anomalous 'current frame'. May not be strictly correct.
        // Close enough.
        uintptr_t fn_first = prev->pc - 12;
        sample->frames[0].resume_addr = pc;
        sample->frames[0].resume_offset = pc - fn_first;

        // Ripped off from backtrace.c.
        int i;
        for (i = 1; i < 10 && prev->fp != 0; i++) {
            struct apcs *cur = (struct apcs *)(prev->fp - 12); // caller's frame
            uintptr_t fn_first = cur->pc - 12;
            sample->frames[i].resume_addr = prev->lr;      // addr of return insn
            sample->frames[i].resume_offset = prev->lr - fn_first;
            prev = cur; // frame advance
        }
        sample->num_frames = i;
    }
}
