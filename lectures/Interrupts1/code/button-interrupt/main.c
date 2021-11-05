#include "console.h"
#include "echo.h"
#include "gpio.h"
#include "gpio_extra.h"
#include "gpio_interrupts.h"
#include "keyboard.h"

#define BUTTON_GPIO GPIO_PIN21
#define NROWS 16
#define NCOLS 32
#define REPEAT ((NCOLS/4)*(NROWS/2))

static volatile int gCount = 0;

static void button_pressed(unsigned int pc, void *aux_data)
{
    if (gpio_check_and_clear_event(BUTTON_GPIO)) {
        gCount++;
    }
}

static void update_screen()
{
    console_clear();
    console_printf("\nCount of button presses\n");
    for (int r = 0; r < REPEAT; r++) {
        console_printf("%4d", gCount);
    }
    console_printf("\n\nWaiting for button click...\n");
}

void main(void)
{
    gpio_init();
    gpio_set_input(BUTTON_GPIO);
    gpio_enable_event_detection(BUTTON_GPIO, GPIO_DETECT_FALLING_EDGE);

    interrupts_init();
    interrupts_register_handler(INTERRUPTS_GPIO3, button_pressed, NULL);
    interrupts_global_enable();

    console_init(NROWS, NCOLS, GL_AMBER, GL_BLACK);
    console_printf("\n\nWaiting for button click...\n");

    int last_count = gCount;
    while (1) {
        if (last_count != gCount) {
            update_screen();
            last_count = gCount;
        }
    }
}
