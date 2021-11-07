#include "armtimer.h"
#include "console.h"
#include "gpio.h"
#include "gpio_extra.h"
#include "interrupts.h"
#include "keyboard.h"
#include "printf.h"
#include "uart.h"
#include "gpio_interrupts.h"
#include "timer.h"

#define BUTTON GPIO_PIN21

static volatile int elapsed, last_button, last_scan, nbutton, nscan;

static void button_click(unsigned int pc, void *aux_data)
{
    if (gpio_check_and_clear_event(BUTTON)) {
        last_button = elapsed;
        nbutton++;
    }
}

static void second_elapsed(unsigned int pc, void *aux_data)
{
    if (armtimer_check_and_clear_interrupt()) {
        elapsed++;
    }
}

static void clock_edge(unsigned int pc, void *aux_data)
{
    static int nClock; // internally count clock edges, 11 = one scan code

    if (gpio_check_and_clear_event(KEYBOARD_CLOCK)) {
        nClock++;
        if (nClock % 11 == 0) {
            last_scan = elapsed;
            nscan++;
        }
    }
}

void configure_button(void)
{
    gpio_set_input(BUTTON);
    gpio_set_pullup(BUTTON);
    gpio_enable_event_detection(BUTTON, GPIO_DETECT_FALLING_EDGE);
    gpio_interrupts_register_handler(BUTTON, button_click, NULL);
}

void configure_alarm(void)
{
    // armtimer is intialized to number of usecs between events
    armtimer_init(1000000);
    armtimer_enable();             // enable timer itself
    armtimer_enable_interrupts();  // receive timer events as interrupts
    interrupts_register_handler(INTERRUPTS_BASIC_ARM_TIMER_IRQ, second_elapsed, NULL);
    interrupts_enable_source(INTERRUPTS_BASIC_ARM_TIMER_IRQ);
}

void configure_keyboard(void)
{
    keyboard_init(KEYBOARD_CLOCK, KEYBOARD_DATA);
    gpio_enable_event_detection(KEYBOARD_CLOCK, GPIO_DETECT_FALLING_EDGE);
    gpio_interrupts_register_handler(KEYBOARD_CLOCK, clock_edge, NULL);
}

void main(void)
{
    interrupts_init();
    gpio_init();
    gpio_interrupts_init();
    uart_init();
    console_init(12, 20, GL_AMBER, GL_INDIGO);

    configure_button();
    configure_alarm();
    configure_keyboard();

	gpio_interrupts_enable();
    interrupts_global_enable();

    while (1) {
        console_clear();
        console_printf("\n  Time now %02d:%02d\n\n"
                       "\n scancode count %d"
                       "\n   last @ %02d:%02d\n"
                       "\n button count %d"
                       "\n   last @ %02d:%02d",
                        elapsed/60, elapsed % 60,
                        nscan, last_scan/60, last_scan % 60,
                        nbutton, last_button/60, last_button % 60);
        timer_delay_ms(500);
    }
}
