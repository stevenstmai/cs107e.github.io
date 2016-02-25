#include "proto.h"
#include "gpio.h"
#include "timer-int.h"
#include "circular.h"
#include "keyboard.h"
#include "console.h"

#define NROWS 512
#define NCOLS 640

// This function should not be called.
void impossible_vector(unsigned pc) {
  printf("impossible exception at pc=%x\n", pc);
  reboot();
}

void interrupt_vector(unsigned pc) {
  // FIXME: Handle interrupts.
}

void main(void) {
  uart_init();
  keyboard_init();
  console_init(NROWS, NCOLS);

  while (1) {
    char c = keyboard_read();
    if (c > 0) {
      console_putc(c);
    }
  }

  reboot();
}
