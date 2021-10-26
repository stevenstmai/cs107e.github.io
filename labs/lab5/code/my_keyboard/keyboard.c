#include "gpio.h"
#include "gpio_extra.h"
#include "keyboard.h"
#include "ps2.h"

static ps2_device_t *dev;

void keyboard_init(unsigned int clock_gpio, unsigned int data_gpio)
{
    // create new PS2 device
    dev = ps2_new(clock_gpio, data_gpio);
}

unsigned char keyboard_read_scancode(void)
{
    // read from PS2 device
    return ps2_read(dev);
}

key_action_t keyboard_read_sequence(void)
{
    // The implementation started below assumes sequence is exactly
    // one byte long. This is the case for ordinary key press actions
    // but not same for all key actions.
    // What key actions generate a sequence of length 2?  What
    // about length 3?
    // Figure out what those cases are and extend this code to
    // properly handle those sequences and generate the correct
    // key actions
    key_action_t action;
    action.keycode = keyboard_read_scancode();
    action.what = KEY_PRESS;
    return action;
}
