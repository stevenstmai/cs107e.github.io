/* Joystick demo */

#include "gpio.h"
#include "gpio_extra.h"
#include "uart.h"
#include "mcp3008.h"
#include "printf.h"

#define BUTTON GPIO_PIN12
#define CSI "["
#define CURSOR_UP "[1A"
#define CURSOR_DOWN "[1B"
#define CURSOR_FORWARD "[1C"
#define CURSOR_BACK "[1D"

void main(void) 
{
    gpio_init();
    gpio_set_function(BUTTON, GPIO_FUNC_INPUT);
    gpio_set_pullup(BUTTON);
    uart_init();
    mcp3008_init();
    while (1) {
        // x and y will be between 0 and 1023
        
        printf("x: %04d, y: %04d, button: %d\n", mcp3008_read(0), mcp3008_read(1), gpio_read(BUTTON)); 
    }
}
