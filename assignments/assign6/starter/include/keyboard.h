#ifndef KEYBOARD_H
#define KEYBOARD_H

void wait_for_falling_edge(unsigned pin);
void keyboard_init(void);
int keyboard_read_byte(void);
char keyboard_read(void);

#endif
