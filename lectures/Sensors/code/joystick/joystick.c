/* Joystick demo */

#include "gpio.h"
#include "gpio_extra.h"
#include "uart.h"
#include "mcp3008.h"
#include "printf.h"

#define BUTTON GPIO_PIN12
void main(void) 
{
    gpio_init();
    gpio_set_function(BUTTON, GPIO_FUNC_INPUT);
    gpio_set_pullup(BUTTON);
    uart_init();
    mcp3008_init();
    while (1) {
        // read channel 0
        printf("x: %04d, y: %04d, button: %d\n", mcp3008_read(0), mcp3008_read(1), gpio_read(BUTTON)); 
    }
}
