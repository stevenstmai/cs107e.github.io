#include <stdio.h>
#include <gpio.h>
#include <uart.h>

#include "ps2.h"
#include "keyboard.h"

const unsigned CLK  = GPIO_PIN23;
const unsigned DATA = GPIO_PIN24;

void wait_for_falling_edge(unsigned pin) {
  while (gpio_read(pin) == 0) {  }
  while (gpio_read(pin) == 1) {  }
}

void keyboard_init(void) {
  gpio_set_function(CLK, GPIO_FUNC_INPUT);
  gpio_set_pullup(CLK);

  gpio_set_function(DATA, GPIO_FUNC_INPUT);
  gpio_set_pullup(DATA);
}

/**
 * Reads a byte from the PS2 keyboard.
 *
 * @return the byte (a positive number) if the read was successful
 *         a negative number if the read was unsuccessful
 */
int keyboard_read_byte(void) {
  int bit = 0;
  int scancode = 0;

  wait_for_falling_edge(CLK);
  for (int i = 0; i < 8; i++) {
    wait_for_falling_edge(CLK);
    bit = gpio_read(DATA);
    scancode |= (bit << i);
  }

  wait_for_falling_edge(CLK);
  wait_for_falling_edge(CLK);

  return scancode;
}

/**
 * Reads a character from the PS2 keyboard. This happens in two steps. First,
 * the scancodes are read directly via the PS/2 protocol. Then, the scancodes
 * are converted to their ASCII character.
 *
 * @return the char (a positive number) if the read was successful
 *         0 if the read was unsuccessful
 */
char keyboard_read(void) {
  int scancode = keyboard_read_byte();
  if (scancode > 0) {
    return char_from_scan[scancode];
  } else {
    return 0;
  }
}
