#include "printf.h"
#include "fb.h"
#include "assert.h"
#include "system.h"
#include "timer.h"

#define _WIDTH 640
#define _HEIGHT 512
#define _DEPTH 4

struct pixel {
    unsigned char b, g, r, alpha;
};
typedef struct pixel pixel_t;

static pixel_t *fb;

// #1: Basic gl_clear code
static void draw_pixel(unsigned char v, int x, int y) {
    pixel_t (*fb_s)[fb_get_width()] = (pixel_t (*)[fb_get_width()])fb;
    pixel_t *p = &fb_s[y][x];
    p->r = v;
    p->g = v;
    p->b = v;
    p->alpha = 0xff;
}

void write_screen_decomposed(unsigned char v) {
    for (unsigned i = 0; i < fb_get_height(); i++) {
        for (unsigned j = 0; j < fb_get_width(); j++) {
            draw_pixel(v, j, i);
        }
    }
}

























// #2: Writes v to the R, G, and B of each pixel in framebuffer.
void write_screen(unsigned char v) {
    for (volatile unsigned i = 0; i < fb_get_width() * fb_get_height(); i++) {
        pixel_t *p = &fb[i];
        p->r = p->g = p->b = v;
        p->alpha = 0xff;
    }
}

























// #3: Pre-computing the number of bytes to write
void write_screen_precomp(unsigned char v) {
    unsigned n = fb_get_width() * fb_get_height();
    for (volatile unsigned i = 0; i < n; i++) {
        pixel_t *p = &fb[i];
        p->r = p->g = p->b = v;
        p->alpha = 0xff;
    }
}

























// #4: Remove unnecessary volatile
void write_screen_precomp_novolatile(unsigned char v) {
    unsigned n = fb_get_width() * fb_get_height();
    for (unsigned i = 0; i < n; i++) {
        pixel_t *p = &fb[i];
        p->r = p->g = p->b = v;
        p->alpha = 0xff;
    }
}










































// #5: Writing in 4 bytes at a time instead of 1
void write_screen_unsigned(unsigned char v) {
    unsigned n = fb_get_width() * fb_get_height();

    pixel_t p;
    p.r = p.g = p.b = v;
    p.alpha = 0xff;

    unsigned u = *(unsigned *) &p;

    for (unsigned i = 0; i < n; i++) {
        ((unsigned *) fb)[i] = u;
    }
}

























// #6/8: Writing in 8 bytes instead of 4!
void write_screen_ll(unsigned char v) {
    unsigned n = fb_get_width() * fb_get_height();

    pixel_t p;
    p.r = p.g = p.b = v;
    p.alpha = 0xff;

    unsigned long long u = *(unsigned *) &p;
    unsigned long long uu = (u << 32) | u;

    // Since each pixel is 4 bytes, we're writing in
    // two pixels at a time, which means we can loop
    // n/2 times instead of n times
    for (unsigned i = 0; i < n/2; i++) {
        ((unsigned long long *) fb)[i] = uu;
    }
}

























// #7/9: Unrolling the for-loop
void write_screen_ll_unroll(unsigned char v) {
    unsigned n = fb_get_width() * fb_get_height();

    pixel_t p;
    p.r = p.g = p.b = v;
    p.alpha = 0xff;

    unsigned long long u = *(unsigned *) &p;
    unsigned long long uu = (u << 32) | u;

    for (unsigned i = 0; i < n/2; i += 8) {
        unsigned long long *fbll = (unsigned long long *) &fb[i];
        fbll[0] = uu;
        fbll[1] = uu;
        fbll[2] = uu;
        fbll[3] = uu;
        fbll[4] = uu;
        fbll[5] = uu;
        fbll[6] = uu;
        fbll[7] = uu;
    }
}

























// #10: ASSEMBLY
void assign8(void *dst, unsigned u, unsigned n);

void write_screen_asm(unsigned char v) {
    unsigned n = fb_get_width() * fb_get_height();

    pixel_t p;
    p.r = p.g = p.b = v;
    p.alpha = 0xff;

    unsigned u = *(unsigned *) &p;

    assign8(fb, u, n / 8);
}


























#define TIME(cmd, val, iter) do {                       \
        printf("----------\n");                         \
        printf("running: " #cmd "\n");                  \
        int i;                                          \
        for (i = 0; i < iter; i++) {                    \
            unsigned start = timer_get_ticks();          \
            cmd(val);                                   \
            unsigned total = timer_get_ticks() - start;  \
            printf("took %d ticks\n", total);           \
        }                                               \
    } while (0)

void main() {
    //printf_init();
    timer_init();

    fb_init(_WIDTH, _HEIGHT, _DEPTH, 0);
    fb = (struct pixel *) fb_get_draw_buffer();

    TIME(write_screen_decomposed, 0xff, 4);
    TIME(write_screen, 0xff, 4);
    TIME(write_screen_precomp, 0xff, 4);
    TIME(write_screen_precomp_novolatile, 0xff, 4);
    TIME(write_screen_precomp_novolatile_bracket, 0xff, 4);
    TIME(write_screen_unsigned, 0xff, 4);
    TIME(write_screen_ll, 0xff, 4);
    TIME(write_screen_ll_unroll, 0xff, 4);

    system_enable_cache();
    printf("caching.....\n------\n");

    TIME(write_screen_ll, 0xff, 4);
    TIME(write_screen_ll_unroll, 0xff, 4);
    TIME(write_screen_asm, 0xff, 4);

    printf("%c", 4); // Send EOT to signal done.
}
