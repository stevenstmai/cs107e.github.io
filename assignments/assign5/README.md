---
layout: page
title: 'Assignment 5: Basic Graphics Library and Console'
permalink: /assignments/assign5/
---

**Due: Monday, February 15, 2016 at 11:59PM**

![Wargames Console](images/wargames.jpg)

A console is a text interface for entering commands and seeing output.
Today we have powerful shell programs that support scripts, process
control, and output redirection. But simpler consoles can be very
powerful too. One very famous console is
[Joshua in WarGames](https://www.youtube.com/watch?v=ecPeSmF_ikc).

### Learning goals

In these next three assignments (5, 6, and 7), you will take 
steps to turning your Raspberry Pi into a working personal computer: 
writing a console.
After completing these 3 assignments, you will be able to plug a keyboard
and monitor into your Raspberry Pi,
type text, and see the text on the screen.

After completing this first assignment, you will be able to
draw strings of text on your screen.
We will use double-buffering so that changes seem instantaneous
without flickering or tearing.
In the next assignment you will write a keyboard driver 
so you can type in characters from a keyboard 
and display them on the screen.
In the final assignment, you will add interrupt processing,
so you never miss a character and the console code uses
the processor much more efficiently.

### Assignment tasks

1. __Pull the assignment 5 project.__

    To start the assignment, pull your repository to get the latest starter 
    code and `git checkout assign5` if necessary. You should see the starter 
    code in your directory (header files are located in the `inc` directory). 
    You will be writing functions in various files for this assignment, 
    but all test code should be written within `main.c` (so your Makefile 
    should continue to build `main.bin` as the output to load to the Pi).

2. __Finish implementing the fb libary.__  The functions in the framebuffer
    library are declared in `fb.h` and defined in `fb.c`.
    We have provided the code we
    showed in lecture to initialize the framebuffer in the starter files. 
    You will need
    to extend the library to include all the functions defined in `fb.h`.

    * `void fb_init(unsigned width, unsigned height, unsigned depth, unsigned doublebuffer)`:
    This function initializes a framebuffer with the given dimensions
    (`width`, `height`, `depth`).
    Make sure that the code works for different values of width and height.
    If `doublebuffer` is true, then double buffering is enabled;
    otherwise only a single buffer is created.
    If double buffering is enabled, you will need to create space
    for two buffers by setting the virtual
    height of the buffer to be twice the physical height.

    * `void fb_swap_buffer()`:
    This functions swaps the front and back buffer.
    The front buffer should be displayed,
    and drawing should occur in the back buffer.
    A buffer swap involves changing the Y offset from 0 to the 
    physical height (or vice versa). 
    This must be done by writing the fb struct to the mailbox
    with the new x_offset and y_offset.

    * `unsigned char* fb_get_draw_buffer()`: 
    Returns a pointer to the memory storing the back buffer,
    the one being drawn into.

2. __Basic graphics library__.  The functions used
   by the graphics library are declared in `gl.h` and defined
   in `gl.c`.  You should implement the following functions:

    * `void gl_init(unsigned width, unsigned height, unsigned mode)`: 
      This function initializes the framebuffer to a
      given `width`, `height`, and number of buffers (`GL_SINGLEBUFFER`
      or `GL_DOUBLEBUFFER`).  Assume the graphics library always uses
      32-bit RGBA pixels.

    * `gl_swap_buffer()`: This functions swaps the front and back buffer.

    * `color gl_color(unsigned r, unsigned g, unsigned b)`:
      This handy utility function 
      returns a 32-bit value representing a pixel with the
      corresponding red, green, and blue values. alpha is set to `0xff`.
      Note that `color` is defined as a type in `gl.h`.

    * `void gl_clear(color c)`:
      clear the entire framebuffer to color c.

    * `void gl_draw_pixel(int x, int y, color c)`:
      draw a single pixel at `x`,`y` with color `c`.
      Note the implementation of draw_pixel used in lecture
      has to be generalized to work with any `width`.
      Make sure that pixels are only drawn inside the 
      the rectangle defining the framebuffer.

    * `void gl_draw_rect(int x, int y, int w, int h, color c)`:
      draw a solid rectangle starting at (x, y) and with size (w, h)
      with color `c`.
      Again, make sure that pixels are only drawn inside the 
      the framebuffer.


3.  __Add text drawing to the graphics library__.

    We have also included two files
    `font.c` and `font.h`, which provide 32-bit
    (RGBA) images of standard ASCII characters. The character images are
    stored as one contiguous image in memory. The first character is '&nbsp;'
    (space), whose ASCII value is 32 (0x20). The last character is '~'
    (tilde), whose ASCII value is 127 (0x7e). The characters are a
    fixed-width font, so finding the X offset in the image involves
    subtracting 32 from the value and multiplying it by the character
    width. The underlying image was generated by using GIMP (the open
    source Photoshop), typing in the characters, and choosing a C file
    as the output format. 

    You should have read the source to `font.h` and `font.c` during lab.

    * `void gl_draw_char(int x, int y, char ch, color c)`:
      This function draws a single character `ch` with its top left
      corner at `x`, `y`. It should check that the character does not
      march off the right edge or bottom edge of the display (there
      should be no wrap-around or memory corruption).
   
    * `void gl_draw_string(int x, int y, char* str, color c)`:
      This function draws a the null-terminated string `str`
      with its top left corner at x,y. 

4.  __Console__

    Next, write a console application that acts like a terminal.
    The console will implement a function,
    `console_printf` (which takes the same arguments as printf),
    that can be used to print text on the terminal.

    The console should contain a buffer of characters

    that holds all the NROWS containing a line of text
    with NCOLS characters. If you change the characters
    in the console buffer, the screen should be automatically
    updated to display the text in the buffer.

    The console should also keep track of the current cursor position.
    When you print a character to the console, you should
    add it to the buffer at the current cursor position,
    increment the current cursor position, 
    and refresh the display.
    If you print past the end of a line,
    you should automatically wrap around to the next line of text.
    As you wrap around on the last line of text (the one displayed
    on the bottom), you should scroll the text.
    That is, you should shift all the lines up by one.
    The top line should disappear and the bottom line should contain
    the new text.

    When processing characters, interpret the following special characters:

    * `'\n'`: move to the next line and return to the beginning of the line

    * `'\r'`: return to the beginning of the line

    * `'\b'`: back space

    * `'\f'`: form feed, clear the console and set the cursor at the home position

    You should implement your console with two files,
    `console.h` and `console.c`.
    We have given you `console.h`, which contains declarations
    for the following functions which you should implement.

    * `console_init(unsigned nrows, unsigned ncols)` - Initialize the
    console with a character buffer that stores `nrows` of text
    each containing `ncols` characters. You should use the
    memory allocater you wrote in the last assignment to allocate
    space for the character buffer.

    * `console_putc(int ch)`:
    Put a single character into the console
    buffer. Implement the special processing of characters such as
    `'\n'`, `'\r'`, `'\b'`, and `'\f'`, as described above.

    * `console_printf(format, ...)`:
    Print a formatted string to the
    console. You should use the function `snprintf` that you wrote
    previously.

    * `char console_get_char( const unsigned row, unsigned col )`
    This small function simply returns the character currently at the
    given row and column in the console.

### Extensions

Extend the graphics library so that you can draw lines and triangles.
Make sure to follow the function prototypes given in `gl.h`.

This extension requires you to learn about line drawing algorithms.
A good starting point is 
[Line Drawing Algorithm](https://en.wikipedia.org/wiki/Line_drawing_algorithm).

After these functions extend your line drawing function to draw
*anti-aliased* lines

![Aliased Lines](images/pixelated.png)

![Anti-aliased Lines](images/antialiased.png)
