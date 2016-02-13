#include "bcm.h"
#include "memory.h"
#include "timer.h"
#include "gpio.h"
#include "pwm.h"

#define BM_PASSWORD 0x5A000000

#define CM_PWMCTL 0x201010A0
#define CM_PWMDIV 0x201010A4

#define CM_ENABLE  (1 << 4)
#define CM_FLIP    (1 << 6)
#define CM_BUSY    (1 << 7)
#define CM_MASH0   (0 << 9)
#define CM_MASH1   (1 << 9)
#define CM_MASH2   (2 << 9)
#define CM_MASH3   (3 << 9)

#define PWM_CTL    0x2020C000
#define PWM_STATUS 0x2020C004
#define PWM_DMAC   0x2020C008
#define PWM_FIFO   0x2020C018

#define PWM_FULL1 0x01

#define PWM0_RANGE 0x2020C010
#define PWM0_DATA  0x2020C014

#define PWM1_RANGE 0x2020C020
#define PWM1_DATA  0x2020C024

#define PWM0_ENABLE      0x0001
#define PWM0_SERIAL      0x0002
#define PWM0_REPEATFF    0x0004
#define PWM0_OFFSTATE    0x0008
#define PWM0_REVPOLARITY 0x0010
#define PWM0_USEFIFO     0x0020
#define PWM0_MARKSPACE   0x0080

#define PWM1_ENABLE      0x0100
#define PWM1_SERIAL      0x0200
#define PWM1_REPEATFF    0x0400
#define PWM1_OFFSTATE    0x0800
#define PWM1_REVPOLARITY 0x1000
#define PWM1_USEFIFO     0x2000
#define PWM1_MARKSPACE   0x8000

void pwm_clock( int freq )
{
    int timer = F_OSC; // 19.2 MHz
    int source = 1;

    int divisor  = timer / freq;
    int fraction = (timer % freq) * 4096 / freq;

    if( divisor < 2 )
        divisor = 2;
    if( divisor > 4095 )
        divisor = 4095;

    if( fraction > 4095 )
        fraction = 4095;

    // turn off pwm before changing the clock
    int pwm = GET32( PWM_CTL );
    PUT32( PWM_CTL, 0 );

    PUT32( CM_PWMCTL, BM_PASSWORD ) ;        // turn off clock
    while ( GET32( CM_PWMCTL ) & CM_BUSY ) ; // Wait for clock to stop

    PUT32( CM_PWMDIV, BM_PASSWORD | (divisor << 12) | fraction );

    int mash = fraction ? CM_MASH1 : CM_MASH0;

    PUT32( CM_PWMCTL, BM_PASSWORD | CM_ENABLE | mash | source );

    PUT32( PWM_CTL, pwm );
}


void pwm_set_mode( int chan, int enable, int markspace, int usefifo)
{
    int ra = GET32( PWM_CTL );

    if( chan == 0 ) {
        if( enable )
            ra |=  PWM0_ENABLE;
        else
            ra &= ~PWM0_ENABLE;

        if( markspace )
            ra |=  PWM0_MARKSPACE;
        else
            ra &= ~PWM0_MARKSPACE;

        if( usefifo )
            ra |=  PWM0_USEFIFO;
        else
            ra &= ~PWM0_USEFIFO;
    }

    if( chan == 1 ) {
        if( enable )
            ra |=  PWM1_ENABLE;
        else
            ra &= ~PWM1_ENABLE;

        if( markspace )
            ra |=  PWM1_MARKSPACE;
        else
            ra &= ~PWM1_MARKSPACE;

        if( usefifo )
            ra |=  PWM1_USEFIFO;
        else
            ra &= ~PWM1_USEFIFO;
    }

    PUT32( PWM_CTL, ra );
}

void pwm_set_range( int chan, int range )
{
    if( chan == PWM_CH0 )
        PUT32( PWM0_RANGE, range );
    if( chan == PWM_CH1 )
        PUT32( PWM1_RANGE, range );
}

void pwm_set_width( int chan, int width )
{
    if( chan == PWM_CH0 )
        PUT32( PWM0_DATA, width );
    if( chan == PWM_CH1 )
        PUT32( PWM1_DATA, width );
}

int pwm_get_status()
{
    return GET32( PWM_STATUS );
}

void pwm_write( int value )
{
    return PUT32( PWM_FIFO, value );
}
