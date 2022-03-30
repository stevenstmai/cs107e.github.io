---
released: true
permalink: /assignments/assign0/
title: "Assignment 0: Git oriented"
toc: true
---

{% comment %}
Task list to copy/paste when creating PR for this assign:

**Before releasing assign0:**

- [ ] Review writeup/starter files/process (TA)
- [ ] Followup on issues from previous quarter postmortem (issue #385)

**To prep for assign0:**

- [ ]

{% endcomment %}

_Written by Omar Rizwan, updated by Maria Paula Hernandez for Spring 2022_

{% include duedate.html n=0 %}

<small>This assignment is not for a grade, but it's critical that you understand all the topics covered and that you complete it on-time so that you are ready to tackle the upcoming assignments. If you run into troubles, please reach out on Ed or come by office hours!</small>

## Goals

Your goal for this assignment is two-fold:

1. Walk through and understand the assignment workflow
2. Practice with your tools and refresh on background concepts


The tasks you will do include downloading the starter files, editing the files, committing your changes, and submitting for grading.

This is the same workflow you will use for each assignment in the course. Our process uses the
[git](<https://en.wikipedia.org/wiki/Git_(software)>) version control
system and the [GitHub](https://github.com) repository hosting service. Note
that this assignment assumes that you've completed [lab0](/labs/lab0) in its
entirety. If you haven't done so, please go back and ensure that you've
completed all of the steps.

## Steps

### 0. Ensure you are familiar with your editing environment

In Lab 0, we asked you to explore text editors like vim and emacs. Before you 
begin the assingment, make sure that you are familiar with the editor that you chose 
to work with. This can be in the form of watching a couple of tutorials, reading 
manuals, going to Matt's special intro OH and practicing using your editor of choice! 

### 1. Acquire starter code 

Please refer to the [Git Workflow Guide](/guides/cs107e-git#assign-workflow), 
and follow the instructions to get the starter code for your assignment (Section 'Get assignment 
starter code'). 

### 1.5 Set git editor 

Notice that whenever git opens a text editor window by default, it does so in a specific 
text editor. Which is it? 

This isn't ideal if the editor you are familiar with is different. If it is the one you prefer, 
you can move on to the next section! If not, set your default git editor to your preferred text editor 
as follows: 

```console
$ git config --global core.editor [PREFERRED-EDITOR-NAME]
```

### 2. Answer background questions

Having downloaded your starter files, you should find a folder labelled 'assign0' in your assignments
repo. The folder corresponding to each assignment will contain all of the starter code that you need
to complete it. 
In the file 'background.txt', please answer the following questions. 
Please ensure that your responses are clearly labeled (i.e. 
we know what question it corresponds to) and reasonably organized.

> **Tip** If you're stuck on any of the questions, take a look at the guides section
> of the course website, post on Ed, or start reading some articles online!
> {: .callout-info}

1. What is the result of performing a bitwise OR of the following two
   hexadecimal numbers (include the result in decimal): `0x0f OR 0xff`. Now left
   shift that number by 24; what is the result in hexadecimal? Assume numbers are 32-bit.

2. How many milliamperes of current will flow through a 1.5K resistor connected
   to 3V on one end and 0V (Ground) on the other end?

3. Find a file in the directory `/etc` on your computer; tell us the name of the
   file and the number of bytes contained in that file. How many files and
   directories are contained in the first level of directory `/etc`? Include
   the commands you used to answer these questions.

4. Change directory to your `cs107e.github.io` repo and find the folder named `cs107e`. What is the
   the absolute path to this folder? What is the relative path using the
   CS107E environment variable you created during your environment setup? Remember
   this folder location! Inside the `cs107e` there is an `include` folder where all your
   assignment header files are located. (You can find more information on the filesystem in our [unix guide](/guides/unix/)).

5. What editor do you plan on using? What is your plan on learning
   how to best use your editor? (i.e. for people using vim, you can run the `vimtutor` command from your terminal). Tell us a bit about how you customized your
   editor!

6. In git speak, what is a "commit"? What is a "branch"?
   If you're unsure, refer to our [git guide](/guides/git).

### 3. Commit your change locally and push it to remote

Now you are going to tell Git about the changes you have made. Please refer to the [Git Workflow Guide](/guides/cs107e-git#assign-workflow), and follow the instructions to commit the changes you made (Section 'Assignment Commit'). 
 
<a name="submit"></a>
### 4. Tag submission commit

We've now told the remote repository about the changes we made locally. Now, lets 
tell the teaching team that's the code you want to be graded. 
Please refer to the [Git Workflow Guide](/guides/cs107e-git#assign-workflow), and
follow the instructions to tag your Assignment0 submission (Section 'Assignment tags'). 

### 5. Create a pull request (submission)

The last step to submitting your assignments will be to create a pull request. 
Please refer to the [Git Workflow Guide](/guides/cs107e-git#assign-workflow), and
follow the instructions to create a pull request (Section 'Assignment pull request').

You have now followed all of the steps to submit your assignment. Please refer to the [Git Workflow Guide](/guides/cs107e-git#assign-workflow), section 'Assignment Submission', where you will find a checklist of all the things to do 
to ensure you submit your assignments properly. (But there is more! See below)  

### 6. Edit your submission

You have submitted your assign0, but as you scroll down the page you realize there is more! 
You need to now go back and edit your submission, then ensure that you inform git AND the 
teaching team so they are grading the submission you ammended. This may happen during your future 
assignments workflow if you realize after submission that there was a bug, or there is 
something else you want to fix. Let's figure out how to do that now. 

### 7. Add a photo and edit your assign0 README.md 

First of all, whats missing? A fabulous CS107E tradition is creating a Wall of Fame 
with all of your and the teaching team's pictures and fun facts. In order to create it, 
please add a photo of yourself (if you are comfortable) to your assign0 folder. Then, go into
the README.md file in your assign0 folder, and edit it to include the following information: 
1. Your name 
2. Your hometown 
3. A fun fact about you! 

Note that typically, the README.md file of each assignment will contain information 
you'd like to communicate to the grader about your submission. This can be something like 
'I haven't been able to get X working yet' or 'I am still confused about X topic 
and will come to OH to clarify!'. It may also be left blank. 

Now, we have created new changes in our assignment that we want to be reflected in our 
submission. Please refer to the [Git Workflow Guide](/guides/cs107e-git#assign-workflow), 
to stage, commit and push your changes, as well as move the submission tag to alert the grader 
that the commit you want graded has changed (Hint: you will want to refer to the section of 'Assignment tags' 
that explains how to change a tag that already exists). 

### 8. Final Steps 

Now, go over the submission checklist in the [Git Workflow Guide](/guides/cs107e-git#assign-workflow)
one more time to ensure you have submitted your assignment correctly. 
Note that the [Git Workflow Guide](/guides/cs107e-git) will be a really important resource that you 
will want to read thoroughly to understand how assignment and lab workflows operate, 
as well as how to interpret your feedback. Make sure to read through everything before moving on 
from Assignment 0. 

And you're done! 
