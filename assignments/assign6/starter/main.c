#include <stdio.h>
#include <gpio.h>
#include <uart.h>

#include "ps2.h"
#include "keyboard.h"
#include "commands.h"
#include "console.h"
#include "strtol.h"

static const command_t commands[] = {
  {"help", "[cmd] prints a list of commands or description of cmd", cmd_help},
  {"echo", "<...> echos the user input to the screen", cmd_echo},
};

int cmd_echo(int argc, const char *argv[]) {
  for (int i = 1; i < argc; ++i) {
    console_printf(argv[i]);
  }

  console_printf("\n");
  return 0;
}

int cmd_help(int argc, const char *argv[]) {
  // FIXME: Part 7.

  return 0;
}

void main(void) {
  uart_init();
  keyboard_init();

  while (1) {
    char c = keyboard_read();
    if (c > 0) {
      printf("%c\n", c);
    }
  }
}
