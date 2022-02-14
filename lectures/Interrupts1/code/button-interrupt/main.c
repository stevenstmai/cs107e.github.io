#include "console.h"
#include "echo.h"
#include "gpio.h"
#include "gpio_extra.h"
#include "gpio_interrupts.h"

#define BUTTON_GPIO GPIO_PIN21
#define NROWS 16
#define NCOLS 40
#define REPEAT ((NCOLS/4)*(NROWS/2))
#define DKGRAY 0xff222222

static volatile int gCount = 0;


static void update_screen()
{
    console_clear();
    console_printf("\nCount of button presses\n");
    for (int r = 0; r < REPEAT; r++) {
        console_printf("%3d ", gCount);
    }
}

static void button_pressed(unsigned int pc, void *aux_data)
{
    if (gpio_check_and_clear_event(BUTTON_GPIO)) {
        gCount++;
    }
}

void main(void)
{
    gpio_init();
    gpio_set_input(BUTTON_GPIO);
    gpio_enable_event_detection(BUTTON_GPIO, GPIO_DETECT_FALLING_EDGE);

    interrupts_init();
    gpio_interrupts_init();
    gpio_interrupts_register_handler(BUTTON_GPIO, button_pressed, NULL);
    gpio_interrupts_enable();
    interrupts_global_enable();

    console_init(NROWS, NCOLS, GL_AMBER, DKGRAY);
    console_printf("\n\nWaiting for button click...\n");

    int last_count = gCount;
    while (1) {
        if (last_count != gCount) {
            update_screen();
            last_count = gCount;
            console_printf("\n\nWaiting for button click...\n");
       }
    }
}
