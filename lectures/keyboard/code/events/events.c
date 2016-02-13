#include <stdio.h>
#include "gpio.h"
#include "uart.h"
#include "ps2.h"

const unsigned GPIO_EVENT_DETECT_STATUS = 0x20200040;
const unsigned GPIO_FALLING_EDGE_ENABLE = 0x20200058;

const unsigned CLK  = GPIO_PIN23;
const unsigned DATA = GPIO_PIN24; 

void enable_falling_edge_detect(unsigned pin) {
  if ( pin < 0 || pin >= GPIO_MAX ) return;

  volatile unsigned *addr = (unsigned*)(GPIO_FALLING_EDGE_ENABLE + 4 * (pin / 32));
  unsigned shift = pin % 32;

  unsigned val = *addr;
  val |= (1 << shift);
  *addr = val;
}

int read_event(unsigned pin) {
  if ( pin < 0 || pin >= GPIO_MAX )
    return 0;

  volatile unsigned *addr = (unsigned*)(GPIO_EVENT_DETECT_STATUS + 4 * (pin / 32));
  unsigned shift = pin % 32;

  unsigned val = *addr;
  unsigned mask = (1 << shift);
  return (val & mask);
}

void clear_event(unsigned pin) {
  if ( pin < 0 || pin >= GPIO_MAX )
    return;

  volatile unsigned *addr = (unsigned*)(GPIO_EVENT_DETECT_STATUS + 4 * (pin / 32));
  unsigned shift = pin % 32;

  *addr = (1 << shift);
}

void wait_for_clock(unsigned pin) {
  while(read_event(pin) == 0) {}
  clear_event(pin);
}

void keyboard_init(void) 
{
  gpio_set_function(CLK, GPIO_FUNC_INPUT); 
  gpio_set_pullup(CLK); 
  enable_falling_edge_detect(CLK);

  gpio_set_function(DATA, GPIO_FUNC_INPUT); 
  gpio_set_pullup(DATA); 
}


int keyboard_read(void) 
{
  int bit = 0;
  int scancode = 0;

  wait_for_clock(CLK);
    
  for (int i = 0; i < 8; i++) {
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
