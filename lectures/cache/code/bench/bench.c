#include <stdio.h>
#include "uart.h"
#include "timer.h"
#include "system.h"
#include "armtimer.h"
#include "measure.h"

extern void ARMTEST0 ( unsigned int );
extern void ARMTEST1 ( unsigned int );
extern void ARMTEST2 ( unsigned int );
extern void ARMTEST3 ( unsigned int );
extern void ARMTEST4 ( unsigned int );
extern void ARMTEST5 ( unsigned int );

void measure_time(void (*f)(unsigned int), unsigned int n)
{
    unsigned beg = armtimer_get_time();
    (*f)(n);
    unsigned elapsed = (armtimer_get_time() - beg)/250;
    // armtimer runs at the system core clock frequency = 250 Mhz

    printf("elapsed time = %d usecs\n", elapsed);
}

void measure( void (*f)(unsigned int), unsigned int n)
{
    //measure_time(f, n);
    measure_instructions(f, n);
    measure_branch(f, n);
}

void measureall(void)
{
    printf("ARMTEST0: estimated instructions %d\n", 0x02000000);
    measure(&ARMTEST0, 0x01000000);
    printf("ARMTEST1: estimated instructions %d\n", 0x01200000);
    measure(&ARMTEST1, 0x01000000);
    printf("ARMTEST2: estimated instructions %d\n", 0x01100000);
    measure(&ARMTEST2, 0x01000000);
}

void main ( void )
{
    timer_init();
    armtimer_init();
    uart_init();

    delay(1);

    printf("no cache\n");
    measureall();

    printf("cache\n");
    system_enable_cache();
    measureall();
}
