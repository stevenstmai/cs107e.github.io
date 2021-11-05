#include "console.h"
#include "echo.h"
#include "gpio.h"
#include "gpio_extra.h"

#define BUTTON_GPIO GPIO_PIN21
#define NROWS 16
#define NCOLS 32
#define REPEAT ((NCOLS/4)*(NROWS/2))

static int gCount = 0;

static void wait_for_press(void)
{
    while (gpio_read(BUTTON_GPIO) == 0) ;
    while (gpio_read(BUTTON_GPIO) == 1) ;
    gCount++;
}

static void update_screen()
{
    console_clear();
    console_printf("\nCount of button presses\n");
    for (int r = 0; r < REPEAT; r++) {
        console_printf("%4d", gCount);
    }
}

void main(void)
{
    gpio_init();
    gpio_set_input(BUTTON_GPIO);
    console_init(NROWS, NCOLS, GL_GREEN, GL_BLACK);

    while (1) {
        console_printf("\n\nWaiting for button click...\n");
        wait_for_press();
        update_screen();
    }
}
