---
released: true
permalink: /labs/lab4/
title: 'Lab 4: Linked and Loaded'
toc: true
readings: |
  [Prelab](/labs/lab4/#prelab-preparation) to prep before lab.
---
{% comment %}
Task list to copy/paste when creating PR for this lab:

__Before releasing lab4:__
- [ ] Review writeup/code/checkin questions (instructor)
- [ ] Walk through (SL)
- [ ] Followup on issues from previous quarter postmortem (issue #333)

__To prep for lab4:__
- [ ] Make copies memory diagrams (ideally in color if possible) to hand out in lab

{% endcomment %}

*Lab written by Pat Hanrahan and Julie Zelenski*

## Goals

During this lab you will:

- Understand how executing programs are laid out in memory, 
  including the organization of stack frames.
- Explore the stack and heap in preparation for assignment 4.
- Experiment with the linker `ld`, with the goal of understanding what is in
  an object (ELF) file by using `nm`, and how object files are combined to produce an executable.

## Prelab preparation
To prepare for lab, do the following: 

- Pull the latest version of the `cs107e.github.io` courseware repository.
- Clone the lab repository `https://github.com/cs107e/lab4`. 
- Read this [recap of stack frames and the APCS full frame](/lectures/Memory/stack_notes) from Monday's lecture. 
- Review the example program we will use in the stack exercise [code/simple/simple.c](code/simple/simple.c) and look over the [memory diagram](images/stack_abs.html) of the program mid-execution. You will examine the diagram in more detail in lab.

## Lab exercises
<a name="stack"></a>
### 1. Stack

Change to the directory `lab4/code/simple`.  This is a simple example program that uses the stack for function calls and local variables. We will use this program to study management of stack frames. Have a printed copy of the program's [memory diagram](images/stack_abs.html) handy for making notes.

Run `simple.elf` under the gdb simulator. Disassemble the `abs` function.

```console?prompt=(gdb)
(gdb) disass abs
Dump of assembler code for function abs:
   0x00008010 <+0>: mov r12, sp
   0x00008014 <+4>: push  {r11, r12, lr, pc}
   0x00008018 <+8>: sub r11, r12, #4, 0
   0x0000801c <+12>:  cmp r0, #0, 0
   0x00008020 <+16>:  rsblt r0, r0, #0, 0
   0x00008024 <+20>:  sub sp, r11, #12, 0
   0x00008028 <+24>:  ldm sp, {r11, sp, lr}
   0x0000802c <+28>:  bx  lr
End of assembler dump.
```

We are going to drill down into these eight instructions. When entering a function, the first three instructions set up the APCS frame. These instructions are called the function _prolog_.  The frame is torn down by the final instructions at the end called the function _epilog_. The structure of the prolog and epilog is basically the same for all C functions. The instructions in the middle are the _body_ of the function and they differ based on the function's operation.

#### Prolog and epilog
Put your heads together with your tablemates and very carefully trace through instructions in the prolog and epilog. Mark up your copy of the memory diagram and relate to the action of the instructions.  Below are some issues to note and questions to discuss as you work through it.

__Function prolog__:
- The first three instructions (`<+0>, <+4>, <+8>`) are the function _prolog_.  These instructions configure the frame for the function that was just entered.
- Side note: register `r11` is used as the frame pointer `fp`. The disassembly in gdb refers to `r11`, while an objdump listing calls it `fp`. The two are completely synonymous, so don't let that trip you up.
- The first instruction of the prolog copies `sp` to `r12` before then pushing `r12` in the next instruction. This dance may seems roundabout, but is unavoidable. Do you have a guess why? (Hint: attempting to use value of `sp` at same time push instruction is changing `sp` seems possibly problematic...)
- After pushing the four registers, to what location does `sp` now point? 
- The third instruction of the prolog is used to set `fp` to "anchor" the frame. After executing this instruction, where does `fp` point?

__Function body__:
- The middle two instructions  (`<+12>, <+16>`) are the function body.  
- Work out how these instructions do the job of the `abs` function. Where does it read the value of `v` from?  Where does it write the return value?

__Function epilog__:
- The final three instructions (`<+20>, <+24>, <+28>`) are the function _epilog_. These instructions tear down the stack frame and restore caller-owned registers before returning to the caller. 
- The first instruction of the epilog changes the `sp`. To what location does `sp` point after executing that instruction?
- The `ldm` instruction ("load multiple") reads a sequence of words from memory starting at a base address and copies the words into the named registers. `pop` is an alias for a `ldm` that also does an automatic adjustment the base address as a side effect (i.e. reads the word and changes the `sp` to "remove" it from the stack) . This `ldm` instruction reads three words in memory starting at `sp` and copies those values into the registers `r11`, `sp`, and `lr`.  This instructions restores those three registers to the value they had at time of function entry.  
- The fourth value that was pushed is not restored into the register `pc`.  Why is it important to __not__ restore the value of the `pc` to the value it had on entry?  
- How the values are removed from the stack is quite subtle. Because it is not using `pop`, there is no auto adjustment of `sp`.  However, one of the effect of this `ldm` is to reload `sp` with the saved value it had at time of function entry, thus restoring `sp` to where it started and effectively removing any values that were pushed.  Tricky!
- The final instruction of `abs` is the branch exchange that returns control
to the caller. Who is the caller of `abs`? What is the address of the 
instruction in the caller that will be executed when `abs` returns?  Which registers are changed when the `bx` instruction executes?

Relate your understanding of the stack to the [memory diagram](images/stack_abs.html). The diagram shows the entire address space of the `simple`
program, including the text, data, and stack segments.  Use the diagram to confirm your understanding of how the stack operates and what is stored where in the address space. It may also help to run gdb on the program, step to the same point in execution and using the commands `backtrace` and `info frame` to examine stack frames and `disassemble` to view the assembly instructions and relate those observations to the diagram.

The diagram contains a lot of details, but if you take the time to closely inspect it, you will gain a more complete understanding of the relationship between the contents of memory, registers, and the executing program.   Go over it with your tablemates and ask questions of each other until everyone has a clear picture of how memory is laid out and how stack frames are managed.  

#### Local variables
Let's look at one other function, `make_array`. This function store some local variables in its stack frame, 
so it looks like a little bit different from the standard frame. Disassemble `make_array` and trace through its assembly instructions. Sketch a picture of its stack frame as you
go.

- After the instructions for the standard prolog, what additional instruction makes space for the array local variable?
- How are the contents for the array initialized (or not)?
- In the body of the function, the array elements stored on the stack are accessed `fp`-relative.  What is the relative offset from the `fp` to the base of the array? How can you determine that from reading the assembly instructions?
- If the function erroneously tried to write to an index past the end of the allocated array, what data would be corrupted?  What kind of consequence might result from this error?

#### Solving a stack mystery!
Your newfound understanding of how the stack is managed is a neat superpower that you can now test out. Here is another [memory diagram](images/stack_mystery.html) of the simple program stopped somewhere else in its execution. In this diagram, the stack is not annotated with labels and color-coded frames as before. The stack memory looks to be a inscrutable jumble of hex numbers.  However, the current value of `fp` and `sp` are marked. How can you use these anchors to get a foothold to the stack frame of the currently executing function? How can you then work backwards from there to the frame of the caller and its caller and so on? Manually unwind and annotate the stack memory with labels to identify each stack frame and its contents. You have just produced your first backtrace! Show off your annotated diagram to us![^1] 

### 2. Heap

Change to the directory `lab4/code/heapclient` to begin your foray in heap allocation.
So far we have stored our data either as local variables on the stack or global variables in the data segment. The functions `malloc` and `free`  offer another option, this one with more precise control of the size and lifetime and greater versatility at runtime.

Study the program `heapclient.c`. The `tokenize` function is used to 
dissect a string into a sequence of space-separated tokens. The function calls on the not-yet-implemented function `char *strndup(const char *src, size_t n)` to make a copy of each token. The intended behavior of `strndup` is to return a new string containing the first `n` characters of the `src` string.

Talk over with your partner why it would not be correct for `strndup` to declare a local array variable in its stack frame to store the new string.  When a function exits, its stack frame is deallocated and the memory is recycled for use by the next function call.  What would be the consequence if `strndup` mistakenly returns a pointer to memory contained within its to-be-deallocated stack frame?

Instead `strndup` must allocate space from the heap, so that the data can persist after the function exits. Edit `strndup` to use a call to `malloc` to request the necessary number of bytes. How many total bytes of space are needed to store a string with `n` characters?  

Now that you have the necessary memory set aside, what function from the `strings` module can you call to copy the first `n` characters from the `src` string to the new memory?

What is the final step you must take to complete the new string? (Hint: how is the end of a string marked?)

Once you have completed your implementation of `strndup` to make a proper heap copy of the string, build and run the program to verify your code is correct.

Unlike stack and global memory, which is automatically deallocated on your behalf, you must explicitly free dynamic memory when you are done with it. For the finishing touch, edit `main` to add the necessary calls to `free` to properly deallocate all of the heap memory it used. You're ready for this check-in question.[^2]

### 3. Linking and memmap

In this exercise, you will repeat some of the live coding demonstrations shown in the lecture on linking and loading.

Let's first review some terminology. An _object file_ (also called an .o file or a relocatable) is the result of compiling and assembling a single source file. An object file is on its way to becoming a runnable program, but it's not finished. The linker takes over from there to combine the object file with  additional object files and libraries. The linker is responsible for resolving inter-module references and relocating symbols to their final location. The output of the linker is an _executable_ file, this represents a full program that is ready to run.

#### Symbols in object files

Change to the `code/linking` directory of `lab4`. Read over the code in the files `start.s` and `cstart.c` and then build the object files `start.o` and `cstart.o`:

```console
$ make start.o cstart.o
```
The tool `nm` lists the symbols in an object file. Each function, variable, and constant declared at the top-level in the module is a _symbol_. Try `nm` out now:

```console
$ arm-none-eabi-nm -n start.o cstart.o
```

What symbols are listed for `start.o`? For `cstart.o`? How do the symbols listed correspond to the functions defined in the source files?
What is the significance of the number shown in the left column for each symbol?
What do each of the single letters `T`, `U`, and `t` in the second column mean? 

Skim the man page to learn a little bit about this tool and the variety of symbol types:
```console
$ man arm-none-eabi-nm
```
Our modules will typically contain text (code) symbols and data symbols (with variants common, uninitialized, read-only). What is the significance of upper versus lowercase for the symbol type? What does the `-n` flag do? What about the `-l` flag? Try adding it to your call to `arm-none-eabi-nm` and see what happens.

Let's look at the symbols in a more complex object file. Review the variable definitions in the source file `linking.c`. Build `linking.o` and view its symbol list:
```console
$ make linking.o
$ arm-none-eabi-nm -n linking.o
```
How many symbols are listed for `linking.o`?  What do the single letter symbols `D`, `R`, `C`, and `b` mean in the `nm` output?

Can you match each function/variable definition in `linking.c` to its symbol in the `nm` output? A few of the variables defined seem to have been completely optimized out, what made that possible? None of the parameters or stack-local variables in `linking.c` are listed as symbols, why not?

What type and size of symbol would correspond to an array definition such as  `const int[5]`? See for yourself by uncommenting the declaration on line 13 of `linking.c`, rebuild and view `arm-none-eabi-nm -S linking.o`.

#### Symbols in an executable

After compiling each individual source file into an object file, the final build step is to link the object files and libraries into a program executable. The three object files we examined above are linked together in `linking.elf`.  Use `make linking.elf` to perform the link step and then use `nm` to look at the symbols in the final executable.

```console
$ make linking.elf
$ arm-none-eabi-nm -n linking.elf
```
The executable contains the union of the symbols in the three object files. What is the order of the symbols in the executable? How have the symbol addresses changed during the link process?
Do any undefined symbols remain?
What happened to the symbols previously marked `C`?

#### Resolution and relocation

The Makefile in this project has additional action that creates a `.list` file for each build step. These listing files contain the disassembly of the compiled module.  Let's look into those listings to get a better understanding of how symbols are resolved and relocated by the linker.

```console?prompt=$
$ cat start.o.list

00000000 <_start>:
       0:   mov     sp, #134217728  ; 0x8000000
       4:   mov     fp, #0
       8:   bl      0 <_cstart>

0000000c <hang>:
       c:   b       c <hang>
```

The third instruction is where `_start` calls `_cstart`. This *branch and link* instruction `bl` has 0 at the target destination address.
This target is labeled `<_cstart>`, but 0 doesn't seem quite right. In this module, 0 is the address of `_start`.  Hmm, most curious...

The listing for `linking.elf` begins with the instructions for `_start` but this is _after_ linking. What do you notice that is different now?

```console?prompt=$
$ cat linking.elf.list
 00008000 <_start>:
     8000:       mov     sp, #134217728  ; 0x8000000
     8004:       mov     fp, #0
     8008:       bl      80b8 <_cstart>

 0000800c <hang>:
     800c:       b       800c <hang>
 ...

 000080b8 <_cstart>:
     80b8:       mov     ip, sp
 ...
```

First note that after linking, the addresses (in leftmost column) start at `0x8000` and increase from there. These addresses indicate the location of each instruction in the final executable. Can you work out how each symbol's final address relate to its original offset in the object file?  The process of gathering all symbols from the modules and laying out into one combined package at their final locations is called _relocation_. The linker uses the [memmap](#memmap) to determine how and where to layout the symbols.

In the listing `start.o.list`, the destination address for the branch to `_cstart` was 0.  In the listing `linking.elf.list`, the destination address has been changed to `0x80b8`.  Read further down in the listing to see what is at address `0x80b8`. Makes sense?

In the listing for `linking.o.list` (pre-link), find the instructions for the function `main`. It contains three `bl` instructions, one is a function call to a function defined in this module (`sum`), the other two call functions outside this module (`uart_init` and `printf`).  The call within module has the function offset as destination address, but the calls to outside the module have destination address 0, used as a placeholder. In the listing `linking.elf.list` (post-link), find those same instructions for `main` and you will see all destination addresses are now filled in with the final location of the symbol.

The compiler processes only a single module (file) at a time and thus it can only resolve references to symbols that appear within the module currently being compiled. The linker runs in a subsequent pass to perform tasks that require joining across modules. The process of filling in the missing placeholder addresses with the final symbol locations is known as _resolution_.

The linker is given a list of object files to process and it will combine the files together and arrange symbols into their final locations (relocation) and resolve cross-module references (resolution).

Answer the check-in question on linking.[^3]

#### Memmap

As part of the relocation process, the linker places all of the symbols into their final location. You supply a _memory map_ to the linker to indicate the layout of the sections. Let's look into this file to better understand its purpose and function.

Change to the `lab4/code/linking` directory and use `nm` to see the final locations of all the symbols in the executable.

```console
$ arm-none-eabi-nm -n linking.elf
```

Note how all symbols of a given type (text, data, rodata, etc.) are grouped together into one section.

Now open the file `memmap` in your text editor. `memmap` is a _linker script_, which tells the linker how to lay out the sections in the final executable file.

- Do you see how the `memmap` linker script specifies how sections from
  individual files are to be combined?

- One of the purposes of `memmap` is to ensure that the symbol `_start`
  appears first in the executable file. Why is it critical that this 
  function be first? How does `memmap` specify where `_start`
  should be placed?

- Another purpose of `memmap` is to setup block storage of uninitialized
  variables. Look for the symbols `__bss_start__` and
  `__bss_end__`. Where are those symbols placed? In a C program, uninitialized global
  variables are to be set to 0 at program start. How does `_cstart` use the bss start/end symbols to
  zero the unset variables?

Our projects all use this same `memmap`, which defines a correct layout for a standard bare-metal C program for the Pi. You are unlikely to need to edit or customize it.  However, it is still worth taking a look at some basic [documentation on linker scripts](https://sourceware.org/binutils/docs-2.21/ld/Scripts.html).

## Check in with TA
<a name="checkin"></a>
Each question below is a diagnostic question for a lab section. Test your understanding by answering the corresponding question as you finish an exercise. We encourage you to check in with a TA after
completing a section or two, while the material is still fresh in your mind.

[^1]: Show us your marked up copy of the mystery diagram.
[^2]: How should the number of `free` calls relate to the number of `malloc` calls in a correctly-written program that uses heap allocation?
[^3]: Compare the symbol list from `nm linking.o` to `nm linking.elf`. How do the symbol addresses from an object file differ from the addresses in the linked executable?  How does the instruction `bl _cstart` change after linking?
