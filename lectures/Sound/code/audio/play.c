#include "gpio.h"
#include "pwm.h"
#include "audio.h"
#include "printf.h"
#include "timer.h"
// #include "sin8.h"
// #include "sound2.h"
#include "sound3.h"

void main ()
{
    gpio_init();
    pwm_init();
    audio_init(sample_freq);

    while (1) {
        printf("starting play\n");
        if (bits_per_sample == 8) {
            audio_write_u8((uint8_t *)wav_data, sizeof(wav_data), repeat);
        } else {
            audio_write_i16((int16_t *)wav_data, sizeof(wav_data), repeat);
        }
        printf("done playing\n");
        timer_delay_ms(1000);
    }
}
