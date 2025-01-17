#include "gpio.h"
#include "pwm.h"

#define FREQ (19200000/16) // clock is 19.2MHz, and this divider gives us
                              // a pretty good range for musical notes
#define LEFT_HZ 220 
#define RIGHT_HZ 440 

void main ( void )
{
    gpio_init();
    gpio_set_function( 40, GPIO_FUNC_ALT0 ); // Stereo left
    gpio_set_function( 45, GPIO_FUNC_ALT0 ); // Stereo right

    pwm_init();
    pwm_set_clock( FREQ ); // 9,600,000

    pwm_set_mode( 0, PWM_MARKSPACE);
    pwm_set_fifo( 0, 0 );
    pwm_enable( 0 );

    pwm_set_mode( 1, PWM_MARKSPACE);
    pwm_set_fifo( 1, 0 );
    pwm_enable( 1 );

    int left_width = FREQ/LEFT_HZ; // 1.2M / 440 = 2727
    pwm_set_range( 0, left_width ); // 2727 
    pwm_set_width( 0, left_width/2 );  // 681

    int right_width = FREQ/RIGHT_HZ; // 1.2M / 523 = 2294
    pwm_set_range( 1, right_width ); 
    pwm_set_width( 1, right_width/2 );

    while(1) ;
}

