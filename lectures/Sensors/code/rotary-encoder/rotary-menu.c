/*
 * Rotary Encoder -- interrupt based
 */

#include "timer.h"
#include "gpio.h"
#include "gpio_extra.h"
#include "uart.h"
#include "printf.h"
#include "gpio_interrupts.h"

const unsigned int CLOCK = GPIO_PIN16;
const unsigned int DT = GPIO_PIN20;
const unsigned int SW = GPIO_PIN21;
volatile int rotary_status = 0; // 0 == none, -1 == ccw, 1 == cw
volatile int rotary_button = 1; // 0 = pushed, 1 = not pushed

static void encoder_rotated(unsigned int pc, void *aux_data)
{
    if (gpio_check_and_clear_event(CLOCK)) {
        static int last_clock = 1;
        int clock_val = gpio_read(CLOCK);
        if (clock_val != last_clock) {
            last_clock = clock_val;
            if (gpio_read(DT) == clock_val) {
                // printf("counterclockwise\n");
                rotary_status = -1;         
            } else {
                // printf("clockwise\n");
                rotary_status = 1;         
            }
        }
    }
    if (gpio_check_and_clear_event(SW)) {
       rotary_button = gpio_read(SW); 
    }
}

void main(void) {
    timer_init();
    gpio_init();
    uart_init();

  	gpio_set_input(CLOCK);
  	gpio_set_input(DT);
  	gpio_set_input(SW);
  	gpio_set_pullup(CLOCK);
  	gpio_set_pullup(DT);
  	gpio_set_pullup(SW);
    gpio_enable_event_detection(CLOCK, GPIO_DETECT_FALLING_EDGE);
    gpio_enable_event_detection(CLOCK, GPIO_DETECT_RISING_EDGE);
    gpio_enable_event_detection(SW, GPIO_DETECT_FALLING_EDGE);
    gpio_enable_event_detection(SW, GPIO_DETECT_RISING_EDGE);

    interrupts_init();
    interrupts_register_handler(INTERRUPTS_GPIO3, encoder_rotated, NULL);
    // interrupts_register_handler(INTERRUPTS_GPIO3, encoder_button, NULL);
    interrupts_global_enable();
    int last_button = rotary_button;
    while (1) {
        if (rotary_status != 0) {
            printf("%s\n", rotary_status == -1 ? "ccw" : "clockwise");
            rotary_status = 0;
        }
        if (rotary_button != last_button) {
            if (rotary_button) {
                printf("button up\n");
            } else {
                printf("button down\n");
            }
            last_button = rotary_button;
        }
    }
}
