==== Pat ====

Normally MIDI uses 5V, but since it is a current loop
it can also be run at 3.3V. 

MIDI spec says 5 mA of current in the current loop.

doc/pi.midi.jpq shows a picture of a MIDI breakout board
with MIDI IN and OUT DIN connectors. The schematic is
doc/pi.midi.schematic.jpg.

MIDI OUT is connected to GPIO26 using the green wire.
Green is our color convention for PI TX and HOST RX.

MIDI IN is not used in these examples.
It would be connected to PI RX and HOST TX.
MIDI IN is routed through the 6N138 optoisolator.

The current circuit uses 220 Ohm resistors as is typical
of the MIDI spec. It would be safer to lower the value
of the resistor by 3.3V/5.0V to keep the current
constant with 3.3V. 

An inexpensive USB IN-OUT MIDI cable can be used to
connect to a laptop. I connected this to my macbook,
and was able to play music using GarageBand. I also
used MidiMonitor to show the midi notes as they were
being sent.

Author: Pat Hanrahan <pal@cs.stanford.edu>
Date: Feb 18, 2019, Updated Mar 9, 2021

==== Phil ====

Sample code to control a KORG volca keys or volca beats from the Pi.

Connect the midi data line to GPIO pin 25
(through a 220 Ohm resistor) and the current 
line to 5.0V through a 220 Ohm resistor.

Author: Philip Levis <pal@cs.stanford.edu>
Date: May 14, 2017


