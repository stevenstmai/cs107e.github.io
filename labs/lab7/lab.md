---
layout: page
title: 'Lab 7: Raspberry Pi, Interrupted'
permalink: /labs/lab7/
---

## Learning goals

During this lab you will:

1.  Go through how interrupts are set-up on the Pi.
2.  Get GPIO event interrupts working on your Pi.
3.  Display something on the screen when a button is pressed.

We've provided several support libraries (GPIO implementations, timers,
interrupt initialization, etc.) to make this easier. Look at what's available
to you before getting started so you don't have to repeat work. The goal of the
lab is for you to get experience with enabling interrupts and having them
interact with your main loop. Please complete the [check list](checklist) as
you work through the lab.

## Lab exercises

To start this lab, pull from `cs107e.github.io` and go into the directory
`labs/lab7`.

### 1) Compile the project and inspect its assembly

With your lab-mates, read through the code (starting from `start.s`,
but also including `cstart.c` and `main.c`). Then, answer the
questions in [Part 1 of the check list](checklist). This code
should be familiar from lecture.

### 2) Set-up a button circuit

Set-up a simple, one button circuit such that the button's output feeds into
GPIO pin 23. What we want is for the pin to default to being high (1). When we
press the button, it should go low (0).

The way to do this is to make the pin have a "pull-up resistor". (We
won't use a *physical* resistor; instead, we'll tell the Pi to set one
up for us.) This means that when the pin is in an open circuit (the
button is not pressed), it will default to a value of 1. When the
button is pressed, we want to close a circuit that connects the pin to
ground, so it will read a 0.

You should simply need to connect one side of the button to ground, and the
other side of the button to GPIO pin 23.

<img title="Button circuit" src="images/button-circuit.jpg" width="300">

Next, implement the `button_test` function in `main.c`. The function
should start by setting GPIO pin 23 as an input and setting the
pull-up on the same pin. (Look at the commented-out code in
`kdriver_init` for examples of how to do these for pin 23.)

Then spin in an infinite loop. On each iteration of the loop:

1. First wait until the pin is 0 (checking its state with
`gpio_read`). This waits for the button to be pressed down.

2. Once the button is pressed down, print a `"+"` using `printf` to
tell you.

3. Then wait until the pin is 1 again (that is, wait until you've
released the button).

Insert a call to `button_test` before the while loop in `main`.

Compile the program and run it on your Raspberry Pi. Ensure that
`button_test` works. Note that you'll likely get more than one "button
press" per physical button press. Why do you think this might be? When
you're done, answer [part 2 of the check list](checklist).

### 3) Write an interrupt handler!

Remove the call to `button_test` in `main`.

Before being able to handle interrupts, you'll need to configure your Pi so
that a falling edge on GPIO pin 23 will trigger an interrupt. We've already
written this code for you in `kdriver_init`: you simply need to uncomment it.
Ensure you understand what every line does and why it's necessary.

In the interrupt handler `int_handler`, increment the counter `cnt`. In `main`, write
an infinite loop that just displays the value of `cnt` on each iteration
using `printf`.

Compile and run your program. Ensure that it works as expected. That
is, that the counter increments ~once per button press and that the
counter is printed when it is incremented by the interrupt handler.

Now, comment out the `gpio_check_and_clear_event` call in `int_handler`.
Compile, run, and test this program by pressing the button. What happens? Why?

Uncomment the `gpio_check_and_clear_event` call. Compile and run your program,
and ensure that it works again. When you're done, answer [part 3 of the check
list](checklist).

### 4) Use push/pop in interrupt handler.

We've provided a precompiled version of the circular buffer code from lecture
in `lib/circular.o`. The `Makefile` links this file into the final binary so
that you can use the `cir_push` and `cir_pop` functions to push and pop from a
circular buffer of integers. The `circular.h` file declares these functions.

Instead of simply incrementing a counter in the interrupt handler, call
`cir_push` with the counter's value. Then, in `main`, instead of reading the
counter directly, call `cir_pop` to get the last counter's value. Recompile and
ensure that your code works exactly as before.

When you're done, answer [part 4 of the check list](checklist).

### 5) Display interrupts

Make 4 copies of your test circuit with 4 different buttons. Hook them up to 4
different GPIO pins. Configure your Pi so it has an interrupt on either a
falling or rising edge, that is, whenever the state of a button changes.

In the interrupt handler, clear any pending events and use `gpio_pin_read` to
check the state of each button. For each time the button is pressed or
released, increase a counter by 1.

To do this, you'll need to keep track of the previous state of each
button. Display the counter on your screen in your main loop.

By how much does the counter increment on each button press or
release?  Does this number seem higher or lower than the actual number
of times you pressed buttons?

When you're done, answer [part 5 of the check list](checklist).

## TA Check Off

At the end of the lab period, submit the checkoff form and ask your lab TA to
approve your submission so you are properly credited for your work.

