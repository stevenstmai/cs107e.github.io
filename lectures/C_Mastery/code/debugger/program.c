#include "gpio.h"
#include "timer.h"
#include "printf.h"
#include "uart.h"

void blink_gpio(unsigned int pin)
{
    gpio_set_output(pin);
    for (int i = 0; i < 3; i++) {
        gpio_write(pin, 1);
        timer_delay(1);
        gpio_write(pin, 0);
        timer_delay(1);
    }
}

int increment_if(int n)
{
    if (n != 0)
        n++;
    return n;
}

void main(void)
{
    gpio_init();
    uart_init();

    blink_gpio(GPIO_PIN47);

    int result = increment_if(2);
    printf("Increment(2) = %d\n", result);
    result = increment_if(0);
    printf("Increment(0) = %d\n", result);

    uart_putchar(EOT);
}
