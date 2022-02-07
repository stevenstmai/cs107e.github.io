#include "timer.h"
#include "gpio.h"
#include "gpio_extra.h"
#include "midi.h"

static unsigned int midi_pin = MIDI_PIN;

#define BAUD     31750
#define DELAY    (1000000 / BAUD)

static unsigned int channel = 0;

void midi_init(unsigned int pin) {
    midi_pin = pin;
    gpio_set_output(midi_pin);
}

static inline void send_bit(uint8_t val) {
    gpio_write(midi_pin, val);
    timer_delay_us(DELAY);
}

static inline void send_byte(uint8_t val) {
    send_bit(0); // start bit
    for (unsigned int i = 0; i < 8; i++) { // data bits, LSB first
        send_bit((val >> i) & 1);
    }
    send_bit(1); // stop bit
}

void midi_send(uint8_t* cmd, unsigned int len) {
    for (unsigned int i = 0; i < len; i++) {
        send_byte(cmd[i]);
    }
}

void midi_note_on(uint8_t key, uint8_t velocity) {
    uint8_t command[3];
    // Note on is 1001cccc where cccc is the channel
    command[0] = 0x90 | (channel & 0xf);
    command[1] = key;
    command[2] = velocity;
    midi_send(command, 3);
}

void midi_note_off(uint8_t key, uint8_t velocity) {
    uint8_t command[3];
    // Note off is 1000cccc where cccc is the channel
    command[0] = 0x80 | (channel & 0xf);
    command[1] = key;
    command[2] = velocity;
    midi_send(command, 3);
}

void midi_test(void) {
    unsigned command = 0xaaaa5555;
    midi_send((uint8_t*)&command, 4);
}

void midi_set_channel(unsigned int ch) {
    channel = ch;
}

unsigned int midi_channel(void) {
    return channel;
}
