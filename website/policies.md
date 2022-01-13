---
permalink: /policies/
title: Course Policies
toc: true
---


## Grading Policy
Your course grade is compromised your participation in lab and your work on the assignments and final project.

+ __Labs__ meet weekly, your participation is mandatory.
+ There are 7 weekly __assignments__. Each assignment has a set of required core features along with optional extensions or "stretch goals".  You must implement the core functionality and are encouraged to attempt some of the extensions.
+ The course culminates with a final __project__ where you design and implement a system of your choosing.

Your code for each assignment will be evaluated against a set of tests, sorted into three priority levels. Priority 1 tests exercise core functionality without which your code is unusable. Priority 2 tests exercise other functionality prescribed by the basic assignment spec, but without which your modules are still usuable in the most important ways. Priority 3 tests evaluate minor or more obscure edge cases that are important to be aware of but will likely not affect the use of your module.

Many of the assignments in this course build upon each other. It is a good idea, both for your learning and your grade, to revise and resubmit old assignments after seeing what tests they fail.

If you have your sights set on earning an __A__ course grade, you will need consistently __outstanding__ work:
+ Attend and participate in all labs
+ Assignments core
    - Core functionality is complete/correct for all assignments
        - Passing results on all Priority 1 and Priority 2 tests for all assignments by the due date for assignment 7
        - At least 5 out of 7 assignments have their respective Priority 1 tests passing by the assignment due date. Fewer assignments passing P1 on time will correspond to a lower course grade, depending on the number of on-time functional submissions.
    - Code quality (style and tests) trending to `+`
+ Assignments stretch/bonus
    - 3 or more assignment extensions successfully completed
    - Earn the full system bonus for using all your own code on the last assignment
+ Outstanding final project, excellent execution

For a __B__ course grade, we expect consistently __solid__ work:
+ Attend and participate in all labs
+ Assignments core
    - Core functionality is mostly complete/correct for all assignments
        - Passing results on all Priority 1 tests
    - Code quality (style and tests) trending to `ok`
+ Assignments stretch/bonus
    - One extension completed or full system bonus earned
+ Good final project, satisfactory execution

Work that is not completed satisfactorily will earn grades **C and below**.


## Late Policy

The course moves at a steady clip and the weekly assignments build on one other. In our experience, one of the strongest factors in student success has been the dedication to stay on pace. Learning to set a schedule and manage your time to hit deadlines is a valuable skill to develop and an accomplishment you can be proud of.  We designed our policy to encourage and reward good habits, but knowing that things come up, we have a standing grace period that provides a little flexibility if you need it. 

- The submission deadline for the weekly assignments is 5pm Tuesday. An ontime submission earns a small bonus in timeliness. Kudos to you for pacing your work and shipping on schedule! 
- There is also a 48-hour grace period after the deadline in which we accept late submissions. There is no penalty or cap applied to late submissions within the grace period, but they do not earn the timeliness bonus. 
- Late submissions beyond the grace period are arranged with the course staff as warranted for exceptional circumstances.
- The final project must be submitted on time without exception.



## Collaboration Policy

*Adapted from CS107 policy by Julie Zelenski, some wording borrowed from a
collaboration policy distributed by Brown CS.*

The programming assignments are an integral part of the course learning
experience. We have a great set of projects lined up for you and the time you
spend designing your own solution and working toward its successful
implementation can be fun, challenging, illuminating, time-consuming,
rewarding, and frustrating. Your pride upon finishing is a fantastic high and
your efforts earn you powerful skills and deep understanding. Don't cheat
yourself out of this incredible learning opportunity! Borrowing someone else's
design, building on another's code, being lead by another person, and other
such "shortcuts" jeopardize the chance to develop your own mastery and
compromise your integrity.

This document is designed to make clear our expectations and restrictions on
collaboration. We expect your assignment submissions to be your own independent
effort and not be derived from the thoughts and work of others. You should do
your own thinking, your own design, your own coding, and your own debugging.
This doesn't mean that you can't ask questions or get help when you get stuck,
but any help must remain within acceptable limits, as detailed in the concrete
examples given below.

All of you should be familiar with the principles of the [Stanford Honor
Code](https://communitystandards.stanford.edu/student-conduct-process/honor-code-and-fundamental-standard#honor-code). The [CS
department Honor Code policy](http://csmajor.stanford.edu/HonorCode.shtml)
further explains how it applies in CS courses. Students are to uphold their
obligations to do honorable work and encourage others to do the same. On our
part, we will treat students with trust and respect.

<style>
    li .text-success:before {
        content:  '\f087';
        font-family: "FontAwesome";
        margin-right: 4px;
    }
    li .text-warning:before {
        content: '\f071';
        font-family: "FontAwesome";
        margin-right: 4px;
    }
    li .text-danger:before {
        content: '\f05e';
        font-family: "FontAwesome";
        margin-right: 4px;
    }
</style>

### Assistance that is allowed

These things are encouraged and allowed for all students and require no citation:

- __Discussing course topics__{: .text-success }

    You may freely talk through any material from the lectures, labs, readings, and course website.

- __Discussing the language, libraries, and tools__{: .text-success }

    For example: "What does the keyword static mean? How do I view my git history? What does this ARM instruction do?"

- __Clarifying an assignment specification__{: .text-success }

    For example: "Do the results have to be sorted? What is the expected response if the input is empty?"

- __Sharing generic advice and techniques__{: .text-success }

    For example: "I test each function right after I finish writing it. When my program crashes, I first look at the stack trace in the debugger. I used a logic analyzer to study the signals in my circuit."

- __Use of external resources for background information__{: .text-success }

    You may search for and use external resources (web sites, blogs, forums, etc.) for information on course topics, as reference material on the programming language and libraries, and to resolve technical difficulties in use of the tools.

- __Any discussion between student and the staff__{: .text-success }

    You are welcome to discuss any aspects of design, code, or debugging with the course staff. They are the best folks to talk to because they are knowledgeable about all the material and know how to help you without overly influencing or leading you.

### Assistance that must be cited

Discussion and advice specific to the particulars of an
assignment should be cited. The particulars include such things
as the program's design, data structures, choice of algorithms,
implementation strategies, testing, and debugging. Some examples:

- __Discussing your assignment design__{: .text-warning }

    Design is a crucial part of the programming process, and we want you to learn to work through design problems on your own. Only after you completed your own independently-conceived design, you may compare and contrast with a peer who has also completed their own design. You both must cite this discussion and note any ideas taken away from it.

- __Helping another student to debug__{: .text-warning }

    A student might describe symptoms to a peer who responds with suggestions (e.g. "it sounds like you might have forgotten to terminate the string" or  "have you tried running under the gdb simulator?"). If you receive debugging help that was essential to your progress, please cite it.

- __Sharing test strategies or inputs__{: .text-warning }

    If you discuss strategies for testing or jointly brainstorm test inputs (e.g. "be sure to verify handling when index is out of range"), this collaboration should be cited.

#### What is an appropriate citation?

A citation should be specific, complete, and truthful. Clearly identify the source of the help/discussion (person's
name, book title, URL), describe the nature and extent of the
assistance, and indicate how it influenced
your submission.

### Assistance that is NOT allowed

Discussions should never become so detailed that they involve jointly
writing or exchanging/sharing passages of code. Your code must
represent your original, independent work and it should not be
developed in conjunction with or derived from anyone else's. You
should never be intimate with another's code nor allow others to
be intimate with yours. Here are specific examples of unpermitted
aid:

- __Copying code__{: .text-danger }

    It is an act of plagiarism to submit work which is copied or
derived from the work of others and represent it as your own.
It does not matter if the plagiarized source was a current or
former student, outside the course, or found on the web, or
whether the amount was an entire program or just a small part;
in all cases, it is unacceptable. You should never be in
possession of anyone's else code, whether in printed, written,
or electronic form.

- __Reviewing the code/design of another__{: .text-danger }

    You are not permitted to have another person "walk you through"
their approach nor may you use their work "as a reference" to
look at if you get stuck. This prohibition applies to both code
and design, to isolated passages as well as the entire program,
and whether the review is conducted verbally or in
printed/written/electronic form.

- __Joint development/debugging__{: .text-danger }

    You are not permitted to work with another to jointly develop
a design, write code, or debug. Two students should never be
working together on a passage of code/pseudocode whether on
paper, on a whiteboard, or in editor/debugger of a shared
computer.

- __Use of external resources for assignment-specific code__{: .text-danger }

    You should not be searching external resources for solutions,
whether in the form of code, pseudocode, or design. Should you
find full/partial solutions anyway, you are to turn away and
report the location to us. A submission must not be adopted
from or influenced by study of any external resource.

- __Sharing your code__{: .text-danger }

    You must not share your code with individual students nor
publicly broadcast it. The repositories we create for you on Github, 
will be private and we expect that you will 
keep them so. Even after the course ends, you are expected to take reasonable security precautions
to maintain your work privately. If we request that you
remove publically-shared code, you are
expected to comply in a timely manner.

### Integrity as community

The Honor Code is a powerful assertion that we as a community proudly
dedicate ourselves to upholding the highest standards of academic
integrity. The vast majority will do right by CS107E -- we ask a lot
of you and you will consistently meet those challenges by creating
work that authentically represents your own effort. We demonstrate
our respect and appreciation for your honor and efforts by doing
our part to make absolutely clear our expectations and hold accountable
those students who act in violation.

