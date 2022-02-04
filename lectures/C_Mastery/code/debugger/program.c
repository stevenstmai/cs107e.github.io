#include "gpio.h"
#include "timer.h"
#include "printf.h"
#include "uart.h"
#include "strings.h"

void blink_gpio(unsigned int pin)
{
    uart_putstring("Watch me blink the green led on the Pi\n");
    gpio_set_output(pin);
    for (int i = 0; i < 3; i++) {
        uart_putstring("on...");
        gpio_write(pin, 1);
        timer_delay(1);
        uart_putstring("off...");
        gpio_write(pin, 0);
        timer_delay(1);
    }
    uart_putstring("Done\n");
}

int increment_if(int n)
{
    if (n != 0)
        n++;
    return n;
}

bool trouble(int howmany)
{
    char buf[5] = "abcd";
    printf("How much trouble? Writing %d bytes beyond... ", howmany);
    memset(&buf[4], 0, howmany);
    return true;
}

void main(void)
{
    static int i;

    gpio_init();
    uart_init();

    printf("\n\n++++++++++ Starting program.c ++++++++++\n");

    blink_gpio(GPIO_PIN47);

    int result = increment_if(2);
    printf("Increment(2) = %d\n", result);
    result = increment_if(0);
    printf("Increment(0) = %d\n", result);

    for (i = 0; i < 100; i += 4) {
        if (trouble(i))
            printf("success!\n");
    }
    printf("Bye now!\n\004");
}
