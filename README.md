![Holberton Logo](https://i.ibb.co/Tk2BZyT/wordmark-cherry72.png)
# Lightning Shell ⚡️

A simple shell

## Synopsis

A Unix shell is both a command interpreter and a programming language. As a
command interpreter, the shell provides the user interface to the rich set of
GNU utilities. The programming language features allow these utilities to be
combined. Files containing commands can be created, and become commands
themselves. These new commands have the same status as system commands in
directories such as /bin, allowing users or groups to establish custom
environments to automate their common tasks.

On this project, this program is a simple implementation of a shell.

## Description
This program runs and mimics like a simple UNIX command interpreter. 

Rundown of the program
- Gets user input
- Tokenize input
- Check builtins
- Check Environment and use PATH
- Use fork(), execve(), and wait()

## Requirements

-   Compiled on Ubuntu 14.04 LTS
-   Your programs and functions will be compiled with gcc 4.8.4 using the flags
    -Wall -Werror 
-Wextra and -pedantic
-   Follows the Betty style
-   No more than 5 functions per file
-   Prototypes of the functions are in the crikey.h header file

## Program Flow

The figure below shows the overview how the program flows acting as a simple
shell.

![Program Flow](https://i.ibb.co/nPhZhcg/lightning.png)
