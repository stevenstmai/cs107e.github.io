#ifndef LED_H
#define LED_H

/* Functions for the Raspberry Pi status LED.
 * Author: Philip Levis <pal@cs.stanford.edu>
 * Date: August 14 2014
 */ 

void led_init(void);
void led_write(int val);
void led_on(void);
void led_off(void);
void led_toggle(void);

#endif
