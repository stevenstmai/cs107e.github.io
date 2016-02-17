#include <stdio.h>
#include "gpio.h"
#include "uart.h"
#include "ps2.h"

const unsigned CLK  = GPIO_PIN23;
const unsigned DATA = GPIO_PIN24; 

void wait_for_clock(unsigned pin) {
  while(gpio_read(pin) == 0) {}
  while(gpio_read(pin) == 1) {}
}

void keyboard_init(void)
{
  gpio_set_function(CLK, GPIO_FUNC_INPUT); 
  gpio_set_pullup(CLK); 
 
  gpio_set_function(DATA, GPIO_FUNC_INPUT); 
  gpio_set_pullup(DATA); 
}

int keyboard_read(void) 
{
  int bit = 0;
  int scancode = 0;

  wait_for_clock(CLK);
  
  for(int i=0; i < 8; i++) {
    wait_for_clock(CLK);
    bit = gpio_read(DATA);
    scancode |= (bit << i);
  }

  wait_for_clock(CLK);
  wait_for_clock(CLK);

  return scancode;
}


void main(void) 
{
  uart_init();
  keyboard_init();

  while (1) {
      int scancode = keyboard_read(); 
      if( scancode )
          printf("%2x -> %c\n", scancode, char_from_scan[scancode]);
  }
}
