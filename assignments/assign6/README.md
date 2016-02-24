---
layout: page
title: 'Assignment 6: From Keyboard to Screen'
permalink: /assignments/assign6/
---

**Due: Tuesday, February 23, 2016 at 7:00PM**

## Assignment 6: From Keyboard to Screen

![Matrix Trinity Hack](images/shell.png)

In this assignment, you'll get a PS2 keyboard working with your Raspberry Pi.
This will let you type in commands and control the Pi without needing to plug
another computer into it.

### Learning goals

In this assignment, you will

1.  Learn how PS2 scancodes work.
2.  Write a small driver that correctly translates PS2 scancodes into ASCII
    characters that can be displayed on the screen.
3.  Write a console program that allows you to type in and execute commands.

### Assignment tasks

1.  **Pull the assignment 6 project.**

    To start the assignment, pull your repository to get the latest starter code
    and `git checkout assign6` if necessary. You should see the starter code in
    your directory. Header files are located in the `include` directory. You
    will be writing functions in various files for this assignment, but all test
    code should be written within `main.c`, so your `Makefile` should continue
    to build main.bin as the output to load to the Pi.

    You will also need to copy your framebuffer, graphics, and console code into
    the code directory. Modify the `Makefile` so that your graphics and
    framebuffer code gets compiled and linked when you call `make`. You should
    only need to modify the `C_SRCS` variable. Your code will not build until
    these steps are completed.

2.  **Process PS2 scancodes.**

    Recall from lecture and lab that a PS2 scancode is an 8-odd-1 packet
    consisting of 11 bits. The first bit, the start bit, is low. The next 8
    bits are data bits, least significant bit first. The tenth bit is a parity
    bit -- odd parity means that there should be an odd number of 1s in the
    data and parity bits. The 11th and final bit is the stop bit, which is
    always high.

    ![PS2 Packet Format]

    We've provided the intial keyboard code from lecture in `keyboard.c`.
    Extend `keyboard_read_byte` so that it verifies the integrity of the parity
    bit. If the parity check fails, return `-1` from `keyboard_read_byte`. Also
    extend the function so that it checks that the start and end bits are the
    correct values. Return `-1` if either are incorrect. If the start bit is
    incorrect, you should return from the function early, immediately after
    checking.

3.  **Print characters to the screen.**

    The `main()` function in `main.c` currently uses the functions defined in
    `keyboard.c` to send the ASCII translation of the scancode (done
    by `keyboard_read()`) over UART. Modify `main()` so that it uses your
    graphics library from the previous assignment to draw characters on the
    screen. Do not worry about shift or other complexities. All you need is a
    while loop that reads a character and draws it.

    ![PS2 scancodes]

    Note that, since `keyboard_read()` simply turns scancodes to characters,
    typing some keys might lead to strange symbols appearing on the screen. You
    might also see characters appear twice: once for the press, and again for
    the release. That's fine: what matters is that typing basic characters
    shows up correctly. We'll fix these issues shortly.

4.  **Handle key press vs. key release.**

    When you press a key, the PS2 keyboard sends a scancode. When you release
    the same key, it also sends a scancode. This scancode is the same as the
    first one, except it is one byte longer: it has a leading `0xF0`. So typing
    `z` will cause the keyboard to send scancode `0x1A`. Releasing `z` will
    cause the keyboard to send scancode `0xF0 0x1A`. If you hold down z long
    enough the keyboard will send multiple press scancodes (auto-repeat).

    Modify `keyboard_read` in `keyboard.c` so that it will only return
    characters when a key is pressed, not when it is released. For example, if
    the scancodes received are `0x1A`, `0x1A`, `0xF0 0x1A` and `0x34`, the
    calls to `keyboard_read()` should return `z`, `z`, `g`, and not `z`, `z`,
    `z`, `g`. Keep in mind that we'll need to use the key up vs. down
    distinction to correctly handle shift in the next section.

    Also, modify your driver so it ignores (reads and does nothing with) a
    value of `0xE0`. This code is used for some more advanced keys. Ignoring it
    means that you might see some funny behavior (e.g., pressing volume up will
    cause a b to be read), but that's OK. If you don't do this then pressing
    keys which have an `0xE0`, such as the right control key, will cause
    multiple characters to be read.

    Note: we have `#define`d a few scancodes in `include/ps2.h`.

5.  **Implement shift and caps lock.**

    Modify `keyboard_read()` so that it correctly handles caps lock and shift.
    If you press a key while the shift key is down, `keyboard_read()` should
    return the result of the character in `shift_lookup_table`, declared in
    `include/ps2.h`. If you press the caps lock key, then shift should be
    enabled until caps lock is pressed again. If you press shift while caps
    lock is enabled, characters should be lower case.

    [PS2 Packet Format]: images/ps2.png
    [PS2 Scancodes]: images/scancode.gif

6.  **Implement a simple shell.**

    At this point, you should be able to handle most characters typed at the
    keyboard. You'll now implement a simple shell which will allow you to type
    in and execute commands. You'll do this in `main` in `main.c`.

    To do so, you'll need to store the characters that are being typed into the
    console line by line. When `backspace` is pressed (scancode `0x66`), the
    console should delete the last character on the current line or do nothing
    if the line is empty. When `enter` is pressed, you should execute the
    command the user has typed in.

    Executing a command entails interpreting the line as a command, creating
    the inputs to the function corresponding to the command, and finally
    calling the function. We've declared a three-field structure in
    `include/commands.h` that represents commands. The first field, `name`, is
    the name of the command a user will type in to execute the command.
    `description` is self explanatory and is intended for human consumption.
    Finally, `fn` is a pointer to a function that takes two arguments: `argc`,
    the number of strings in `argv`, and `argv` a list of strings. It returns
    an `int` which should be `0` if the command executed successfully, or
    nonzero otherwise.

    We've constructed a table of commands in `main.c` called `commands`. You
    should modify this table if you wish to add commands to your console.

    When a user presses `enter`, you should process the current line as a
    command as follows:

    1. If the line is empty, simply print a new line.
    2. Otherwise, create an array of `char *` where each entry is one word in
       the line. "Words" are any characters separated by a space.
    3. Search the `commands` array (in `main.c`) for the command whose name
       is the first word on the line. If no matching command is found, print a
       short error message of your liking.
    4. Call the `fn` associated with the command, passing `argc`, the number of
       words (or arguments) in the line, including the first, and `argv`, an
       array of `char *`, i.e. an array of strings, with one element for each
       word in the line. There should be `argc` elements in `argv`.

    We've implemented the `echo` command for you. `echo` simply prints out all
    of its parameters. For instance, when a user types `echo Hello, world!` in
    the console, the console should print: `Hello, world!`. The session should
    look as follows once you've successfully implemented this tiny shell:

        echo Hello, world!
        Hello, world!

    _Note: This is very similiar to the way your shell (bash, zsh, etc.) works!_

7.  **Utilities**

    Add the following commands to your console:

    **help**

    Without any parameters, this should print a list of all available commands
    along with their description in the following format:

        help
        cmd1 - description
        cmd2 - description

    If a parameter is given, it should print the description for that command,
    or an error message if the command doesn't exist:

        help help
        [cmd] prints a list of commands or description of cmd

        help please
        error: 'please' is not a valid command

    **clear**

    This should clear the screen and bring the console back to the top line. It
    takes no parameters.

    **reboot**

    This command should reboot your Pi. It takes no parameters. We've included
    the `reboot` function in `libpi` and the header file `reboot.h` in
    `include/`. You can simply call `reboot()`.

    **peek**

    This command takes two parameters: `[address] <n>`. The first is a required
    address, and the second an optional number, `n`. It prints to the console
    the `n` bytes, in hex, that are currently at address `address`. If `n` is
    not supplied, it prints a single byte.

    Example (assume 0xFFFF contains the number 0x12345678):

        peek 0xFFFF
        78

        peek 0xFFFF 4
        78 56 34 12

    Note the little endian storage. You should use `strtoul`, which we've taken
    from Apple (yay, open source!), and have supplied to you via `lib/strtol.c`
    and `include/strtol.h`, to convert a numeric string to a C integer. The
    Makefile already takes care to compile and link in `strtol.c`. It's [man
    page](http://linux.die.net/man/3/strtoul) has more information on its usage.
    You should use the `char **endptr` parameter to check if the passed in
    string was a valid number. You should also use `0` as the base. If a number
    is invalid, `peek` should print an error message.

    **poke**

    This command takes two parameters: `[address] [value]`. The first is a
    required address, and the second a required number. It sets the value at
    `address` to be `value`.

    Example (assume 0xFFFF contains the number 0x12345678):

        peek 0xFFFF 4
        78 56 34 12

        poke 0xFFFF 12345678

        peek 0xFFFF 4
        4e 61 bc 00

        poke 0xFFFF 0

        peek 0xFFFF 4
        00 00 00 00

    You should use `strtoul` to implement this command as well. Print an error
    message if either number is invalid.

### Handing in

Commit and push your code to your repository. Then, create a pull request.

### Extension

This extension consists of two parts.

1.  **History**

    Extend your command line so that pressing `up` changes the current line to
    display the command that ran prior to the one on the current line. Pressing
    down should change the current line to display the command that ran _after_
    the one on the current line, or whatever the user had typed until he/she
    pressed `up`. You should keep at least 5 lines of history, but you may
    choose to keep more.

2.  **Line Editing**

    Extend your command line so it explicitly displays where the cursor is
    (e.g., by inverting colors or a white line at the bottom) and allows the
    user to move back and forth with the arrow keys. So, for example, someone
    can type "hlp", then hit left arrow twice and type "e" to spell "help". The
    user should also be able to `backspace` at any point in the line. Hitting
    return at any point in the line should execute the entire command.
