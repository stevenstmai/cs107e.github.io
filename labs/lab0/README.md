---
released: true
permalink: /labs/lab0/
title: 'Lab 0: Orientation'
toc: true
readings: |
  Please do the Lab 0 [prelab preparation](/labs/lab0/#prelab-preparation) before coming to lab.
---

{% comment %}
Task list to copy/paste when creating PR for this lab:

__Before releasing lab0:__
- [ ] Review writeup/code/checkin questions (instructor)
- [ ] Walk through (SL)
- [ ] Followup on issues from previous quarter postmortem (issue #375 and #385)

__To prep for lab0:__
- [ ] Review tips recorded in private/staff_notes.md and private/answers.md
- [ ] Review installation instructions, bring up-to-date for latest versions
- [ ] Bring blank labels and pens -- students make name tag and decorate kit box
- [ ] Create Google sheet with class roster to record lab attendance

{% endcomment %}


Welcome to CS107e lab! Lab is one of the most beloved components of this course. We aim to create a lab experience brings us together to teach and learn from one another in the same great spirit of collaboration and community.

## Goals

During this lab you will:

- Start getting to know one another
- Confirm working install of developer tools
- Set up your assignments repo
- Practice with the command line and key tools such as your text editor
- Review binary and hexadecimal number representations

## How does lab work?
Lab is a time to experiment and explore. After we introduce topics in
readings/lectures, you'll do guided exercises in lab to further your
understanding of the material, get hand-on practice with the tools in
a supported environment, and ready yourself to succeed at this week's
assignment.

Bare metal programming requires precision. A trivial typo or slight
misunderstanding can stop your progress cold. Working with the support
of your classmates and staff can make the difference between quickly
resolving that sticking point versus hours of frustration wrestling on
your own in the dark.

Each lab has a set of check-in questions to answer as
you go. Touch base with the staff on each question to confirm your
understanding and resolve any confusion. The check-in questions are
intentionally simple and your responses are not graded; we use them as
a gauge of how you're doing with the material so that we know better
how to help guide you.

To get the most out of lab, don't set your goal at merely finishing
the absolute minimum required in the shortest possible time.  If you
already have a good handle on the material, use the lab period to dive
into further nooks and crannies or help out those peers who could
benefit from your experience.  You should also get to know the
staff.  They are masters of the craft, and you will learn a lot
by talking to them and asking them questions.

The combination of hands-on experimentation, give and take with your
peers, and the expert guidance of our staff is what makes lab time
truly special.  Your sincere participation can really accelerate your
learning!

## Prelab preparation

To prepare, please do the following before coming to this lab:

1. Follow the instructions in [installation guide](/guides/install) to set up your environment.
2. From our course guides, please review:
    -  [Unix command line](/guides/unix) 
    -  [git](/guides/git) version control system
    -  [binary and hexadecimal](/guides/numbers) numbers
3. Check out these CS107 guides on using the `emacs` or `vim` text editor: 
    - [emacs](https://cs107.stanford.edu/resources/emacs.html)
    - [vim](https://cs107.stanford.edu/resources/vim.html)

## Lab exercises

<a name="step1"></a>

### 1. Confirm install
Use the __Final check steps__ at the end of the [installation guide](/guides/install) to confirm that the needed tools are installed and your environment is correctly configured. If you hit any snags during install, bring those issues to lab and we can help you resolve. If you're good to go [^1], go ahead and move on.

### 2. Set up your local assignments repository
Our course repositories will be hosted on GitHub. You will download assignment 
starter files from GitHub and upload your completed work to GitHub for grading.  Each student will be given a private assignments repository inside our
[CS107e GitHub organization](https://github.com/cs107e).  The repository that resides on GitHub is your __remote__ assignments repo. It will be connected to the __local__ assignments repo on your computer where you will work on the assignments.  Set up the local assignments rep by following the steps below. Be sure to ask for help if you run into any snags.

- __Step 1: Accept GitHub invitations__ 
    
    You should have received two email invitations from GitHub: an invitation for read-only access to the starter code repo <https://github.com/cs107e/assignments-mirror.git> and another invitation for read-write access to your private assignments repo. Once you receive and accept both invitations, you're ready to proceed.

-   __Step 2: Create SSH key and add to GitHub account__

    In order to interact with GitHub from the command line, you'll need set up an SSH
    key on your GitHub account. An SSH key is a way to authenticate
    that you are who you say you are. To create an SSH key, enter the following
    command in your shell:

    ```console
    $ ssh-keygen -t rsa -b 4096 -C "<your_email>"
    ```

    After you press enter, you'll be prompted to choose an alternate name for your
    key. Skip this by pressing enter again. Next, you'll be prompted to enter a
    passphrase for a key. If you want no passphrase, press enter. Otherwise, enter
    your passphrase. If you choose to add a passphrase, you must enter that passphrase each time you push to or pull from GitHub .

    Confirm the key has been created by looking for the key files in your `.ssh` directory:

    ```console
    $ ls ~/.ssh/
    ```

    You should see two files: `id_rsa` and `id_rsa.pub`. SSH uses public-key
    cryptography, which requires a private key and a public key. `id_rsa` is your
    private key and should never be shared. `id_rsa.pub` is your public key and can
    (and should) be shared.

    Now add your new SSH key to your GitHub account by following [these
    instructions](https://docs.github.com/en/github/authenticating-to-github/adding-a-new-ssh-key-to-your-github-account).

- __Step 3: Clone assignments repo__

    **Note**: In this step and the steps to follow, where you see
`[YOUR-GITHUB-USERNAME]`, replace with your __actual GitHub username__.

    After accepting the GitHub invitation and setting up your SSH key, you can now clone your assignments repo.
    In your browser, visit the page
    `https://github.com/cs107e/[YOUR-GITHUB-USERNAME]-assignments` to see the contents of your remote repo.
    It should have only a single file: `README.md`, which lists the name of your
    repo and nothing more. Upon confirming this, switch to the terminal and execute
    the following commands to clone the repo, which creates a local copy on your
    machine of the remote repo on GitHub. We recommend that you store your local repo in the parent directory `cs107e_home` that you made during the install process.

    ```console
    $ cd ~/cs107e_home
    $ git clone git@github.com:cs107e/[YOUR-GITHUB-USERNAME]-assignments.git assignments
    ```

    Confirm that the local clone repo matches the remote repo by cd'ing and and examining its contents.

    ```console
    $ cd assignments
    $ ls 
    $ cat README.md
    ```

- __Step 4: Create dev branch__

    The master branch in your assignments repo is write-protected which means
    that you will not be able to directly modify the master branch on GitHub. Instead, you'll create a separate `dev` branch where you will do your work. To create this
    branch, change to your assignments repo and execute the
    following commands:

    ```console
    $ cd ~/cs107e_home/assignments
    $ git branch
    $ git checkout -b dev
    $ git branch
    ```

    When you run the first `git branch` command, notice how there is only a single
    branch listed: `master` and there is an asterisk next to `master`,
    which means that it is the currently checked out branch. When you run the second
    `git branch` command, you should have two branches--`master` and `dev`--and the
    asterisk marking the currently checked out branch is now next to `dev`. 

- __Step 5: Get starter files__

    Next, you must configure your local `assignments` repo to have an additional remote connection to the starter code repo so that it can also synchronize with that repo. Execute the following commands to add a remote for `starter-code`

    ```console
    $ git remote -v
    $ git remote add starter-code git@github.com:cs107e/assignments-mirror.git
    $ git remote -v
    ```

    After running the first `git remote -v` command, you should have only a single
    remote: `origin`. `origin` is a shorthand way of referring to your remote repo
    on GitHub. The `git remote add` command adds a second remote. This second remote
    is `starter-code`, which is a shorthand way of referring to the starter code
    repo on GitHub. The second `git remote -v` should show you both remotes:
    `origin` and `starter-code` and the URLs that they represent.

    To get the starter files, verify that you're on the `dev` branch and execute the
    following commands:

    ```console
    $ git pull --allow-unrelated-histories starter-code assign0-starter 
    $ ls
    ```

    The `git pull` command will open up `vim` and display the message "Merge branch
'assign0-starter' of github.com:cs107e/assignments-mirror into dev". Confirm
this merge by typing `:x`, which will save and exit `vim`. The `ls` command 
should show the addition of a second file--`notes.txt`--that was pulled down
from the starter code repo when you executed the `git pull`. 

- __Step 6: Create remote branch__

    A few steps earlier, you created a `dev` branch in your repo. Unfortunately, this
    branch is only local. That is, it doesn't exist in your remote repo on GitHub
    yet. Let's fix this now. First confirm that you're on the `dev` branch. Then,
    run the following command:

    ```console
    $ git push --set-upstream origin dev
    ```

    This command creates the `dev` branch on the `origin` remote (your GitHub repo) 
and connects this remote `dev` to your local `dev`.

    If you return to your GitHub repo in your browser, you should now find a `dev` branch in the branches dropdown menu.

With a working git setup, you are ready for the second check-in question [^2].

Bookmark our course [guide on git](/guides/git) to read later for an introduction to git and links to further readings. 

### 3. Website scavenger hunt
Our course website is where you'll find lecture slides, lab writeups, and assignment specifications, along with a trove of additional resources such as our course guides and curated set of readings, resources, and demos. We encourage you to explore a bit and become acquainted with what's available and how it's organized.  The __Search__ tab is handy way to find matching content across all pages on the site.

As you explore, see if you find answers to such questions as:

+ Oh no! I lost my copy of the pinout diagram for the Raspberry Pi A+. Where can I find a new copy of the one CS107E uses? (p.s... Is there an interactive version available as well?)
+ Where can I find the recommended readings to review before a lecture?
+ I have never used the gdb debugger before. Where do I start and where can I learn more?
+ I'm sick of unplugging and replugging in my USB-serial adapter. Is there another solution? (For bonus points, find a link to a soldering tutorial!)
+ What is the course policy on collaboration?
+ Breadboards make no sense to me. How do I know which holes are connected?
+ Pat demo'ed this cool ARM simulator in lecture. How can I play with that myself?
+ I'm working hard to write tests, but I just don't feel like I'm covering my bases. What am I doing wrong? Is there advice on software testing more broadly?
+ I am curious about the final project. Are there examples of what other groups have done in the past to take inspiration from?

If a topic has you curious or confused, start by checking the course website for helpful information. If can't find the information you need, reach out on Ed or come visit us in office hours. We want you to always feel comfortable coming to us with any questions you have, as well as suggestions on how we can improve the quality of the resources available to you. You're ready for the third check-in question [^3].

### 4. Command line practice
Over the course of CS107E, you'll get comfortable navigating the command line. To start, read through and follow all the steps in our [Unix Command Line Guide](/guides/unix).

While that guide covers the basics, here's a couple more tricks to speed up your workflow. Practice using these---you'll be amazed at how much they boost your productivity!

+ Typing a long path of a file or directory? Use ✨tab-complete✨! When you press `[tab]`, UNIX will automatically fill in your partially typed command. Try navigating to new directories in your file system and see what you can get to successfully tab-complete.
+ To replay a previous command, use your arrow keys (↑ and ↓) to move through the commands in your history. Type `history` and see everything you've done in this session.
+ Used a long command a while ago, but don't want to type it all out again? Search through your history with `ctrl+r`!
+ Want to go back to your home directory? Instead of typing `cd ~`, save a couple keystrokes with just `cd`.
+ To move to the beginning of the line, type `ctrl+a`. To get to the end, type `ctrl+e`. (p.s... these are the same in Emacs, which you'll learn about in a bit!)
+ To redirect the output of a command into a file (for example, if you wrote tests with a lot of output, which you want to be able to read through at your leisure), use the `>` symbol like this:
```console
$ command_with_long_output > new_file.txt
```
+ Want to look at the contents of a file without opening it in a text editor? Use `cat`, short for concatenate, like this:
```console
$ cat file_I_want_to_look.at
```
+ Use `man` to access the manual page for a command, including sample usage and list of option flags. For example, read `man cp` and find out what the `-r` option does. A handy website tool is <http://explainshell.com> which can be used to break down and explain a command and its options. Enter `cp -r` there to see an explanation.

Over time, you might learn about other helpful commands, like `grep`, `diff`, and `echo`. Curious about how to use these, or any other commands you've seen used? Get more information from the `man` page, explainshell, a google search, or other reference document. Make a point to learn a new command each day when you sit down to work and you'll soon be well on your way to becoming a command line ninja! 🔥

### 5. Editors
When you've taken CS classes in the past (like 106A/B), you've likely relied on IDEs (integrated development environments) like PyCharm, Qt, or Eclipse. While those are great for some tasks, we're going to rely on a new set of tools for this class: __text editors__. Have you ever opened a file in Notepad or TextEdit? The editors we'll be using, like Emacs and Vim, aren't too different at a basic level, except that they're built specifically for programming and can be configured to do all kinds of fancy things (although you don't need to worry about that for now).

![XKCD Text Editors](images/real_programmers.png){: style="float:center;"}

Every programmer has their own (usually strongly held) opinion about which editor they prefer to use. Common choices are __Emacs, Vim, Sublime, Nano, and VSCode__. While these editors can often feel overwhelming at first---especially command line editors, like Emacs and Vim---you will be so grateful for the time you invest in learning them well during this class.

No matter which editor you decide to make your home base, we think it's a worthwhile investment for everyone to learn enough Emacs and Vim that you could open a file, make an edit, and save & close the file without any trouble (this skill will serve you well in the future, like if you have to quickly edit code on systems you've just ssh'ed into).

Try out Emacs now. The command below will open the editor on a new file named `emacs_is_better.txt` in the directory `~/`. (Note: on more recent macOS versions, use `mg` in place of `emacs`. This is a lightweight emacs-style editor that comes pre-installed. You can also install regular emacs via homebrew.)
```console
$ emacs ~/emacs_is_better.txt
```
If that worked, type away! Once you're ready to save your document and exit Emacs, type `ctrl+x ctrl+s` to save and `ctrl+x ctrl+c` to exit.

Now that you've tried Emacs, let's get a taste of Vim. To open a new file in `~/` named `vim_is_better.txt`, type:
```console
$ vim ~/vim_is_better.txt
```
To edit in Vim, there's actually another step. We need to switch out of command mode into insert mode. Type `i` and you should be able to start writing away! Once you feel ready to quit, type `ESC` (the escape character) and you'll be back into command mode. From there, to save and quit, type `:wq`.

As long as you are able to open, edit, and exit in Emacs and Vim, you could attack any command line and start writing code (albeit, not very efficiently).

At this point, you might be wondering---why are programmers obsessed with these tools? There are a million tools that can edit text far more intuitively, from Google Docs to iMessage to a text box in MS Paint---and while that's all true, the benefit of these text editors is 1) agility & speed and 2) configurability.

Why are these tools so much faster? For one, they can be launched directly from the command line, as we'll see below. Once you get comfortable programming in an editor, you should be able to do everything you need with your keyboard, and never touch your mouse. While it might not seem like a big deal, flipping back and forth between the command line and your code quickly will speed up your workflow a lot.

How are these tools configurable? Well, once you've spent some time working with your editor, you might decide that you want to permanently add line numbers. Or rainbow indent markers. Or have "lambda" always be replaced with λ. Or have your editor always show you an XKCD upon startup. Once you feel comfortable with Emacs or Vim, you can look into editing their `.config` files (or, you can feel free to ask the TAs if they're willing to share their personal configs!).

We won't dictate which text editor you have to use, but whichever you pick, make an investment in learning and mastering its features. For a start, right now, learn how to do the following things in your preferred text editor __without__ touching your mouse. Our [command line guide](/guides/unix) has links to common Emacs and Vim commands, but you can also find all this information online. Practice the following:
+ Move your cursor to the end of the line. Now move it to the start of the line. Practice moving back and forth.
+ Move your cursor one line down. Move it one line up. Go up and down and up down.
+ Scroll the screen down. Now scroll it back up. Repeat. Practice makes perfect!
+ If you can't see line numbers on the side of your screen, learn how to display them. We promise you'll thank us later when there's a bug in line 173.
+ Delete an entire line of text all at once.
+ Now undo that! Hint: if you're working through the command line, you'll likely regret typing `ctrl+z` like you're used to, which sends a SIGSTP to the process---a little sneak peek of CS110!
+ Search through your code. This one can take some practice, because many text editors have different kinds of searches. Find one that works for you.
+ Learn how to copy, cut, and paste code around your document, and then practice doing that over and over.

Now that you've learned how to do these, spend the next week practicing the commands! Your goal is to build up muscle memory around these commands---so even though it'll be annoying for the first week to keep looking up how to do this or that, we promise that with practice it'll become easier and easier, until you can't even remember a time when you needed to leave your keyboard while writing code💪. 

Let us know how you're doing on getting acclimated in your environment with this check-in question [^4].

### 6. Binary numbers

Now that you know where the guides are located, find the [binary guide](/guides/numbers). Practice your binary/hex conversions by writing down answers to the questions in the guide. Then, check out these [bitwise practice problems](https://web.stanford.edu/class/archive/cs/cs107/cs107.1186/lab1/practice.html) courtesy of CS107. Another fun practice tool is this [online visualizer for bitwise expressions](https://mdrach.github.io/cs107-apps/) written by CS107 CA Max Drach. Check it out!


## Check in with TA

Each table group should periodically touch base with us as you work through the exercises. The check-in allows us to
verify your understanding and help with any unresolved issues. 

The four points we'd like you to check in with us for this lab are listed below:

[^1]: All is installed and working in your development environment.

[^2]: You have set up your local assignments repo and are able to push and pull to your remote.

[^3]: You are comfortable with finding information on the course website.

[^4]: You are able to handle simple command-line tasks, can make basic use of your editor, and are ready to learn more!


<style>
    .footnote:before {
        content: ' Q-';
    }
    .footnotes:before {
        content: "Check-in questions";
        font-size: 125%;
    }
</style>
