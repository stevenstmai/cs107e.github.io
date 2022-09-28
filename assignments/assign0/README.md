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

_Written by Maria Paula Hernandez for Spring 2022_

{% include duedate.html n=0 %}

<small>This assignment is not for a grade, but it's critical that you understand all the topics covered and that you complete it on-time so that you are ready to tackle the upcoming assignments. If you run into troubles, please reach out on Ed or come by office hours!</small>

## Goals

Your goal for this assignment is two-fold:

1. Walk through and understand the git workflow we use in this course
2. Practice with your tools and refresh on background concepts


This assignment will give you practice with the standard tasks of getting starter code, editing files, 
committing changes, and submitting for grading, as used in our standard git workflow.


## Steps

### 0. Ensure you are familiar with your editor

In Lab 0, we asked you to explore text editors like vim and emacs. Throughout this course,
you will make heavy use of your chosen editor, so now is a good time to invest in
becoming comfortable and efficient with it.  This can be in the form of 
watching tutorial videos, reading manuals, going to Matt's special intro OH and practicing with your editor.

### 0.5 Set git editor

Some git commands automatically open a text editor on your behalf. If you have not set an editor
in your git config, it uses a default choice.  Which editor is the git default? 
Is this your preferred editor? If it is not, you can configure git to use the editor you prefer with the following command:

```console
$ git config --global core.editor [PREFERRED-EDITOR-NAME]
```

### 1. Acquire starter code

Follow the instructions to get the assign0 starter code in the [Git Workflow Guide](/guides/cs107e-git#get-assignment-starter-code).

### 2. Answer background questions

After pulling the starter code, your `mycode` repo should have a folder named `assign0`. 
The folder for each assignment will contain all of the starter code that you need
to complete it. 

In your `assign0` folder, find the file named `background.txt` and open it in your text editor.

Add answers to the following questions.  Please ensure that your responses are clearly labeled (i.e. 
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

4. Change directory to your `cs107e.github.io` repo and find the folder named `cs107e`. What is
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

After using your editor to save the `background.txt` file, you now need to inform git to record those changes. Follow the instructions in the [Git Workflow Guide](/guides/cs107e-git#assignment-commit) to use git commit to record a local snapshot, followed by a git push to synch those changes to your remote repo.
 
<a name="submit"></a>
### 4. Tag submission commit

Both the local and repo repositories are now up to date with your latest changes.
Tell the teaching team that's the code you want to be graded by following the instructions
in  [Git Workflow Guide](/guides/cs107e-git#assignment-tags) to tag your submission.

### 5. Open a pull request

The last step in submit is to ensuring that you have an open pull request. 
Please refer to the instructions about making a pull request in the [Git Workflow Guide](/guides/cs107e-git#assignment-pull-request).


Confirm that you have now completed all of the steps listed in the checklist under the section "Assignment submission" in the [Git Workflow Guide](/guides/cs107e-git#assignment-submission). Congrats! (but wait, there is more, see below...)

### 6. Edit your submission

You have submitted your assign0, but as you scroll down the page you realize there is more! 
You need to now go back and edit your files, then follow up to inform git and the 
teaching team so they know to grade your amended submission. This may happen during your future 
assignments workflow if you realize after submission that there was a bug, or there is 
something else you want to fix. Let's figure out how to do that now. 

### 7. Add a photo and info about yourself

What's missing? A fabulous CS107E tradition is creating a Wall of Fame 
with all of your and the teaching team's pictures and fun facts. We
would love to include your photo on the wall (if you are comfortable). 
Copy your photo file into your `assign0` folder and add and commit it so it
is included with your submission. 

Then, edit the `README.md` file of `assign0` to include the following information: 
1. Your preferred name and pronouns 
2. Your hometown 
3. A fun fact about you! 

Note that typically, the `README.md` file can be used for any information 
you'd like to communicate to the grader about your submission. This can be something like 
'I haven't been able to get X working yet' or 'I am still confused about X topic 
and will come to OH to clarify!'. It may also be left blank. 

Now that you have edited your files, you need to update your submission with new changes.  
Please refer to the [Git Workflow Guide](/guides/cs107e-git#assign-workflow), 
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
