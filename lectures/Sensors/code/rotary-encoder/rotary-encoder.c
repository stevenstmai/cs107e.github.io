/*
 * Rotary Encoder -- interrupt based
 */

#include "timer.h"
#include "gpio.h"
#include "gpio_extra.h"
#include "uart.h"
#include "printf.h"
#include "gpio_interrupts.h"

#define RED "[39;41m"
#define NORMAL "[39;49m"
#define CURSOR_UP "[1A"
#define CURSOR_DOWN "[1B"
#define CLEAR_LINE "[2K"
#define CLEAR_SCREEN "[2J[1;1H"

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

void rotary_report()
{
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

void up_down()
{
    printf("use the rotary encoder to scroll up or down. Press the button for the main menu.\n");
    timer_delay_ms(200); // for button press
    while (1) {
        // need a bit of debouncing here
        if (!rotary_button) {
            rotary_button = 1;
            timer_delay_ms(200); // button press
            return;
        }
        if (rotary_status == 1) {
            printf("%s", CURSOR_DOWN);
            rotary_status = 0;
        } else if (rotary_status == -1) {
            printf("%s", CURSOR_UP);
            rotary_status = 0;
        }
    }
}

void circle()
{
    printf("use the rotary encoder to go around the circle\n");
}

struct menu {
    char *description;
    void (*fn)();
    int selected;
};


struct menu main_menu[] = {
    {"rotary report", rotary_report, 1},
    {"up and down", up_down, 0},
    {"circle", circle, 0},
};

void (*get_menu_choice(struct menu *m, int num_choices))() {
    int selected_idx = 0;
    for (int i = 0; i < num_choices; i++) {
        if (m[i].selected) {
            selected_idx = i;
            break;
        }
    }
    printf("%s*** Please Choose ***\n", CLEAR_SCREEN);
    while (1) {
        for (int i = 0; i < num_choices; i++) {
            if (i == selected_idx) {
                printf("%s", RED);
            }
            printf(" %s", m[i].description);
            if (i == selected_idx) {
                printf("%s", NORMAL);
            }
            printf("\n");
        }
        while (1) {
            if (rotary_status != 0) {
                if (rotary_status == 1) {
                    selected_idx = (selected_idx + 1) % num_choices;
                } else {
                    selected_idx -= 1;
                    if (selected_idx == -1) {
                        selected_idx = num_choices - 1;
                    }
                }
                for (int i = 0; i < num_choices; i++) {
                    printf("%s%s", CURSOR_UP, CLEAR_LINE); 
                }
                rotary_status = 0;
                break;
            }
            if (!rotary_button) {
                rotary_button = 1;
                printf("%s", CLEAR_SCREEN);
                return m[selected_idx].fn;
            }
        }
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
    interrupts_global_enable();
    interrupts_enable_source(INTERRUPTS_GPIO3);
    while (1) {
        (get_menu_choice(main_menu, sizeof(main_menu) / sizeof(struct menu)))();
    }
}
