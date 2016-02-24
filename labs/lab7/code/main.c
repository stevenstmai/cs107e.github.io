#include "proto.h"
#include "gpio.h"
#include "timer-int.h"
#include "circular.h"

void int_handler(unsigned);

// should not get called.
void impossible_vector(unsigned pc) {
  printf("impossible exception at pc=%x\n", pc);
  reboot();
}

/* we only enable GPIO interrupts, so just forward it blindly  */
void interrupt_vector(unsigned pc) {
  int_handler(pc);
}

/* trivial little program to catch gpio interrupts on button pressing. */
#define RPI_INT_ENABLE_1             0x2000B210
#define RPI_INT_ENABLE_2             0x2000B214
#define RPI_INT_DISABLE_1            0x2000B21C
#define RPI_INT_DISABLE_2            0x2000B220

/*
 * Disable all interrupts except  GPIO interrupt 0, which is for pins 0-31. This
 * interrupt is IRQ 49, so bit 17 of the second register (BCM2835 ARM
 * Peripherals Manual, top of page 113).
 */
void kdriver_init() {
  gpio_init();

  // Ensure all interrupts are disabled.
  PUT32(RPI_INT_DISABLE_1, 0xFFFFFFFF);
  PUT32(RPI_INT_DISABLE_2, 0xFFFFFFFF);

  // We'll be hooking up a button to Pin 23, so set it up appropriately.
  /* gpio_set_input(GPIO_PIN23);  // PS/2 clock */
  /* gpio_set_pullup(GPIO_PIN23);  // PS/2 clock */
  /* gpio_detect_falling_edge(GPIO_PIN23); */

  // Enable GPIO interrupt 0
  /* PUT32(RPI_INT_ENABLE_2, 0x00100000); */

  // Enable interrupts
  /* system_enable_interrupts(); */
}

volatile int cnt = 0;
void int_handler(unsigned pc) {
  gpio_check_and_clear_event(GPIO_PIN23);
  // Do something here?
}

void button_test() {
  // FIXME: Implement me.
}

void main(void) {
  uart_init();
  kdriver_init();

  while (1) {
    // Do nothing, for now.
  }

  reboot();
}
