#include "console.h"
#include "echo.h"
#include "gpio.h"
#include "gpio_extra.h"

#define BUTTON_GPIO GPIO_PIN21
#define NROWS 16
#define NCOLS 40
#define REPEAT ((NCOLS/4)*(NROWS/2))
#define DKGRAY 0xff222222

static int gCount = 0;

static void update_screen()
{
    console_clear();
    console_printf("\nCount of button presses\n");
    for (int r = 0; r < REPEAT; r++) {
        console_printf("%3d ", gCount);
    }
}

static void wait_for_press(void)
{
    while (gpio_read(BUTTON_GPIO) == 0) ;
    while (gpio_read(BUTTON_GPIO) == 1) ;
    gCount++;
}

void main(void)
{
    gpio_init();
    gpio_set_input(BUTTON_GPIO);
    console_init(NROWS, NCOLS, GL_AMBER, DKGRAY);

    while (1) {
        console_printf("\n\nWaiting for button click...\n");
        wait_for_press();
        update_screen();
    }
}
