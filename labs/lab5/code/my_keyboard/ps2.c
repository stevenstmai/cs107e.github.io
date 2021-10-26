#include "gpio.h"
#include "gpio_extra.h"
#include "malloc.h"
#include "ps2.h"

// this definition of struct fields fills out the
// incomplete type declared in ps2.h
struct ps2_device {
    unsigned int clock;
    unsigned int data;
};

ps2_device_t *ps2_new(unsigned int clock_gpio, unsigned int data_gpio)
{
    // consider why must malloc be used to allocate device
    ps2_device_t *dev = malloc(sizeof(*dev));

    dev->clock = clock_gpio;
    gpio_set_input(dev->clock);
    gpio_set_pullup(dev->clock);

    dev->data = data_gpio;
    gpio_set_input(dev->data);
    gpio_set_pullup(dev->data);
    return dev;
}

// adding a helper function read_bit() highly recommended
// the helper wait for falling edge on clock gpio
// then reads value from data gpio. This helper will
// be used for for ps2_read.

unsigned char ps2_read(ps2_device_t *dev)
{
    // TODO: Implement this function during lab5
    return 0xFF;
}
