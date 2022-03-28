---
title: "Guide: Git Workflow for CS107e"
toc: true
---

_Written by CS 107E TAs Jesse Doan and Matt Trost with material borrowed from labs and assignments_

## Configure `mycode` repo
 
> TODO Remove setup instructions from lab0 and put in this document (lab0 can refer to this page)
{: .callout-danger}

Steps:
- accept invites (personal + mirror)
- configure ssh key
- make `mycode` clone in ~/cs107e_home
- set code-mirror as remote (note change in name -- was assignments-mirror, now is code-mirror)
- create dev branch, upstream

Explain organization `mycode` repo, separate subdirectory per each lab and assignment.

## Lab workflow
### Get lab starter code

When starting a new lab, do a `git pull` in your `cs107e.github.io` repository to ensure your courseware files are up to date.

```console
$ cd $CS107E
$ git pull
```
Update your local `mycode` repo by checking out the `dev` branch and pulling the lab starter files from the remote (change labX to lab1, lab2, as appropriate):

```console
$ cd ~/cs107e_home/mycode
$ git checkout dev
$ git pull --allow-unrelated-histories starter-code labX-starter
```

After these commands, your repo is on `dev` branch and all files are up to date. `cd` to the `labX` folder and use `ls` to see the new files.

(Note: the `git pull` command may open up your editor and display the message "Merge branch 'labX-starter' into dev". Confirm the merge by saving and exiting the editor.)

You don't need to commit or submit lab code to be graded. The staff will review your code during lab and check off your participation. 

## Assignment workflow
### Get assignment starter code

When starting a new assignment, do a `git pull` in your `cs107e.github.io` repository to ensure your courseware files are up to date.

```console
$ cd $CS107E
$ git pull
```

Update your local `mycode` repo by checking out the `dev` branch and pulling the assignment starter files from the remote (change assignX to assign1, assign2, as appropriate):

```console
$ cd ~/cs107e_home/mycode
$ git checkout dev
$ git pull --allow-unrelated-histories starter-code assignX-starter
```

After these commands, your repo is on `dev` branch and all files are up to date. `cd` to the `assignX` folder and use `ls` to see the new files.

(Note: the `git pull` command may open up your editor and display the message "Merge branch 'assignX-starter' into dev". Confirm the merge by saving and exiting the editor.)


### Assignment commit

__Some of the steps below are explained in assign0, move text into this document instead (assign0
 can refer to this page)__

> TODO explain add/commit and encourage consistent, regular commit/push
{: .callout-danger}

### Assignment tags

> TODO explain how to set a tag and how to push tags, including how to move a tag, use of tags for extension
{: .callout-danger}

### Assignment pull request

> TODO explain how to open PR, how to check PR is open
{: .callout-danger}

### Assignment submit

> TODO explain submit in terms of commit/push/tags/PR (also how to update submit)
{: .callout-danger}

### Assignment grading feedback

> TODO where to find style comments, issues, logs
{: .callout-danger}

### Assignment re-test

> TODO how to fix open issues, update code in terms of commit/push/tag
{: .callout-danger}

## Decide what to do with text below?
From here down gets bogged down in complex scenario and fussiness about time details, not sure this helps and I would prefer the focus be clearly explaining the basics (i.e. the steps above). Maybe just cut from here to end until we have time to clean it up?

1. For any submission (on-time or resubmission), you first need to `git add` all of the files that you want to add to this commit. You then perform `git commit -m "insert short but meaningful commit message"` followed by `git push`.
2. Next, you also need to tag your commit as your submission with either `git tag assignX-submission` if it's on-time (e.g. before the grace period ends) or `git tag assignX-submission-updated` if it's a resubmission (e.g. fixing code to address bugs and failing tests for eligible resubmission -- extension not included). You then push the tag with `git push --tags`.
3. After submitting your code, check to see if you have an open pull request on GitHub to merge the dev branch into the master branch. If you have an open pull request, you can safely skip the rest of this step (you only need one open pull request at a time for grading). If not, you should create a pull request by going to GitHub -> Pull Requests -> New Pull Request -> Verify that dev is being merged to master (e.g. base: master <- compare: dev) -> Name your Pull Request -> Create Pull Request.
4. If you want to overwrite a submission (on-time or resubmission), you first follow the same steps in Step 1. Next, you perform either `git tag -f assignX-submission` for on-time submission or `git tag -f assignX-submission-updated` for resubmission. The `-f` flag overwrites the tag for the previous commit. You then finish off with `git push --tags --force`.
5. Note that extensions, style, and certain manually-graded tests (that we will specify if applicable on an assignment) are NOT eligible for resubmission. Style grade and style comments are for you to use to improve on future assignments.

We'll also explain the workflow by using an imagined scenario. The dates/times are contrived for purposes of illustration; they are not normative:

1\. It's Thursday, Jan 20. Matt starts working on assignment 2, which is due at 5pm PT on Tuesday, Jan 25.

2\. (On-time submission) Matt completes the basic assignment on Monday, Jan 24. He commits the final change to his basic functionality and tests, then tags that commit as his submission:

```console
$ git commit -m "assign2 basic functionality and tests complete"
$ git push
```

```console
$ git tag assign2-submission
$ git push --tags
```

Note that the git push pushed the commits and code, while the git push --tags pushed the tag information. You need to do both.

3\. (Pull Request) Matt goes to his Github and creates a pull request to merge the dev branch into the master branch. Note that if the assign1 (or any other) pull request is still active/open, then this step is not necessary. Only one pull request can be active at a time. Your graders will close pull requests when they finish grading -- you should NOT merge or close pull requests yourself.

4\. Now that the assignment is submitted prior to the deadline, Matt knows he is eligible for the (albeit quite small) timeliness bonus for this assignment. Matt starts working on the assignment extension.

5\. It's 4pm on Tuesday, Jan 25. Oh no! While working on the extension, Matt discovers a bug in his basic assign2 implementation. He doesn't have time to fix it before the 5pm deadline, but that's ok since every assignment has a 48-hour grace period where code can be submitted to the original submission without penalty. He won't get the (small) timeliness bonus, but he can still fix and submit it without a deduction.

6\. (Overwriting an on-time submission) It's 3pm on Wednesday, Jan 26. Matt fixes the bug and wants to update his submission. Important: because this is within the grace period, Matt will update his original submission tag instead of creating a new tag:

```console
$ git commit -m "fixed bug that did XYZ. basic functionality now complete."
$ git push
```

```console
$ git tag -f assign2-submission
$ git push --tags --force
```

Note that the -f and --force flags were required to overwrite the tag, since it had already been assigned. Also note that you need to do both pushes.

Since the pull request was opened in step 3, Matt does not need to do anything in Github at this time.

7\. It's 3pm on Thursday, Jan 27. Matt completes the assign2 extension, just in time since extension tests are not eligible for resubmission and therefore all extension code must be submitted prior to the end of the grace period. Since the grace period has not yet elapsed, Matt will update his original submission tag just like in step 6:

```console
$ git commit -m "assign2 extension complete"
$ git push
$ git tag -f assign2-submission
$ git push --tags --force
```

As in step 6, Matt does not need to update his github pull request since it will still be open.

8\. (Resubmission after deadline) It's 3pm on Monday, Jan 31. Matt's assign2 has been graded and there are failing tests. Importantly, these failing tests are eligible for resubmission (extension tests and manually-graded tests are not eligible; the eligibility of a test will be marked in the README that lists test results). Matt looks at the failing test logs and discovers some bugs causing those issues. Matt fixes those issues and wants to update his assignment. The grace period has passed, so Matt will tag this commit with an -updated tag:

```console
$ git commit -m "fixed bugs XYZ and ABC."
$ git push
```

```console
$ git tag assign2-submission-updated
$ git push --tags
```

It is very important that you do not overwrite the original assignX-submission tag after the grace period elapses. After the grace period elapses, all resubmissions must be tagged assignX-submission-updated

Matt checks to see if his pull request was already graded and closed. If so, he opens a new one. If not, he doesn't need to do anything in Github.

The next time the graders convene, Matt's updated code will be run again and his test results will be updated and uploaded to his Github. This will occur on roughly a weekly basis.

9\. (Overwriting a resubmission) If further resubmissions are needed, the assignX-submission-updated tag must be force-updated:

```console
$ git commit -m "fixed more bugs UVW and DEF."
$ git push
```

```console
$ git tag -f assign2-submission-updated
$ git push --tags --force
```




