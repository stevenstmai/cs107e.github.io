/* File main.c
 * -----------
 * Simple main program with timing code to measure
 * performance of different implementations of strcpy.
 */

#include <stdio.h>
#include <memory.h>
#include <timer.h>

// string of this length will be copied during time trial
#define COPYLEN (1 << 12)

char src[COPYLEN], dst[COPYLEN];


size_t strlen(const char *str)
{
    const char *cur = str;
    while (*cur) cur++;
    return cur - str;
}

char *strcpy1(char *dst, const char *src)
{
    for (int i = 0; i <= strlen(src); i++) {
        dst[i] = src[i];
    }
    return dst;
}


unsigned tickcount(void)
{
    return GET32(0x20003004); // read cur value of systimer
}


#define TIME_TRIAL(fn) do {         \
  printf("Running " #fn "... ");    \
  unsigned start = tickcount();     \
  fn(dst, src);                     \
  printf("took %d ticks\n", tickcount() - start);  \
} while (0)


int main()
{
     // initialize source string
    for (int i = 0; i < COPYLEN-1; i++) src[i] = 'X';  
    src[COPYLEN-1] = '\0';

    delay(3);   // wait for uart/screen to catch up
    printf("Ready to start time trials!\n");

    TIME_TRIAL(strcpy1);

    printf("Done.\n");
    return 0;
}