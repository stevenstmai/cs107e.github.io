---
layout: page
title: 'Assignment 7: Full Console'
permalink: /assignments/assign7/
---

**Due: Tuesday, March 1, 2016 at 7:00PM**

![Google Console](images/google.png)

In this assignment, you'll complete your console. After this assignment, you
will be able to type with a PS/2 keyboard without any worry of characters being
lost because you type too quickly.

### Learning goals

In this assignment, you will

1.  Handle interrupts from your PS/2 keyboard and use them to read scan codes
    into a circular buffer.

2.  Modify your keyboard implementation to read scan codes from the circular
    buffer rather than directly from GPIO.

### Fully Operational Battle Station

1.  **Pull the assignment 7 project.**

    To start the assignment, pull your assignment repository to get the latest
    starter code. This project is a merge of the assignment 6 and lab 7 code.
    You will need to copy in `keyboard.c` and `console.c` from assignment 6.

    Ensure that `make` compiles your code successfully.

2.  **Set Up PS/2 Clock Interrupts.** Modify `keyboard.c` so that
    `keyboard_init` sets up your system to trigger interrupts when there is a
    falling edge on GPIO pin 23. This is essentially the code you wrote for
    lab 7, which we've copied into lab7.c for your convenience.

3.  **Handle PS/2 Clock Interrupts.** Add a new `keyboard_int_handler` function
    in your keyboard driver, `keyboard.c`. This will be the keyboard's
    interrupt handler.

    In `main.c`, fill in the `interrupt_vector` function so that it calls the
    `keyboard_int_handler` function. Back in the handler, ensure that you clear
    events after you receive them or the event will keep on triggering forever.
    Make the handler do something very simple as we did in lab, like toggle an
    LED or increment a counter. Enable global interrupts in `main` and test
    that this handler is executing and does not crash. Commit your code so you
    have a known working point.

4.  **Read PS/2 Bytes.** Modify your interrupt handler so it reads in a byte of
    a PS/2 scan code. This should be a basic adaptation of the
    `keyboard_read_byte` code from assignment 6 except you will be receiving
    one bit per interrupt. Because you are receiving one bit at a time, you
    will need to store the bits as they come until you've received a full byte.
    Be sure to synchronize on the start bit and check the parity and stop bits.

    Test this code by writing received bytes to an array (e.g. a 16 byte array)
    and printing the contents of this array on the screen in your main loop.
    Once this code is working, commit your code so you have another known
    working point.

    ![PS/2 Packet Format]

5.  **Create a Circular Buffer.** Write the code for a circular buffer of size
    128 in `circular.c`, following the pseudocode. Fill in functions to check
    if the buffer is full and to push and pop bytes onto the circular buffer.
    Remember that all head and tail increments should be modulo `CAPACITY` so
    that the indices are always within the buffer.

6.  **Push Keyboard Bytes onto Circular Buffer.** Modify your interrupt handler
    to push a byte into the circular buffer when it receives a full byte with
    valid parity and stop bits. Adapt your prior test program so that it
    removes bytes from the circular buffer and displays them on the screen.

7.  **Process PS/2 Scan Codes.** Almost there! Modify your `keyboard_read`
    function to pop bytes from the circular buffer until it removes a
    full scancode. As before, `keyboard_read` translates this scancode into a
    character and returns it to the caller. Have your main function (in
    `main.c`) read from the keyboard and print to the console.

    You now have a fully operational console!

[PS/2 Packet Format]: images/ps2.png

### Handing in

Commit your code to your repository.

### Extension: Console Debugger

1.  **Intro.** Normally, the console will be reading characters and printing
    them to the screen as in the basic part. However, if the user presses the
    `ESC` key, the console will go into debugging mode. In debugging mode, the
    console is waiting for debug commands, similar to the tiny shell in
    assignment 6. In debugging mode, you will be able to peek or poke memory
    addresses, observe a backtrace of your function calls, and profile your
    code to observe where it is spending the most time.

2.  **Debugging Mode.** Modify your main function to detect the `ESC` key and
    shift to debugging mode. Each line in debugging mode should be interpreted
    as a command that it executes when the user presses return.

    Add the commands code from assignment 6 so that you can peek or poke any
    memory address when in debugging mode. Add the `quit` command, which will
    take you out of debugging mode and back to the regular console.

3.  **Profiling.** You'll now add profiling support to your console. You'll
    recall from lecture that this involves handling timer interrupts and
    recording the current PC inside the timer interrupt handler. For this part,
    you will incorporate and modify code from lecture and add an additional
    command to your shell.

    We have included the profiler from lecture in `gprof.{h,c}`. We have also
    included `timer-int.{h,c}` from lecture. This will be used to handle timer
    interrupts. You will need to implement `timer_int_handler` to record the
    event in the profiler. Call `timer_int_handler` when there is a timer
    interrupt. To do so, you will need to differentiate between GPIO and timer
    interrupts in `interrupt_vector` in `main.c`. You can do this by checking
    the return value of `gpio_check_and_clear_event`. If it is `1`, then the
    interrupt was caused by the GPIO pin that was checked. Otherwise, the
    interrupt was caused by the timer.

    The `gprof_init` function from `grof.c` allocates space to store counts for
    each address in the text (code) segment. `gprof_add_sample` can be used to
    increment the count for the current program counter each time there is a
    timer interrupt. `gprof_dump` can be called to print the counts. It
    currently prints over UART, so you will need to modify this to print to your
    console.

    Once this is working, add the command `profile [on | off | status |
    results]` to your debugger commands. `profile on` should initialize or
    zero-out all profile counts and start profiling (enable timer interrupts).
    `profile off` should stop the profiling (disable timer interrupts).
    `profile status` should print `Status: on` or `Status: off`, depending on
    whether the profiler is on or off, respectively. `profile results` should
    print current (if status is on) or most recent (if status is off) counts to
    the debugger console using the `gprof_dump` function.

    You now have a mini debugger!
