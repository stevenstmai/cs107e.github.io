---
released: true
permalink: /labs/lab5/
title: "Lab 5: Keyboard Surfin'"
toc: true
readings: |
  [Prelab](/labs/lab5/#prelab-preparation) to prep before lab.
---
{% comment %}
Task list to copy/paste when creating PR for this lab:

__Before releasing lab5:__
- [ ] Review writeup/code/checkin questions (instructor)
- [ ] Walk through (SL)
- [ ] Followup on issues from previous quarter postmortem (issue #396)
- [ ] Update instructions/photos for non-Saleae analyzers, consider PulseView instead of Logic app?

__To prep for lab5:__
- [ ] Confirm sufficient count of PS/2 keyboards+plug board+logic analyzers for all students (Label keyboard with id number for tracking and add column to lab attendance to record number checked out to student?)
- [ ] Print copies of bootloader.c source code
- [ ] Print copies of PS/2 key code chart (assignments/assign5/images/scancode.gif)

{% endcomment %}

*Lab written by Philip Levis and Pat Hanrahan*

## Goals

In your next assignment, you will write a PS/2 keyboard driver for your Pi. The
primary goal of this lab is to set up the keyboard so that you can start on
the assignment.

During this lab you will:

- Connect a keyboard to your Raspberry Pi's GPIO pins.
- Watch the signals from the keyboard using a logic analyzer.
- Print out the scancodes sent by the keyboard.
- Write code to decode the PS/2 protocol to produce scancodes.
- Read and understand the code for the magical bootloader program on your SD card. It is important to be able
  to read code produced in the wild.

## Prelab preparation
To prepare for lab, do the following: 

- Pull the latest version of the `cs107e.github.io` courseware repository.
- Clone the lab repository `https://github.com/cs107e/lab5`.
- We will be using the Saleae `Logic 2` application to visualize the signals
  captured by the logic analyzer. Saleae <http://saleae.com> is a company known
  for its high-quality logic analyzers and software.  Here is the page with
  [links to download Logic 2](https://ideas.saleae.com/f/changelog/). Download
  and install the version for your platform. If using WSL, download the Windows
  version.
- Review the [slides from the Keyboard lecture](/lectures/Keyboard/slides.pdf)
  and this document detailing the [PS/2
  protocol](https://web.archive.org/web/20180302005138/http://computer-engineering.org/ps2protocol/).
  Print a copy of this [PS/2 key code chart](images/scancode.gif) and have it on
  hand.



## Lab exercises



### 1. Install PS/2 plug (10m)

We will distribute a keyboard kit to each of you. The kit includes a keyboard, logic analyzer, and PS/2 plug and circuit board designed for use on a breadboard.
(Click photo to show each full screen).
- __PS/2 keyboard__ (including __USB-to-PS/2 adapter__)
    ![keyboard](images/v7keyboard.png){: .zoom .w-50}
- __Logic analyzer__ 
    ![hiletgo](images/hiletgo.png){: .zoom .w-25}
- __PS/2 plug board__
    ![connector](images/connector.png){: .zoom .w-25}

These supplies are yours to use, but you must return them at the end of the quarter. Please take care of them!


Most modern keyboards use the Universal Serial Bus (USB).  Unfortunately, as we
saw in lecture, the USB protocol is complicated: a typical USB driver for a
keyboard is 2,000 lines of code.  Instead, we will interface with a PS/2
keyboard, which uses a simple serial protocol that is easy to decode.  The PS/2
keyboard appeared on the original IBM PC.  Computers have long since stopped
including a PS/2 port as standard equipment so we will wire a direct connection
from the PS/2 plug board to the GPIO pins on the Raspberry Pi. The keyboard in
your kit is a USB keyboard that can also operate in PS/2 mode.  The keyboard is
wired with a USB connector and includes a USB-to-PS/2 adapter.

There are two common PS/2 devices: a keyboard and a mouse.  PS/2
devices connect to a PC using a 6-pin
[mini-DIN connector](https://en.wikipedia.org/wiki/Mini-DIN_connector).
By convention, mice use a green connector and keyboards use a
purple connector.  Inspect the inside of the mini-din PS/2 connector. It
contains a plastic tab (that forces you to insert it with the correct
polarity) and 6 male pins. Two pins are NC (not-connected), and the others
carry VCC, GND, DATA and CLK.

![PS/2 6-pin mini-din pinout](images/minidin.png)

Identify which four pins correspond to VCC, GND, DATA, and CLK. 

Take our your PS/2 plug board. Flip it over to see how the pins
stick out from the bottom of the circuit board. Four of those pins
are connected to the header pins on the board, through small traces.
Because these traces have to cross physically, three are on one side
of the board and one is on the other.  Choose one of the pins and
connect a male-to-male jumper in the corresponding hole in the min-DIN
socket. Using a multimeter set to resistance mode (Ohms), check that
the connection from the end of the male jumper to the header pin
has a very low resistance.

Place the PS/2 plug board into your breadboard. Be sure that the
four pins are on four different rows. We will use female-to-male
jumpers to connect the pins of the board to your Pi and logic analyzer
through the breadboard.
For visual simplicity, use the following convention: red for
VCC, black for GND, white for CLK, and yellow for DATA.

### 2. Use a logic analyzer to visualize keyboard signals (20m)

We're going to use a logic analyzer to examine the signals sent by the keyboard. 

Open the *Logic 2* application you installed on your laptop as prelab
preparation. The start-up screen should be similar to this:

![Logic2 Startup](images/Logic2ConnectDevice.png)

Once you connect the logic analyzer to your computer, the screen will look like this:

![Logic2 Connected](images/Logic2Start.png)

Familiarize yourself with the hardware of the logic analyzer. It has a bank of
pins that correspond to the different signals or _channels_ to be monitored by
the analyzer. The analyzer supports reading up to 8 simultaneous channels. The
analyzer uses a USB connection to your laptop to receive power and send data.

You need to supply power to your keyboard.  Add VCC (red) and (black) GND
jumpers from the breadboard rows for those pins on your PS/2 plug board 
to 5V and GND pins on your Raspberry Pi.

On the analyzer, identify the pins for channels 0 and 1. You are going to
connect these two channels to the CLK and DATA pins of your PS/2 keyboard.
Connect the white CLK jumper to channel 0
on your analyzer and connect the yellow DATA jumper to channel 1.
From left to right, the colors are red, black, white, yellow.

![wire order](images/connector_wiring.jpg){: .zoom .w-25}

*Add a second white jumper to CLK and a second yellow jumper to DATA.*
We will use these later, but it's easier to connect them in now. They will
let you simultaneously receive the data at your Pi and look at the scancodes 
on the logic analyzer, so during debugging you can compare what your Pi thinks
it's receiving with the ground truth of what the logic analyzer sees.

You must also ground the logic analyzer. Voltage is relative: when the logic
analyzer looks at a signal, all it can tell you is its difference from a
reference, which in this case is the ground provided by the Pi. If you don't
connect ground, then it's measuring voltage against whatever happens to be
on the pins, which can act as tiny little antennas. Identify 
the ground pin on the analyzer and use a black jumper to connect it to a 
ground pin on your Raspberry Pi. There may be a separate ground per channel 
or one shared ground, depending on the model of logic analyzer you are using.

Lastly, connect the USB cable from the logic analyzer to a USB port on your laptop.

This is what it looks like when the keyboard is wired up to the logic analyzer.

![wired up](images/connector_analyzer.jpg){: .zoom .w-75}
![wired up](images/connector_analyzer_spaced.jpg){: .zoom .w-75}

If you haven't already, attach your keyboard to the PS/2 plug board. Make sure
to connect the USB-to-PS/2 adapter to the keyboard, and then you can plug it
right into the plug board outlet.

In the Logic 2 application, hit the green start button in the upper right to
start reading the signal. Type a little bit and stop reading the signal.
The application records and visualizes activity on channels 0 and 1. 
You can zoom in and out and pan left and right to see the details
of the captured signal. You should see the characteristic pattern of the PS/2
protocol. 

The Logic 2 application provides protocol analyzers that can be applied to
the captured data. Click the `1F` icon on the right side of the window to
display the  *Analyzers* pane. Click the `+` in upper right to access the list
of analyzers and choose the PS/2 protocol analyzer. Configure it for CLK on
channel 0 and DATA on channel 1. The captured data is now decoded according to
the PS/2 protocol and displays the scancodes sent by the keyboard.

![Logic 2 Analyzer](images/Logic2Analyzer.png)

Hover over the visualization of the PS/2 clock channel to see the signal timing
data. How far apart is each falling clock edge? At what frequency is the PS/2
clock running?  Is the keyboard operating with the range dictated by the
[spec](https://web.archive.org/web/20180302005138/http://computer-engineering.org/ps2protocol/)? 

You're ready to answer the first check-in question[^1].

### 3. Run keyboard test (20m)

We're now ready to try reading the keyboard signals on the Pi. 
Using your breadboard, connect a white jumper
(CLK) from your PS/2 plug board to GPIO 3 on your Raspberry Pi
and a yellow jumper (DATA) to GPIO 4 (if you added the suggested second jumpers while
setting up your plug board, you can use those to connect to the Pi). You want to have to jumpers
in case you need to inspect what your keyboard is sending while
you are debugging your keyboard code: the logic analyzer gives you
a ground truth on the signal, and you can compare it with what your
code produces.

Here is what it should look like if everything is connected up properly.

![Keyboard plugged into the Raspberry Pi](images/ps2pi.JPG){: .zoom .w-75}

The `keyboard_test` application uses the reference implementation of the
keyboard driver. Let's try it now:

```console
% cd code/keyboard_test
% make run
```
Type keys on the PS/2 keyboard and the program should print the scancodes
received. If you aren't getting events, check your wiring.

Note that scancodes are not ASCII characters. Instead, these values relate to
the physical placement of the key on the keyboard.  Inside the keyboard,
there's a 2D matrix of wires that generates the scancode bits. It is the
keyboard driver that will implement the logic to lookup that code and generate
the appropriate ASCII character. 

Each key press and key release is reported as a distinct action. Press a key;
the keyboard sends a scancode. Release the key; the keyboard sends another
scancode; this code is same as the first one, except it is one byte longer: it
has a leading `0xF0`. Tap the `z` key now. The keyboard sends `0x1A` on key
press, followed by `0xF0` `0x1A` on key release.

If you press `z` and hold it down, the keyboard enters auto-repeat or
_typematic_ mode where it repeatedly generates key press actions until you
release the key.  Press and hold `z`and watch for the repeat events to start
firing. About how long does it seem to take for auto-repeat to kick in? At
about what rate does it seem to generate auto-repeat events?  

Type some single letters to observe the codes for press, release, and
auto-repeat.  Then try typing modifier keys like Shift and Alt. Try pressing
more than one key at a time. 

* What sequence of codes do you see when typing (capital) `A`? What does this
  tell you about what will be required for your keyboard driver to handle the
  Shift or Control keys?  

You're ready for the second check-in question [^2]

<style>
  .sidebar { font-size: small; }
</style>

> __Side note on N-key rollover__
- The PS/2 protocol reports a key action with an individual scancode. If the user simultaneously presses N keys on a PS/2 keyboard, the keyboard should report this state by sending N scancodes, i.e., there is no limit on the number of key actions that can be detected and reported.  In contrast, the USB protocol asks the keyboard for the current state and the keyboard's answer is limited to reporting at most 6 pressed keys, i.e., USB is constrained to 6-key rollover. Try observing this on your laptop keyboard (which is likely USB). Open your editor or use the Mac "Keyboard Viewer" to visualize (In Preferences->Keyboard, enable "Show keyboard and emoji view in menu bar", then choose "Open Keyboard Viewer" from input menu). Hold down one letter, then two, and so on, and you'll reach a point at which no further key presses are detected.
- While the PS/2 protocol has no limitations and in theory allows full N-key rollover, in practice, the internal wiring of many PS/2 keyboards shares circuitry among keys rather than wiring each key independently. As a result, as you hold down more and more keys on your PS/2 keyboard, you'll likely reach a point where additional keys are mis-detected. Try it now on your PS/2 keyboard. How many simultaneous keys can your keyboard reliably detect?
- Here is a good explanation from Microsoft Research on [N-key rollover and keyboard circuitry](http://web.archive.org/web/20180112133411/https://www.microsoft.com/appliedsciences/content/projects/AntiGhostingExplained.aspx) if you want to learn more.
{: .callout-info .sidebar}

### 4. Implement ps2_read (40m)

Your final achievement will be to get a start on writing your own keyboard
driver. We want you to do this in lab because it touches on both
hardware and software, so it can be tricky to debug; it helps to
have staff around! Once this is working, it's all software, which is typically smoother sailing.

Change to the directory `code/my_keyboard`. This is the
same application as `code/keyboard_test`, except that rather than
using the reference implementation, you are going to write your own code to
read scancodes and sequences.

[Browse the headers](/header) for ps2.h and keyboard.h to review the module
documentation. The `ps2` module manages the low-level communication with a PS2
device. The `keyboard` module layers on the ps2 module to interpret scancodes
into typed keys. During lab, you will implement initial versions of the
functions `ps2_read` in `ps2.c` and `keyboard_read_sequence` in `keyboard.c`.

Open `ps2.c` in your text editor. The function `ps2_new` has already been
written for you.  This function configures a new PS2 device for the specified
clock and data gpio. In the library modules we have seen thus far, we have used
global variables to store data that is shared across the module. A single set
of global variables for the ps2 module does not work, as each device needs its
own independent settings (i.e clock and data gpio). `ps2_new` creates a new
struct to hold the per-device settings. Because that memory needs to be
persistent after the function call exits, it allocates memory using your shiny
new `malloc` . The rest of the function is setting the clock and data GPIOs as
inputs and enabling the internal pull-up resistor so these pins default to
high, as expected in the PS/2 protocol.

The function `ps2_read` reads the individual bits that make up a scancode. We
want you to write this function here in lab as a start on your next assignment.

Before reading each bit from the data line, a PS2 device must first wait for
the falling edge on the clock line. You will need to repeatedly do these tasks
and rather than replicate code, we suggest you define a private helper function
`read_bit`. The helper waits until observes the transition from high to low on
the clock line and then reads a bit from the data line. Unifying repeated code
into a shared helper aids readability and maintainability; this is a good habit
to adopt. 

> If you need a refresher on how to correctly wait for a clock edge, take a
> look at the [Keyboard lecture ps2 sample
> code](/lectures/Keyboard/code/ps2/ps2.c). This application prints out
> the raw bits of a scan code.
{: .callout-info}

A scancode transmission consists of 11 bits: a start bit (always low), 8 data
bits, a parity bit, and a stop bit (always high).  To synchronize with the keyboard,
`ps2_read` should verify that first bit read is a valid start bit, e.g. is 0.
If not, discard it and read again until a valid start bit is received.  Next,
read the 8 data bits. 

* In which order do the 8 data bits arrive? [^3]  *Hint: if you're not sure,
  take a look at the signal you captured for the keyboard's data line with the
  logic analyzer, or look back at the PS/2 protocol documentation linked in the
  prelab.*

Lastly, read the parity and stop bits. For the assignment, your driver will
validate these bits have the correct values, but for lab, just read the bits
and assume they are correct. 

If you're having trouble reading in the bits correctly, compare what your code
is reporting with the bits you see with the logic analyzer: run your program,
start the logic analyzer, and type one key. Being able to simultaneously see
exactly what bits are send *and* how your Pi interprets them is extremely
useful: it's like gdb for the pins!

The function `keyboard_read_scancode` in `keyboard.c` simply calls `ps2_read`
to get the next scancode.  This means that once you have a working `ps2_read`,
your `keyboard_read_scancode` should automatically spring to life. Build and
run the application and see that it receives each scancode sent by the
keyboard.

If your implementation of `ps2_read` is working
correctly, you should be able to compile your application and have it act
identically to the `keyboard_test` version you tested in Step 3. If you run
into any snags, please be sure to get help from us now so that you'll be able
to hit the ground running on the assignment. Show us your working code! [^4]

### 4. Bootloader (30m)
The _bootloader_ is the program that runs on the Raspberry Pi that waits to
receive a program from your laptop and then executes it.  Back in lab 1, you
downloaded `bootloader.bin` from the firmware folder and copied it to your SD
card under the name `kernel.img` so it is the program that runs when the
Raspberry Pi resets.  So far, we have used the bootloader as a "black box". Now
you are ready to open it up and learn how programs are sent from your laptop
and execute on the Pi.

The bootloader we are using is a modified version of one written by David
Welch, the person most responsible for figuring out how to write bare metal
programs on the Raspberry Pi. If it wasn't for [his great
work](https://github.com/dwelch67/raspberrypi), we would not be offering this
course!

#### Xmodem file transfer protocol
Your laptop and the bootloader communicate over the serial line via the
Raspberry Pi's UART. They use a simple file transfer protocol called XMODEM. In
the jargon of XMODEM, your laptop initiates the transfer and acts as the
_transmitter_; the bootloader acts as the _receiver_.

The transmitter divides the data from the file into chunks of 128 bytes and
sends each chunk in its own _packet_.  The payload data of a packet is
introduced by a three-byte header and followed by a single CRC checksum byte;
each packet comprises 132 bytes in total.  The transmitter and receiver
synchronize after each packet to decide whether to move on to the next packet
or re-try due to a transmission error.

![xmodem protocol](images/xmodem.svg){: width="50%" style="float:right;"}

To send a file, the transmitter follows these steps:

1. Wait for `NAK` from receiver.
2. Send 132-byte packet consisting of:
  - `SOH`, control character for _start of heading_ indicates start of a new packet.
  - Sequence number. First packet is numbered 1 and 
   the number increments from there; wraps to 0 after 255.
  - Complement of sequence number.
  - Payload, 128 bytes.
  - Checksum (sum all payload bytes mod 256).
3. Read response from receiver:
    - If `NAK`, re-transmit same packet.
    - If `ACK`, advance to next packet.
4. Repeat steps 2-3 for each packet. 
5. Send `EOT` (end of transmission), wait for `ACK`.

The receiver performs the inverse of the actions of the transmitter:

1. Send `NAK` to indicate readiness.
2. Read 132-byte packet consisting of:
    - `SOH`, sequence number, complement, payload, checksum
3. Validate packet fields (start, sequence number, complement, checksum)
     - If all valid, respond with `ACK`, advance to next packet.
     - If not, respond with `NAK` and receive same packet again.
4. Repeat steps 2-3 for each packet. 
5. When `EOT` received, respond with `ACK` to complete the operation.

#### Transmit: `rpi-run.py`

`rpi-run.py` is a Python script that runs on your laptop and transmits a binary
program to the waiting bootloader.

It is written as python script and is compatible with any OS with proper python
support. Given the handy python libraries to abstract away the details of the
XMODEM protocol-handling, the script doesn't expose the internals of the
send/receive mechanics. In fact, the bulk of the script is goop used to find
the CP2102 driver device for different platforms. Find the script and read it
over using this command in your terminal:
```console
$ cat `which rpi-run.py`
```

#### Receive: `bootloader.bin`

The `bootloader.bin` you have installed on your SD card is a C program that
runs bare-metal on the Raspberry Pi. Change to the directory
`lab5/code/bootloader`. This directory contains the bootloader source code. The
bootloader program waits for your laptop to send it a program binary. Upon
receives a program, it loads it into memory, and then branches to the code to
begin execution.

First, read the assembly language file `start.s`.
Note the `.space` directive between `_start` and the label `skip`.
This has the effect of placing the bootloader code
at location `0x200000`.
This creates a hole in memory
(between 0x8000 and 0x200000).
The bootloader loads your program into that hole.
Why can't the bootloader code also be placed at 0x8000?

The `bootloader.c` file contains the C code to perform the receiver side of the
XMODEM protocol. Go over the bootloader code in detail with your tablemates.
Start by tracing the operation when everything goes as planned without errors,
then consider what happens when things go awry.

Here are some questions to frame your discussion:

- Where does the bootloader copy the received program and how does it begin
  executing it? Which instruction is executed first?
- How does the bootloader use the green ACT led to signal to the user?
- In which circumstances does the bootloader respond with a `NAK`? When does
  the bootloader give up altogether on a transmission?
- How/why does the bootloader use the timer peripheral?
- How will the bootloader respond if you disconnect the USB-serial in the middle of
  transmission?

With your group, annotate the bootloader source with comments documenting its operation. Divide it up, something like:
- One person documents normal operation and explains how to "read" what
  bootloader is doing by watching the green LED.
- Another studies checksum calculation, how errors are detected and how
  retry/retransmit is accomplished.
- Another reviews handling for timeout, dropped connection, and when the user
  cancels the operation using Control-C.
- Someone brave can read David Welch's
  [bootloader03.c](https://github.com/dwelch67/raspberrypi/blob/master/bootloader03/bootloader03.c)
  and try to confirm our version is a faithful rewrite.

Have each person jot down notes and then explain their part to the group.
**Collate your group's notes and annotated bootloader code and show to the
CA.**[^5]


## Check in with TA

Before you leave, confirm you have a working `keyboard_read_scancode` and take your keyboard kit[^6] home.

[^1]: The PS/2 clock frequency must be in the range 10 to 16.7 kHz. To be within spec, what should time period between falling clock edges be? When you measured using the logic analyzer, what time period did you observe? Write down this number, you will need it for a later check-in question .

[^2]: What sequence of codes is sent when typing capital `A`? If you hold down both the shift key and 'a' key, what is the sequence of repeating codes is sent?  

[^3]: In a PS/2 scancode, does the least significant or most significant data bit arrive first?

[^4]: Show off that your implementation of `keyboard_read_scancode` correctly receives scancodes from your keyboard.  
    
    Back in lab1, you estimated how many instructions the Pi was executing (~20 million/second).  Earlier in this lab, you measured the time of one cycle of the PS/2 clock.  Calculate how many instructions the Pi can execute in that time. Now consider a call to `printf`. Make a ballpark estimate of how many instructions are used to process and output a single char and multiply that count by length of the format string for a rough total. If your keyboard driver makes a call to `printf` in between reading bits that overruns your budget, what will be the consequence? Keep this lesson in mind whenever working with code that has similar tight timing requirements.

[^5]: Hand in your group's annotated copy of `bootloader.c`.

[^6]: Take your entire keyboard kit (keyboard, adapter, plug board, logic analyzer) with you. This equipment is on loan to you. Please take care of it and return at the end of quarter.
