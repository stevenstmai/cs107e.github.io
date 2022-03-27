---
released: false
permalink: /assignments/assign3/
title: 'Assignment 3: Implement a String Formatting Library'
toc: true
---
{% comment %}
Task list to copy/paste when creating PR for this assign:

__Before releasing assign3:__
- [ ] Review writeup/starter code (instructor)
- [ ] Review consistency/completeness of grading info published to students relative to grading tests used, consider changes clarity/ease of grading (TA)
- [ ] Followup on issues from previous quarter postmortem (issue #395)

__To prep for assign3:__
- [ ]

{% endcomment %}
*Written by Pat Hanrahan and Julie Zelenski*

{% include duedate.html n=3 %}


## Goals

Libraries are critical in software development. They let you build
on existing, well-designed, and well-tested abstractions.
Many of the C standard libraries are surprisingly large. Because we copy our entire program over a slow serial line to the bootloader, we want a smaller, simpler library of just the essentials. The library you will implement supports a subset of the standard features selected for their utility and relevance to our particular needs.

A library for outputting formatted text is particularly powerful,
since printing program state is a valuable form of debugging. The standard C function to output formatted text is `printf`. The standard version of `printf` has many options and a large code size.  You will implement a
pared-down `printf` that provides just the essential core functionality. Your `printf` will be layered on a `strings` module that you will also write.
Completing this assignment will give you two new modules to add to your growing library of Raspberry Pi functions.

In addition to having extended your library with this extremely useful functionality, by implementing these
functions you will learn:

- how to decompose a complex programming problem into smaller and more manageable pieces,
- how strings and characters are represented and manipulated in C,
- how to convert C data types (numbers, pointers) to a string representation, and
- how to use the UART library shown in class to communicate with your laptop.

## Best practices
This is a difficult assignment, and will require a thoughtful plan and good development habits. Here are our strong recommendations on how to approach:

1. **Mindset**. Your skills with memory-wrangling and C pointers will grow leaps and bounds in completing this assignment. When you're done, you'll understand these topics well, but you will work hard for it and you're likely to encounter tough bugs along the way.  Bringing a growth mindset is one of your best assets. Rather than let that tricky bug get you down, instead focus on the improved understanding you will gain as you work it out. If you start to feel you are losing your mojo, reach out to us for help and encouragement.
1. **Start early**. This gives you time to think things through, to come to office hours, to re-work if your first approach isn't working out as you hoped, to pause and appreciate all that you are learning.  In contrast, getting a late start means working non-stop under the unpleasant stress of a looming deadline. Some bugs take ten minutes to resolve, others take hours, and you never know which it will be. When you're dealing with a doozy that has you has stumped, one of the best gifts you can have given yourself is time: for a break, a walk, a nap, a meal,... (and a visit to office hours!).
1. **Follow good development and debugging practice**, just like you learned in lab. Now is the time to build up your mad gdb skills. Take to heart our recommended [Strategies for Success](#strategies-for-success). This will help you complete the assignment more efficiently and with less strife.
1. **Test as you go**. Spending 10 minutes to write a test
can save you hours of debugging time later.
1. **Commit often**. If you modify your code and break it you can easily go back to a working version.

We have many quarters of experience helping students succeed on this assignment, and we know it is within your ability! But please, please, please follow our recommendations so you complete successfully and also have an enjoyable journey.

## Get starter files
To ensure that your courseware files are up to date, do a pull in the `cs107e.github.io` repo.

```console
$ cd ~/cs107e_home/cs107e.github.io
$ git pull
```

Change to your local assignments repo, switch to the `dev` branch, and update your repo with the starter code by pulling from the remote repo:

```console
$ cd ~/cs107e_home/assignments
$ git checkout dev
$ git pull --allow-unrelated-histories starter-code assign3-starter
```

The final setup step is to change the symbolic link to point `Makefile` to the `assign3/makefile`.

```console
$ cd ~/cs107e_home/assignments
$ ln -sf makefiles/assign3.makefile Makefile
```

<a name=mymodules></a>
### Use of `MY_MODULES`
Each week as you move forward, you have the option of building on your own code from the previous assignments. Open the `assign3.makefile` and read the top-level comment about the `MY_MODULES` setting used to control which modules are used when building.  In the starter makefile, `MY_MODULES` lists only the library modules for the current assignment. If you edit `assign3.makefile` to add the library modules you completed previously (e.g. `gpio.o` and `timer.o`), you will now be building on your own code instead of the reference. Using your previous modules as you move forward will further test your code and give you a jumpstart on earning the full system bonus awarded to a final assignment that uses all of your modules and none of the reference. If you encounter a problem using a previous module, you can remove it from `MY_MODULES` to instead use the reference version until you have a chance to resolve the underlying issue.

The source files added to your repo for assignment 3 are:

- `src/lib/strings.c`
  + library module for string functions
- `src/lib/printf.c`
  + library module for printf functions
- `src/tests/test_strings_printf.c`
  + test program with your unit tests for strings and printf
- `src/apps/print_pinout.c`
  + sample application that uses `printf` to display the Pi's pinout. Do not edit this program, just use it as-is.

In this rest of this writeup, we refer to these files by their basename, e.g. just `printf.c` or `test_strings_printf.c`, but keep in mind each file is located in its respective subdirectory depending on the type of source file (application, library, or test).

The `make run` target builds and runs the sample application
`build/print_pinout.bin`. You will likely only use this target at the very end as a final test of your completed work. The `make test` target builds and run the test program
`build/test_strings_printf.bin`. This test program is where you will add all of your unit tests. You will make heavy use of this target. You can run the debugger in simulator
mode on the corresponding ELF file, e.g. `arm-none-eabi-gdb build/test_strings_printf.elf`.

## Core functionality
In this section, we review the module specifications. We recommend you skim this section to get an overview but don't get mired in the minutiae just yet. Before writing any code, read the section [Strategies for success](#stragies-for-success) for a road map and advice on how to proceed. When ready to implement a particular function, come back to this section to review the nitty-gritty details.

### Strings module
Every general purpose programming language supports a string data type and operations. The string type in C is very bare bones; simply a pointer to a contiguous sequence  of characters terminated by a null character (zero, or `'\0'`). You can access individual characters using pointer or array operations and that's about it. To do more useful  things with a C-string, such as find its length, make a copy, or compare two strings, you must write functions to do so.Use the command `man string` to list the functions  from the standard C `strings` module. There are a lot of functions in the standard  library!

You will implement your own `strings` module for the Pi. The module will not
include such a large set of operations, just a few key essentials chosen for
their specific  usefulness to us.

Start by reviewing the header file for the module (available as `$CS107E/include/strings.h` or [browse strings.h here](/header#strings)). The functions exported by the `strings` module are:

- `memcpy` and `strlen` (provided to you pre-written)
- `memset`
- `strcmp`
- `strlcat`
- `strtonum`

Although our function interfaces are modeled after similarly-named functions in the standard C library, we have made some simplifications, so please read our header file carefully to ensure you are implementing only and exactly what is expected.

The choice of these particular six functions may appear eclectic, but each was selected for its utility in implementing or testing `printf`. As you implement each string function, consider how to properly use it and what it will be useful for. In particular, `strlcat` may seem oddly-structured at first glance, but its specific functionality turns out to be an ideal match for certain tasks within `printf`.

### Printf module

The functions in the `printf` module construct formatted strings in preparation
for writing those strings to a terminal or a file.

The three public functions you are to implement in `printf.c` are:
- `printf`
- `snprintf`
- `vsnprintf`
- These two private helper functions are expected to be a part of your implementation:
  - `unsigned_to_base`
  - `signed_to_base`

Review the header file (available as `$CS107E/include/printf.h` or [browse printf.h here](/header#printf)) for documentation of the public functions. The features required in your version is simplified from the standard C library version, so please read our header file carefully to ensure you are implementing only and exactly what is expected.

The printf module is not really so much about output; the work is almost entirely string manipulation. The fundamental task is to process an input string and its embedded formatting codes and expand into a fully fleshed-out output string.

#### Number to string conversion helpers

 ```c
int unsigned_to_base(char *buf, size_t bufsize,
                     unsigned int val, int base, size_t min_width);
int signed_to_base(char *buf, size_t bufsize,
                   int val, int base, size_t min_width);
 ```

These helper functions convert a numeric value to a string representation in a particular base. For example, given the integer value `126`, its string representation in base 10 is the sequence of four ASCII characters `1` `2` `6` `\0`, i.e. the string `"126"`. The string representation of `126` in base 16 would be `"7e"`.

The `val` argument is the integer value to convert. If `signed_to_base` is called with a negative value, the output string will contain a leading minus sign.

The `base` argument indicates whether the output string is to be represented in
decimal (base 10) or hexadecimal (base 16). No other bases are supported.

The `min_width` is the minimum number of characters in the output string.  If the output string contains fewer characters than `min_width`, the output string is padded with leading zeros to bring it up to length `min_width`. If the output string is already at least as long as `min_width`, the `min_width` argument is ignored. The minus sign should precede the zero padding and is included in the `min_width`.

The caller supplies the arguments `buf` and `bufsize`. `buf` is the address of the character array where the output string is to be written. `bufsize` is the size of the array. The functions must respect this size and never write more characters that fit in `buf`. If the output string would be too long, truncate to what fits, being sure to reserve one slot for the null terminator. The contents written to `buf` must be a valid, null-terminated string.

The return value is the count of characters written to `buf` if there is space to fit the entire output string. If not, it returns the count of characters that would have been written if there were space. The null terminator is not included in the count.

Some examples (`'\0'` is the null terminator):

  * `signed_to_base(buf, 20, 35, 10, 0)` writes 3 bytes into buf: `3` `5`  `\0` and returns 2.
  * `unsigned_to_base(buf, 20, 35, 16, 4)` writes 5 bytes into buf: `0` `0` `2` `3` `\0` and returns 4.
  * `signed_to_base(buf, 5, -9999, 10, 6)` writes 5 bytes into buf: `-` `0` `9` `9` `\0` and returns 6.

**Note about bufsize and memory corruption:**
You might notice that some of these parameters overlap in what they specify about the output string. For example, `bufsize` is a hard upper limit on how much space is available to store the output string, but nothing in the calling convention says that `min_width` must fit within `bufsize`. In all cases `bufsize` wins: not writing past the end of `buf` and not corrupting memory is more important than writing out the string requested by the arguments. If `bufsize` is too small to fit all of the output, even if `min_width` says you should go past it, you must truncate the output and store a null terminator in `buf[bufsize - 1]`.  Finally, `bufsize` can be zero: if so, you should not write anything to `buf`, not even a null terminator.


#### `snprintf` and family

<img src="images/snprintf.png" width="120">
```c
int snprintf(char *buf, size_t bufsize, const char *format, ... );
int vsnprintf(char *buf, size_t bufsize, const char *format, va_list args);
int printf(char *format, ... );
```
These three functions of the printf family each accept the same type of input strings and formatting codes, but differ slightly in how they are called or where the output is written.

The "formatting codes" allow combining different types of values into a single output string. Review this [C reference](http://www.cplusplus.com/reference/cstdio/printf/#example)
for sample uses of `printf`. The default `printf` writes the formatted output to your terminal; the `snprintf` variant writes the formatted output to a string buffer. In the final arrangement, the workhorse `vnprintf` will underly both `printf` and `snprintf`.

Full documentation for any standard C function is available in its man page, e.g. `man snprintf`. Bear in mind that your implementation supports a more limited set of options than the full-featured standard library version. Refer to our [printf.h](/header#printf) header file to know exactly what your version is required to support.

The ordinary characters in the input string are copied unchanged to the output string. The input string can also contain formatting codes that are placeholders for values to be inserted in the output string. For each formatting code, the requested conversion is applied to the associated argument and then written to the output string.

Your implementation must support these formatting codes:

```
 %c   single character
 %s   string
 %d   signed decimal integer (optional width)
 %x   unsigned hexadecimal integer (optional width)
 %p   pointer
 %%   output a percent sign
```

For formatting codes `%c` and `%s`, no processing is needed to "convert" characters
and strings, the character or string argument is copied as-is to the output string.

For the integer formatting codes `%d` and `%x`, the integer value is converted to a string representation using your handy `unsigned_to_base` and `signed_to_base` helper functions. The optional width such as `%03d` or `%05x`can be specified to set the minimum number of characters in the converted string. The width is a non-negative decimal number and must be specified with a leading 0. For example, `"%014x"` outputs its unsigned integer argument as a hexadecimal string of at least 14 characters (padded with zeros on the left as necessary).

The `%p` format outputs an address as a width-8 hexadecimal string prefixed with 0x, e.g. `0x20200004`.

The `snprintf`and `printf` functions take a variable number of arguments, one argument for each formatting code in the format string. To access those additional arguments, you use C's `<stdarg.h.>` interface. Read more about [Variadic functions](#varargs) below.

These functions return the number of characters written if they fit or the number of characters that would have been written if there were space.

<a name="varargs"></a>
#### Variadic functions

`printf` and `snprintf` are functions that take a variable number of arguments.
C has standardized the way to access variadic functions using the `stdarg.h` interface.
Here is an example.

```c
#include <stdarg.h>
#include <stdio.h>

int sum(int n, ...)
{
    int result = 0;
    va_list ap;

    va_start(ap, n);
    for (int i= 0; i < n; i++)
        result += va_arg(ap, int);
    va_end(ap);

    return result;
}

int main(void)
{
    printf("%d\n", sum(4, 100, 0, 5, 2) );
    printf("%d\n", sum(2, -1, 1));
    return 0;
}
```

The function `sum` has one fixed argument `n`, followed by some number of
additional arguments, indicated by the `...` in its parameter list.
For example, the call `sum(4, 100, 0, 5, 2)` contains one fixed argument, 4
(number of values to sum), and four additional arguments, 100, 0, 5, and 2.

The implementation of the `sum` function demonstrates how to use `stdarg.h`.

The variable `ap` is declared of type `va_list`.  This variable is initialized
using `va_start`, which is passed the last named argument. In this case, we
tell `va_start` that `n` is the last argument before the variable arguments
begin.

Then we loop over the `n` arguments, fetching each argument using `va_arg(ap,
type)`. In the `sum` example, the variable arguments are all of `int` type, but
the type can be different per-argument by changing what type is used in
`va_arg`. When we are done processing all of the variable arguments, we call
`va_end(ap)` to clean up after ourselves.

Note that because of obscure rules in the C standard about "[default argument
promotions](http://stackoverflow.com/questions/1255775/default-argument-promotions-in-c-function-calls)",
you cannot ask `va_arg` for the `char` type. Instead you must ask it for an
`int` and then cast the `int` to a `char`.

For additional information about `stdarg`, read the [Wikipedia page on
stdarg.h](http://en.wikipedia.org/wiki/Stdarg.h).

## Strategies for success

Having read up to here, you may feel a bit overwhelmed by all that lays before you. It is a big job, but it will be much more tractable if you break it down into manageable tasks and tackle one at a time. Developing an appropriate decomposition and identifying a good path to follow from start to finish can be tricky, so read on for our guidance on strategies that we know work well.

### Order of attack

#### 1. strings module

Definitely start here. Each string function is a small task that can be implemented and tested independently. As you write each function, brainstorm test cases that cover a range of uses. Add those tests into `test_strings_printf.c` and use `make test` to build and run the test program. Don't move on to the next function until the current one is fully vetted and debugged.

- `strcmp` is the simplest of the bunch and makes a great starting point for practice
  with string handling. The `strcmp` function is critical to all your future testing as you will later depend on to confirm the result of other string operations.
  What are some test cases you can use now to ensure `strcmp` will be robust
  and reliable when you need it?
- We provide the implementation of `memcpy`, the generic function that copies a sequence of bytes from source location to destination. The interface
  is written in terms of `void*` which means the function will accept any type of pointer and copy any type of pointee data. Because it is not valid to deference a `void*` or use in pointer arithmetic, it uses a typed pointer `char*` to access the data as an array of raw bytes. Review our given code and confirm you understand how it operates. You're now ready to write `memset`, the generic function that writes a repeated byte in a region of memory.
- Tackling `strlcat` at this point allows it to layer on the already-implemented `strlen` and `memcpy`.
- Working through `strtonum` will reinforce your understanding of the difference
  between the ASCII character '5' and the integer value 5 and what is needed to
  convert from string form to integer value. You will soon implement a similar conversion
  in the opposite direction.
- We cannot over-emphasize the __importance of [testing](#testing) as you go__.
  Attempting to implement `printf` on top of an unreliable/untested strings library is an arduous task, as you must debug all of the code simultaneously and untangle complex interactions.
  In contrast, implementing `printf` on top of a robust strings library is much
  more straightforward. Because of your thorough testing, you can be confident that the strings library does its job correctly and focus your attention on debugging only the new code being added.

Having finished the strings module and thoroughly tested it a great first milestone! You now have a collection of very useful string functions and have important lessons under your belt, such as understanding the relationship between pointers and arrays, being aware of need to take care with the null terminator, and so on.

#### 2. conversion helper functions

Start with the two `xxx_to_base` helper functions. These small but mighty operations
convert a number to a string representation (the inverse of the conversion performed
by `strtonum`).

- At first, focus on conversion to base 10 into an adequately-sized buffer.
  Postpone handling hexadecimal, minimum width and bufsize truncation until after you have the basics working.
- Pro-tip: building the string in reverse (e.g. from the least significant
  digit to the most) allows the logic to be somewhat cleaner.
- Limiting the output to the size of the destination buffer is most
  easily handled as an  afterthought. Declare a maximum-sized temporary buffer on the stack and write the digit characters into temporary. As a final step, copy characters from the temporary into the destination, truncating at bufsize if necessary.
- When ready to add support for base 16, don't copy/paste from base 10
  to create a second nearly identical conversion! Repeated code means more code to write, debug, test, and maintain; a lose-lose all around. Instead, identify how to unify into a single implementation that flexibly allows for either base.
- Similarly, you need both a signed and unsigned conversion function, but
  rather than duplicate code between the two, consider how you can unify by having  the `signed` function called the `unsigned` function.
- These helpers are going to do the heavy lifting of the number formatting for printf, so be sure to test them very thoroughly in all variations.

#### 3. Implement snprintf

You are now ready to tackle `snprintf`. The most important advice is __do not try to implement the whole gamut of snprintf functionality in one go!__ This would be an overwhelming task and will quickly lead to a mess of complicated code that is hard to debug or get right. The way to tame the complexity is to advance in small steps, continually testing as you go.

- Be sure that your `strcmp` is rock-solid. Your unit tests are likely to
  take the form of calling `snprintf` to write a formatted string into a buffer, followed by an assert that uses `strcmp` to confirm the contents written to the buffer match the expected. In order for these tests to be in any way valid, you need a working `strcmp`.
- Start by implementing `snprintf` with no support for formatting codes, it only
  outputs ordinary characters.  Test with simple examples such as
  `snprintf(buf, bufsize, "Hello, World!")`.
- Add support for the simplest formatting codes first: `%%` and `%c`. You can
  now test examples like `snprintf(buf, bufsize, "%c%c = 100%% fresh", 'C', 'S')`.
- Formatting code `%s` is up next. Be sure to remember the functions you have in
  your string module that can help. For example, a function that appends one string to another would be rather useful (hint!).
- The integer formatting codes `%d` and `%x` are the most complex
  of the bunch.  You will use your `xxx_to_base` conversion helpers, be sure they are fully working. Start with the simple conversion and after that works, then add in the optional width. When reading the width from the format string, remember that you already wrote a function that converts a string of digits to a number (hint!). It will require many test cases to verify correct handling of the integer formatting codes.
- The pointer `%p` is easy-peasy, as it is mostly just a special case of
  the `%x` you just wrote. (hint!).
- You can make the simplifying assumption that you will never be asked to construct
  an output string of length greater than 1024 characters (regardless of the size of the destination buffer). `snprintf` can allocate a temporary buffer of this maximum size on the stack, write the full output string to the temporary, and afterward copy the characters that fit from the temporary buffer into the final destination. This is a tidy way to handle truncating to fit the destination size.

Achieving a working `snprintf` is the big hill to get over in this assignment. Once you have that, all that remains is re-factoring and layering. You are in the homestretch!

#### 4. Refactor into `vsnprintf`

```c
int vsnprintf(char *buf, size_t bufsize, const char *format, va_list args);
```

The `printf` function needs the same functionality as `snprintf`. However
since `snprintf` takes a variable number of arguments, you cannot call it directly from `printf`.  You must create a shared helper function `vsnprintf` (that takes a `va_list` parameter), which you can then call from both `snprintf` and `printf`. Refactoring means moving most of your `snprintf` code into `vsnprintf` and then
changing `snprintf` to call `vsnprintf`. Once you have completed this refactor,
confirm you are still passing all of your previous tests.

#### 5. Implement `printf`
Adding `printf` is a piece of cake. It declares a stack array of the maximum output length (1024), calls `vsnprintf` to fill that array with the formatted output string, and hands the string over to `uart_putstring`. Having thoroughly tested `snprintf`/`vsnprintf`,
you will not likely need many new tests for `printf`, since it is built on the same substrate that you have already confirmed correct.

It is time 🕰 for a serious Happy Dance 🙌 and an epic 🎼 that celebrates your amazing feats! You did it! 🏆 We hope you will enjoy the fruit 🍎 of your labors 💪 for a long time to come!


<a name="testing"></a>
### Testing advice
Students who struggled in the past generally wrote too much code before testing it. Instead you want to approach the work by dividing in tiny increments, making a small, testable improvement each time. If the latest changes don't work, you'll know exactly where to look for the mistake. This strategy will save you a lot of time and heartache.
To quote Dawson Engler, Systems Programmer Extraordinaire:

> __Engler’s theorem of epsilon-steps__ Given a working system _W_ and a change _c_,  as _c_ → ε  the time _T_ it takes to figure out why _W_ + _c_ doesn’t work goes to 0 (_T_ → 0).
{: .callout-info}

After taking each epsilon-step in your code, immediately turn your attention to
testing and debugging it. What test case can you add to `test_strings_printf.c`
to confirm that the code you just added is working correctly? It may require multiple test cases to get at different parts of the behavior. Add those tests now and don't move on until you pass them all.

Never delete a test! Sometimes a later change will cause a test that was previously passing to backslide. If you have removed or commented out the test, you won't realize the bug has resurfaced. Instead, accumulate all tests in `test_strings_printf.c` and keep them active. Every subsequent run will re-validate against the entire test suite and alert you to any regression.

Review the function specifications in the `strings.h` and `printf.h` header files and be sure that your test cases have full coverage of the specified behavior, including any edge cases or required error handling. If your own testing gets there ahead
of the autograder, you can find and fix your bugs before submitting to its rigorous scrutiny.

In `test_strings_printf.c`, we want to see a comprehensive test suite
that exercises each function in the strings module and all formatting options mix-and-match for printf and variants. There is a lot of ground to cover! Grading will include an evaluation of the effectiveness of your tests, along with our feedback to help you to develop and refine this critical skill.

Our specifications make some simplifying assumptions relative to the standard library. Your functions need only handle calls that are valid according to our assumptions: e.g. exactly and only these formatting codes, base is always be 10 or 16, the width specified must begin with a zero, the format string
is well-formed and so on. You do not have to detect/handle/reject calls that violate these assumptions. We will not test on such inputs and your tests do not need to consider these cases.

### Debugging advice
One unfortunate circularity with trying to test printf is the lack of a working
printf to help you debug.  Here are a couple of strategies you may want to consider:

- __Use the debugger__! Run under gdb in simulation mode and use gdb commands to
  step and print variables to observe your program's operation. We strongly encourage you to invest in building up your gdb chops now -- this investment will really pay off! Stay mindful of the differences between the simulator and the actual Pi. (Review [Exercise 4 of Lab 3](/labs/lab3/#4d-differences-under-simulation) for a refresher)
<a name="gdbinit">
    * You run the debugger on the `.elf` version of the program you wish to debug. Always start gdb from the __top-level directory__ of your assignments repo and access the elf file in the `build` subdirectory:
    ```console?prompt=(gdb),#
    # cd ~/cs107e_home/assignments
    # arm-none-eabi-gdb build/test_strings_printf.elf
    GNU gdb (GDB) 9.2
    ... blah blah blah...
    (gdb)
    ```
    * If the program you are debugging attempts to access the uart peripheral, be sure your gdb is auto-loading the `.gdbinit` configuration file we provide that fakes a uart for gdb. Our provided `.gdbinit` file is at the top-level of your assignments repo. Once you are inside gdb, confirm that it has been auto-loaded by looking for our special breakpoint:
    ```console?prompt=(gdb),#
    (gdb) info break
    Num     Type           Disp Enb Address    What
    1   breakpoint     keep y   0x00008bf4 in uart_putchar at uart.c:118
        silent
        printf "%c", $r0
        return
        cont
    ```
    This breakpoint intercepts a character intended to output on uart and echoes it manually. Without this bit of trickery, a program that attempts to output to the uart will stall or otherwise misbehave when accessing the non-existent peripheral in the gdb simulator.

    > __Does your gdb get stuck when your program tries to print output?__  The gdb simulator does not emulate the peripherals (no gpio, no timer, no uart, etc.) so a program that attempts to use the uart will be DOA without the help of our `.gdbinit` file. Re-read the instructions above. If your gdb settings disable auto-load, follow the instructions in our [gdb guide](/guides/gdb#autoload) to allow it.
    {: .callout-warning}
- __Liberal use of `assert()` tests__. For example, you can test the output written
  by `signed_to_base` matches the expected output by asserting the two strings
  `strcmp` as equal. Note that the version of `assert` from assign3 forward calls  `uart_putstring` to print out details (i.e. line number, failed expression), so you are no longer limited to interpreting red and green smoke signals.

- **Compare to reference.** The `string` and `printf` functions are a part of the C standard library, available in any C compiler (non-bare-metal). If you are not sure of the expected behavior for a particular call, try it on your local compiler, or do a quick test in this handy [online C environment (Rextester)](https://rextester.com/l/c_online_compiler_gcc ).

## Extension: disassembler
After completing printf, there may not be much bandwidth left for further explorations, but we think this extension is particularly neat and hope we can inspire a few of you to go for it!

The extension is to add a new custom formatting code to your shiny new `printf` that converts a binary-encoded instruction into human-readable assembly. This effectively adds a disassemble operation to `printf` - wow!  Here is a diagram of the bitwise breakdown for a data processing
instruction:

![data processing instruction](images/data_processing.png)

Reading from left to right, the upper four `cond` bits indicate conditional execution, the next three bits are `000` indicate this is a data processing instruction with an immediate operand 2, the four `opcode` bits determine which kind of operation (add, subtract, etc), the `S` bit determines whether the flags are set, and so on.

In lecture, Pat asked you to play the role of _assembler_ by translating an instruction  such as  `add r3, r4, r5` into `e0843005`. The reverse process is a _disassembler_  which picks apart the bits of the encoded instruction `e0843005` to produce the output `add r3, r4, r5`.

Use the custom formatting code `%pI` which expects a corresponding argument of "pointer to instruction". There is no "instruction" type in C; use a pointee type of `unsigned int` to read a binary-encoded instruction from memory. The instructions for all the code in the currently executing program are stored in memory starting at address `0x8000`. If you print the instruction at that address and move upwards in memory, you can disassemble the entire program!

Here is a sample use of `%pI`:

```c
unsigned int add = 0xe0843005;              // manual binary-encoded instruction
unsigned int *first = (unsigned int*)0x8000; // address of instruction in memory

printf("Encoded instruction %x disassembles to %pI\n", add, &add);
printf("Encoded instruction %x disassembles to %pI\n", *first, first);
```
The output of the above code is:
```console?prompt=none
Encoded instruction e0843005 disassembles to add r3, r4, r5
Encoded instruction e3a0d302 disassembles to mov sp, #134217728
```

You _could_ use your bit-masking superpowers to pick apart an encoded instruction but a simpler way is to define a C bitfield. In the starter file `printf.c` we included some code that demonstrates sample use of a bitfield to get you started.

To learn more about the instruction encoding, refer to the [ARM ISA documentation](/readings/armisa.pdf#page=2) and this
[ARM guide from USCD](https://cseweb.ucsd.edu/~ricko/CSE30/ARM_Translation_Guide.pdf).

Your extension should be capable of decoding the most common variants of the data processing and branch instructions. The ARM instruction set has a remarkably regular encoding, so you can catch a good chunk of all instructions with just a few cases. If you want to get fancier, try decoding load/store and load/store multiple (i.e. push and pop). Don't worry about making special cases for oddballs. For any instructions you don't decode, simply print the encoded value. Make sure that the output of your disassembler has the format `instr dst, op1, op2`.

There is a unit test in the `test_strings_printf.c` that demonstrates sample disassemble use.  To see how good a job your disassembler is doing, compare your output to the result from gdb's tools.  In `gdb`, you can disassemble the single instruction at an address with the `x/i` command or dump a sequence of instructions using the `disassemble` command:

```console?prompt=(gdb)
130     const unsigned int add = 0xe0843005;
(gdb) x/i &add
   0x7ffffcc: add r3, r4, r5
(gdb) disassemble main
Dump of assembler code for function main:
   0x000086b0 <+0>: push  {r4, lr}
   0x000086b4 <+4>: sub sp, sp, #8, 0
   0x000086b8 <+8>: bl  0x9454 <uart_init>
   0x000086bc <+12>:  ldr r0, [pc, #128]  ; 0x8744 <main+148>
```

You just wrote a program that dissects itself from the inside -- how meta and awesome is that! We will offer more credit on this extension as it is more challenging than  the previous ones; a great implementation deserves to be generously rewarded!🎖

## Submitting

The deliverables for `assign3-submission` are:

+ implementations of the `strings.c` and `printf.c` library modules
- comprehensive tests for both modules in `test_strings_printf.c`
- `assign3-readme.md` (possibly empty)

Submit the finished version of your assignment by tagging `assign3-submission` and ensuring you have an open pull request. The steps to follow are given in the [Assignment 0 writeup](/assignments/assign0/#submit).
  
As time permits, you are encouraged to revisit code from previous assignments and submit fixes for any issues that are marked "Resolvable".  To resubmit, commit your changes, tag `assign2-submission-updated` (`assignN` where `N` is the assignment you are resubmitting) and push. This tag signals that we should re-run the unit tests and update your issue lists to show new successes.  Most unit tests on library modules are eligible for resubmit, manual tests and extensions are not.

## Grading

To grade this assignment, we will:

- Verify that your project builds correctly, with no warnings
- Run automated tests on your `strings` and `printf` modules
- Go over the unit tests you added to `test_strings_printf.c` and evaluate them for
  thoughtfulness and completeness in coverage.
- Review your code and provide feedback on your design and style choices.

Our highest priority tests will focus on the essential functionality of your library modules:

  - strings
    + correct behavior according to spec
    + all strings properly null-terminated, buffer size respected
  - printf
    * correct behavior according to spec
    * format codes `%c`, `%s`, `%d`, `%x`, `%p`
    + all strings properly null-terminated, buffer size respected


The additional tests of lower priority will examine less critical features, edge cases, and robustness. Make sure you thoroughly tested on a wide variety of scenarios!

