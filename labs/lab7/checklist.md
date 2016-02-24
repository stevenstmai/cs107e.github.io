---
layout: page
title: 'Lab 7: Interrupts Checklist'
permalink: /labs/lab7/checklist/
---

# PS2 Keyboard Lab Checklist

## Part 1 ##

1.  What assembly function does your Raspberry Pi boot into and what does it
    do?

2.  What function does this function call, and what does that function do?

3.  How does the starter code know how long the interrupt table is and safely
    copy it (and nothing more, nothing less) to 0x0?

4.  What is the name of the C function that the IRQ handler invokes? What file
    can this C function be found in?

## Part 2 ##

1. Name two disadvantages, and one advantage, that the spin-loop implementation
   of detecting button presses has or would have over an interrupt based
   implementation.

2. Do you record (i.e., detect in code) one button press per physical button
   press? If not, why might this be?

## Part 3 ##

1. Describe what every line of code in `kdriver_init` does, even if it's
   commented out.

2. What happens if the interrupt event is not cleared before returning from the
   handler?

3. Show the TA that your counter increments when you press the button.

## Part 4 ##

1. Why might you want to push/pop instead of arbitrary logic in the interrupt
   handler?

## Part 5 ##

1. Show the TA that pressing and releasing buttons causes your counter to
   increase and suggest a reason why it might not match up with how many times
   you press or release the buttons.
