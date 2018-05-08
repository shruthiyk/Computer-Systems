# Terminal Overview

"Name 10 terminal commands"

That was a prompt I was given when interviewing for LinkedIn. It's not that you should memorize 10 terminal commands, but rather you should understand that working on the terminal is an essential skill.

In this lab, you are going to perform a few terminal commands to get familiar with the Unix Environment.

## Part 0 - Obtain the mono repo

Run through the following github tutorial if you are not familiar with git.

https://try.github.io/levels/1/challenges/1

## Part 1 - SSH

The first thing you are going to need to do is learn how to SSH.

**I don't care what operating system you use as long as you have a terminal**

* For Windows Users installing Putty is sufficient. You might prefer to also install the bash shell from the Windows Store as well.
* For Linux/Mac users, you already have a terminal available! Just search for 'terminal'.

* Once your terminal is open, 'ssh' into ccis with: *ssh ccis_user_name_here@login.ccs.neu.edu*
  * If for some reason you do not have a ccis username, let me know. We'll have to e-mail operations.
* After you have successfully ssh'd, you are now running programs on the ccis servers (not locally on your machine).
* Now you may 'git clone' the mono repo to this location (Presumably you have done this if you are reading this text).

## Part 2 - The (at least) 10 Commands

Try running the followng commands.

- ls
- mkdir
- cd
- man
- rmdir
- sort
- cat
- nl
- cut
- grep

In fact, calling each of these 'commands' is not correct. Each of these is itself a program (typically implemented in C).

As an example, here is the source code for 'ls': http://git.savannah.gnu.org/cgit/coreutils.git/tree/src/ls.c
Each of these commands are part of the coreutils package in Unix. If you look through the source tree, you will additionally find many other programs (i.e. terminal commands you run in your shell) here: http://git.savannah.gnu.org/cgit/coreutils.git/tree/src/.


## Deliverable

* Copy and Paste the output of your commands above into a file called "output" (no capitalization, no file extension, exactly as named.)
