#include "keyboard.h"
#include "console.h"

#define NROWS = 1024
#define NCOLS = 1280

void interrupt_vector(unsigned pc) {
  /* Fill this in to call your keyboard interrupt handler */
}

void main(void) {
  console_init(NROWS, NCOLS);  
  keyboard_init();

  while (1) {
    char c = keyboard_read();
    if (c > 0) {
      console_putc(c);
    }
  }
}
