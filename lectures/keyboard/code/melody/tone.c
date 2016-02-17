#include "pwm.h"
#include "tone.h"

void tone( int freq )
{
    if( freq == 0 ) {
        // Disable PWM
        pwm_set_mode( PWM_CH0, !PWM_ENABLE, PWM_USE_MARKSPACE, !PWM_USE_FIFO );
        pwm_set_mode( PWM_CH1, !PWM_ENABLE, PWM_USE_MARKSPACE, !PWM_USE_FIFO );
        return;
    }
    // Enable PWM
    pwm_set_mode( PWM_CH0, PWM_ENABLE, PWM_USE_MARKSPACE, !PWM_USE_FIFO );
    pwm_set_mode( PWM_CH1, PWM_ENABLE, PWM_USE_MARKSPACE, !PWM_USE_FIFO );

    int divisor = F_AUDIO / freq;
    int divisor2 = divisor/2;

    pwm_set_range( PWM_CH0,  divisor );
    pwm_set_width( PWM_CH0,  divisor2 );

    pwm_set_range( PWM_CH1,  divisor );
    pwm_set_width( PWM_CH1,  divisor2 );

}
