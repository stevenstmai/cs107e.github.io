#include "midi.h"
#include "gpio.h"
#include "timer.h"
#include "gpio_extra.h"
#include "printf.h"

#define MIDI_PIN GPIO_PIN25
//#define BAUD     32000
#define BAUD     31250
#define DELAY    (1000000 / BAUD)

static unsigned channel = 0;

void midi_init() {
  gpio_set_output(MIDI_PIN);
  gpio_set_pulldown(MIDI_PIN);
  midi_reset();
}

// Need inversion: a logical 1 is a high signal
inline void send_bit(uint8_t val) {
  ///gpio_write(MIDI_PIN, val == 0);
  gpio_write(MIDI_PIN, val);
  timer_delay_us(DELAY);
}

inline void send_byte(uint8_t val) {
  unsigned i;
  send_bit(0); // start bit
  for (i = 0; i < 8; i++) { // data bits, LSB first
    send_bit((val >> i) & 1);
  }
  send_bit(1); // stop bit
}

void midi_reset() {
    uint8_t cmd[] = {0xff};
    midi_send(cmd, 1);
}

void midi_send(uint8_t* cmd, unsigned len) {
  unsigned i;
  for (i = 0; i < len; i++) {
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

void midi_test() {
  unsigned command = 0xaaaa5555;
  midi_send((uint8_t*)&command, 4);
}

void midi_set_channel(unsigned ch) {
  channel = ch;
}

unsigned midi_channel() {
  return channel;
}

void midi_print(uint8_t* cmd, unsigned len) {
    for (unsigned int i = 0; i < len; i++) {
        printf("%x, ", cmd[i]);
    }
    printf("\n");
}

void play_midi(uint8_t *data, unsigned int length, int tempo) {
   for (int i = 0; i < length; i++) {
       // read time
       int dt = data[i]; // will work for simple programs (need to read var length, eventually)
       printf("delay: %d\n", dt);
       timer_delay_us(dt * tempo / 200);
       // read message type
       uint8_t msg_type = data[i + 1];
       if ((msg_type >> 4) == 0x9 || 
           (msg_type >> 4) == 0x8 ||
           (msg_type >> 4) == 0xb ||
           (msg_type >> 4) == 0xe) {
           // two argument message
           midi_send(data + i + 1, 3); 
           midi_print(data + i + 1, 3); 
           i += 3;
       } else if ((msg_type >> 4) == 0xc) {
           // one argument message
           midi_send(data + i + 1, 2);
           midi_print(data + i + 1, 2);
           i+=2;
       }
   } 
}
