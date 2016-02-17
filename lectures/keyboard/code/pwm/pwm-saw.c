#include "pwm.h"

void main() {
  audio_init();
  audio_send_tone(WAVE_SAW, 1000);
}
