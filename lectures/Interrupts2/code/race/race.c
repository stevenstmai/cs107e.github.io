#include "timer.h"
#include "gpio.h"
#include "uart.h"
#include "armtimer.h"
#include "interrupts.h"
#include "printf.h"

static volatile unsigned int a = 0;
static volatile unsigned int b = 0;
static volatile int numViolations = 0;

void timer_event_race(unsigned int pc, void *unused) {
    static unsigned int n_timer_interrupts = 0;
    armtimer_check_and_clear_interrupt();
    n_timer_interrupts++;
    a++;
    b++;
    if (a != b) { // values expected same, when would they not be?
        numViolations++;
        printf("VIOLATION (after %3d interrupts): a=%d,b=%d, pc = 0x%x\n", n_timer_interrupts, a, b, pc);
        timer_delay(3);
        a = b; // re-synch
    }
}

void main(void) {
    timer_init();
    gpio_init();
    uart_init();
    interrupts_init();
    armtimer_init(20000);
    armtimer_enable();
    armtimer_enable_interrupts();
    interrupts_register_handler(INTERRUPTS_BASIC_ARM_TIMER_IRQ, timer_event_race, NULL);
    interrupts_enable_source(INTERRUPTS_BASIC_ARM_TIMER_IRQ);
    interrupts_global_enable();

    while (numViolations < 5) {
        // interrupts_global_disable();
        a++;
        b++;
        // interrupts_global_enable();
    }
    uart_putchar(EOT);
}
