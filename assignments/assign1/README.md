---
released: true
permalink: /assignments/assign1/
title: "Assignment 1: Implement a Larson Scanner"
toc: true
---

{% comment %}
Task list to copy/paste when creating PR:

**Before releasing assign1:**

- [ ] Review writeup/starter code (instructor)
- [ ] Review consistency/completeness of grading info published to students relative to grading tests used, consider changes clarity/ease of grading (TA)
- [ ] Followup on issues from previous quarter postmortem (issue #)

**To prep for assign1:**

- [ ]

{% endcomment %}

![Knight Rider Car](images/knightrider.jpg){: style="float:right;"}

_Written by Pat Hanrahan_

## {% include duedate.html n=1 %}

[Glen A. Larson](http://en.wikipedia.org/wiki/Glen_A._Larson),
the man responsible for producing
the original
[Battlestar Galactica](http://en.wikipedia.org/wiki/Battlestar_Galactica)
and
[Knight Rider](http://en.wikipedia.org/wiki/Knight_Rider_%281982_TV_series%29)
television series,
often used simple lighting effects in his shows.
One famous example is a scanner
that consists of a set of red LEDs that scan back and forth.
The front of the Knight Rider car had a scanner.

Watch this video tribute to Glen Larson.
How many times does the scanner pattern appear?

<iframe width="500" height="281" src="https://www.youtube-nocookie.com/embed/hDUoyeMLxqM?modestbranding=1" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

---

The Larson scanner demoed in this video is a [DIY kit from Evil Mad Scientist Labs](https://shop.evilmadscientist.com/productsmenu/tinykitlist/152-scanner).

<iframe width="350" height="196" src="https://www.youtube-nocookie.com/embed/alW5zHiF6_0?modestbranding=1&end=10&version=3&loop=1&playlist=alW5zHiF6_0" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

## Goals

When you're done with this assignment, you should

- understand ARM assembly language,
- feel fluent with the ARM cross-development tools,
- know how to use breadboards and use LEDs,
- and be able to program general-purpose input/output (GPIO) pins.

## How do assignments work?

The course follows a weekly cadence where material is introduced in the Friday-Monday lectures and lab follows up with hands-on guided practice so that you're ready to tackle the week's assignment which is released after lab. Completing each assignment will solidify your understanding of the week's topics. In addition to being a satisfying accomplishment on its own, the code you write each week contributes a building block to your library of Pi features. Completing this system is an accomplishment of which you will be immensely proud!

Each assignment is structured into a core/basic part and one or more proposed extensions. Completing the core part is required for all students; the extensions are the optional "stretch goals" for those students aiming to go further. We encourage everyone to try the extensions; they're a great way to challenge yourself and solidify your understanding.

> **YEAH = Your Early Assignment Help**  Each Thursday we'll hold a YEAH session as a kickoff for the week's assignment and more quality time with the CS107e family! We can answer your questions, pump you up for the neat things you'll be learning, and facilitate a group brainstorm on practices for success. YEAH Hours will take place Thursday 4-5pm in ohyay. Everyone welcome!
{: .callout-success}

## Core functionality: simple scan pattern

This assignment involves modifying the blink program showed in class.
`blink.s` is an ARM assembly language program that blinks a single
LED. To implement a scanner, you will need to control at least 4
LEDs. Using arithmetic and loops, your assembly program changes which
LED is lit to show a scanner pattern.

### 1. Wire up your breadboard

The scanner should have a row of 4 LEDs. If you feel ambitious and want to make more interesting patterns, wire up 8 LEDs. Validate your breadboard wiring by testing that each LED lights up when powered. 

### 2. Connect the LEDs to GPIO 20-23

The leftmost LED in your scanner should be connected to GPIO 20 of your Raspberry Pi, the second from the left to GPIO 21, and so on, such that the rightmost LED in your scanner is connected to GPIO 23 (or GPIO 27 if using 8 LEDs). Refer to the diagram of the [pinout](/guides/images/pinout.pdf) to map each GPIO to the physical pin so that you correctly wire up the connections.

We hope you share our appreciation for  breadboarding as art and craftsmanship! Secure your components close to the breadboard, snipping the ends to fit and using your pliers to make neat bends. Not only does this look nice, it will be more robust to being handled. 

Show off your creation by taking a picture of your larson scanner hardware setup and commit it to your repo with the name `larson_board.jpg` (or .png). Don't forget to `git add` the file!

### 3. Get starter files

Before starting each new assignment, first do a `git pull` in your copy of the `cs107e.github.io` repository to ensure your courseware files are up to date.

```console
$ cd ~/cs107e_home/cs107e.github.io
$ git pull
```

Next, update your local assignments repo with the latest starter code for the assignments by pulling any changes from the remote repo:

```console
$ cd ~/cs107e_home/assignments
$ git checkout dev
$ git pull --allow-unrelated-histories starter-code assign1-starter
```

After these commands, your assignments repo is on `dev` branch and all files are up to date. Use `ls` to see the files now in your repo.

At the top level there are two subdirectories `src` and `makefiles`. 
Source files will be stored in `src` directory, which itself is further divided into
into subdirectories based on the type of source file. For assign1, the only subdirectory is `src/apps` which holds the files for programs that run on the Pi. In later assignments, there will be additional subdirectories for library modules and test programs.

In the directory `src/apps` is the file `larson.s`. This is the file you will edit to implement your Larson scanner.

The `makefiles` directory contains the rules for how to build the programs. You can think of a makefile as a recipe that contains the
steps for how to build your code.  Each assignment will be distributed with a makefile named `assignN.makefile`.

To build a program, we use the `make` tool, which looks for a file named `Makefile` in the current directory.  But there is no `Makefile` here!  When working on assign1, you will want to use the `assign1.makefile`, but later you will use `assign2.makefile` and so on.  To easily switch between them, we will use a symbolic link (also called a soft link)
that will point `Makefile` to the current assignment makefile. The `ln` command is used to create a symbolic link. Use the commands below to point to the `assign1.makefile`:

```console
$ cd ~/cs107e_home/assignments
$ ln -sf makefiles/assign1.makefile Makefile
$ ls -l Makefile
lrwx------  1 julie  26 Jan 19 21:47 Makefile@ -> makefiles/assign1.makefile
```

The `ln` created a new file named `Makefile` that points to `makefiles/assign1.makefile`. Neat!  Now `make` will follow the `Makefile` link to use the `assign1.makefile`.  Try it now using the commands shown below; `make` to build the program and `make run` to run the program on your Pi. Using the `assign1.makefile`, these commands build and run the program from the file `src/larson.s`.

```console
$ make
mkdir -p build
arm-none-eabi-as src/apps/larson.s -o build/larson.o
arm-none-eabi-objcopy build/larson.o -O binary build/larson.bin
$ make run
rpi-run.py build/bin/larson.bin
```

If you're wondering how `make` and makefiles work, sit tight. We have an lab exercise on makefiles coming up lab2.

### 4. Configure scanner GPIOs

The starter program is a copy of the `blink.s` you studied in lab 1. This program configures the single pin GPIO 20 and enters an infinite loop to set and clear that pin. Carefully review this code and be sure you understand how it accomplishes its tasks. Ask questions if anything is unclear! Your job is to modify this program to instead blink the scanner sequence.

A good first step is to extend the initialization code to configure all of the GPIOs your scanner uses, not just GPIO 20. Refer to section 6 of the [Broadcom ARM Peripheral](/readings/BCM2835-ARM-Peripherals.pdf) for the details on the GPIO registers.

Be sure to verify that your configuration code is correct. You can test an individual pin by changing the existing loop to blink GPIO 21 or GPIO 22 and so on instead of GPIO 20. Once you have verified that all pins are properly configured, you're now ready to tackle changing the loop body to blink the pins in the scanner sequence.

One strong recommendation from us is that you make a habit of **regular git commits**. A commit takes a snapshot of your changes and records them into your repository history. This takes a snapshot that allows you to later return to this version if need be. When should you commit? Any time you hit an "interesting" point in your development: after achieving a milestone, before stopping for break, after fixing a bug, before embarking on an exploratory path, and so on. Be sure to include a descriptive message with each commit. Following up a commit with `git push` will sync your local repository to your GitHub remote repository.

### 5. Generate scanner pattern

The loop will scan back and forth from the GPIO 20 LED to the GPIO 23 LED. Each iteration of the loop still turns on/off one GPIO, but instead of blinking the same GPIO each time, it will blink the next GPIO pin in sequence.

The scanning pattern should move smoothly back and forth. In particular, exactly one LED should be on at any given time, so the light appears to be "moving" between LEDs. Make sure you handle the left and right
ends properly (that is, the leftmost and rightmost LED should be each
on for the same amount of time that a middle LED would be on). The scanning frequency should be around 1Hz (that is, the light should bounce back and force about once per second).

Here is a short video of our 8-LED scanner in action:

<iframe width="420" height="236" src="https://www.youtube-nocookie.com/embed/vhDcb7lxCF4?modestbranding=1&version=3&loop=1&playlist=vhDcb7lxCF4" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>


Writing clean, readable assembly code is a challenge. Commenting is essential!  
Be sure to choose good label names and add named constants using `.equ` to aid readability.
Because you don't know how to write functions yet in assembly, you'll need to
write your program without the aid of this useful abstraction. 

A branch instruction is the assembly equivalent of a goto (a practice long considered harmful <https://en.wikipedia.org/wiki/Considered_harmful>), and code with lots of branches can be hard to debug and follow.
Straight-line code is code without branches and is almost always easier
to understand. However, a downside of a straight-line approach is that you may end up with duplicated code. There is a tension here between less code and clearer code. For this first assignment, prioritize writing code that can be easily understood, whether it's by you six months from now
or by us in a week when we grade your assignment.

Besides being understandable, good code should be easy to extend and maintain.
A rule of thumb for style is that if your code is well-designed, it should take
little additional code to extend it from 4 to 8 LEDs.

Congratulations on completing your first step on the path to bare-metal mastery!
Sit back and enjoy the show by turning off the lights and impressing your
friends.

## Submitting

Because you've been committing regularly throughout the development process (even
if you haven't been, we're going to pretend that you have because it helps
all of us sleep at night) all you need to do now is create your
submission tag, push to sync with your remote repo, and open a pull request on GitHub. 

Create a submission tag by doing the following:

```console
$ git tag assign1-submission
$ git push --tags
```
This tag is used to identify the latest commit as your submission. Be sure to name your submission tag with the format `assign1-submission`. 

When grading, we look in your repo for the commit tagged `assign1-submission`. This is the commit that we will grade. You are in charge of ensuring that the `assign1-submission` tag is attached to the correct commit and that your commits/tag is pushed to GitHub. You can confirm the status of your submission by browsing your repo on GitHub and verifying that `assign1-submission` tag is listed in the "Tags" section of the "Branches" dropdown menu and that the tag refers to the commit you intend.

If you previously tagged your submission but later realize you need to make further changes, commit changes, move the tag to this commit and push. In the commands below note the use of the `-f` flag to force an update of tag name that already exists:

```console
$ git tag -f assign1-submission
$ git push --tags
```

As before, browse on your repo on GitHub to confirm your submission status. 

After committing, tagging, and pushing your submission, the final task is to open a pull request in GitHub just like you did in assignment 0. The pull request should be to merge `dev` into `master` and give the pull request an intuitive title like "Submit assign1".

> **Don't forget to open a pull request!** We need you to open a pull request so that
> we can grade your assignment.
> {: .callout-warning}

To refresh on the steps to open a pull request, refer to
the [Assignment 0 writeup](/assignments/assign0/).

Assignment 1 is due on Tuesday, January 18 at 5:00pm Pacific. The timestamp on the tagged commit determines the submission time.  Learning to pace your work so as to deliver on schedule is a great skill to build and one that we reward. On-time submissions earn a timeliness bonus. There is also a 48-hour grace period where we accept late submissions without penalty. Read more about the [late policy](/policies/#late-policy).

## Extension

If you enjoyed the core assignment portion and want to explore further, we encourage you to tackle the extension. The extension is more challenging, and may involve using additional
ARM assembly instructions. It will almost certainly require more complicated code
involving conditional branches.

Your extension will build on your core implementation in the same larson.s file. As such, we'll expect that your extension implementation works as good, or better than your core implementation of the scanner.

<!---
1 Program up 4 more patterns.
If you want ideas,
check out some of these
[patterns](https://www.youtube.com/watch?v=uUlkumlkryo#t=17).
-->

If you watch the Larson scanner carefully,
several LEDs are turned on at once.
The center one is at full brightness,
and the ones on the edge are dimmer.
How would you dim an LED? Your challenge for the assignment extension is to
implement a scanner with LEDs aesthetically dimmed
in a way that would please Glen Larson.

You should have a central, full-brightness light that scans just like
in the core version of the assignment, but you should visibly dim the
neighbors of that central light as it moves. Aim for a look similar to
the
[Larson Scanner Kit Demo](https://www.youtube.com/watch?v=yYawDGDsmjk).

You should have at least three distinct levels of brightness.

Before starting on the extension, be sure you have completed all core tasks, including commit, tag, and push of your finished scanner. This ensures your submission tag is a known good place that can be a fallback if the extension doesn't pan out. 

The extension follows the same workflow, edit files on the `dev` branch, make regular commits and pushes. When you have successfully completed the extension, **then move your submission tag to this version so it is the one graded.**

## Grading

Our general process for grading assignments focuses on evaluating the __functionality__ and __quality__ of your submission. For functionality, we assess the completeness and correctness of the implementation of required features. We run tests against the code for a variety of situations and report results to you in terms of passed and failed test cases. Quality comprises an evaluation of the design of your implementation, style and readability of your code, and thoroughness of your test cases.  We evaluate quality through an individual review and provide qualitative and constructive feedback.

To grade your Larson scanner, your beloved CAs will invoke `make` to build your `larson.bin`
file and test it on a Pi with the LEDs plugged in. For this process to go smoothly,
please ensure the following:

- A `make` will successfully build your program with no warnings or errors.
- You use pins 20-23 or 20-27 (depending on how many LEDs you chose to use).

While grading, we'll be checking for the following criteria to be met:

- 4-8 LEDs that individually light
- Scanning pattern is even and smooth
- Scans in both forward and reverse direction
- Reverse at end is handled correctly (no duplicate or skipped LEDs)
- (extension) At least three differentiated levels of brightness

If the CA grading your assignments needs to go into your repository and edit your code for `make` to successfully build, there will be automatic ding in "Build Quality" and we will be sad.

For long-winded general information on grading and policy, see our pages on [assignments](/assignments/#faq) and [course policies](/policies).
