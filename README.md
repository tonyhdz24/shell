# MISO Shell

**Author:** AntonioHernandez

**Version:** 1.0

**Date:** [InsertDate]

## Table of Contents

1. [Introduction](#1-introduction)
2. [Features](#2-features)
3. [Requirements](#3-requirements)
4. [Usage](#4-usage)
5. [Code Structure](#5-code-structure)
6. [Functions and Commands](#6-functions-and-commands)
7. [How It Works](#7-how-it-works)
8. [Future Improvements](#8-future-improvements)
9. [Acknowledgments](#9-acknowledgments)

## 1. Introduction

**MISO Shell** is a simple, lightweight command-line interpreter (shell) implemented in C. It reads user commands, tokenizes inputs, executes built-in functions, and manages system-level processes via `fork()` and `execvp()`.

The shell is designed for educational purposes, demonstrating basic concepts of operating systems, process management, and command-line tools.

## 2. Features


* **Command Input:** Reads commands from the user.
* **Command Parsing:** Tokenizes input strings into commands and arguments.
* **Built-in Commands:** Includes `cd`, `help`, and `exit`.
* **Program Execution:** Executes external programs via execvp().
* **Process Management:** Handles child processes using `fork()` and `waitpid()`.
* **Graceful Exit:** Allows users to terminate the shell with the exit command.

## 3. Requirements
* **Operating System:** Unix/Linux-based system (e.g., Ubuntu, macOS).
* **Compiler:** GCC (GNU Compiler Collection) or any C compiler.
* **C Standard:** C99 or later.

## 4. Usage
### Compilation

To compile the MISO Shell, use the following command:
```
gcc -o miso_shell miso_shell.c
```

### Execution

Run the compiled program:
```
./miso_shell
```
### Example Commands


* Built-in Commands:
    * `cd [directory]` - Change the current directory.
    * `help` - Display built-in commands.
    * `exit` - Exit the shell.
* External Commands:
    * ``ls`` - List files in the current directory.
    * ``echo Hello`` - Print "Hello" to the terminal.
## 5. Code Structure
The project is composed of the following key components:

* **Main Loop:** The miso_loop() function continuously reads, parses, and executes user commands.
* **Input Reading:** The miso_read() function reads a single line of input using fgets().
* **Command Parsing:** The miso_parse() function tokenizes input strings using strtok().
* **Command Execution:**
    * Built-in commands are handled by miso_exe() and builtin_func.
    * External programs are executed via fork() and execvp().

* **Utility Functions:** Helper functions such as strTrim() clean and format input.
## 6. Functions and Commands

### 6.1 Built-in Commands

| **Command** | **Description**                       | **Function Implementation**      |
|-------------|---------------------------------------|---------------------------------|
| `cd`       | Change the current working directory. | `int miso_cd(char **args)`      |
| `help`     | Display the list of built-in commands.| `int miso_help(char **args)`    |
| `exit`     | Exit the shell.                       | `int miso_exit(char **args)`    |

### 6.2 Core Functions

| **Function**      | **Purpose**                                                            |
|--------------------|------------------------------------------------------------------------|
| `miso_read()`      | Reads a line of input from the user using `fgets()`.                  |
| `miso_parse()`     | Tokenizes the input into command and arguments using `strtok()`.      |
| `miso_exe()`       | Executes built-in or external commands.                              |
| `miso_launch()`    | Launches external programs using `fork()` and `execvp()`.            |
| `strTrim()`        | Removes the trailing newline character from input strings.           |


## 7. How It Works
The MISO Shell follows a simple Read-Parse-Execute loop:

1. **Read:** The `miso_read()` function gets input from the user. It ensures the string does not exceed 80 characters and trims newline characters.
2. **Parse:** The `miso_parse()` function tokenizes the input string, splitting it into a command and its arguments. The tokens are stored in a dynamic array.
3. **Execute:** The miso_exe() function determines if the command is built-in.
    * Built-in Commands: Execute directly via builtin_func[].
    * External Commands: Use fork() to create a child process and execvp() to replace the process image. The parent process waits for the child to complete using waitpid().
4. **Loop:** The shell continues to prompt the user until the exit command is executed.

## 8. Future Improvements
* **Input Redirection and Piping:** Add support for input/output redirection (<, >) and pipes (|).
* **Background Processes:** Enable background execution using the & symbol.
* **Error Handling:** Improve error messages and edge-case handling.
* **History Management:** Store and recall previous commands using an arrow key history.
## 9. Acknowledgments
This project was inspired by simple shell implementations in operating system courses. Special thanks to resources like:
* GNU `bash` documentation
* The Linux manual pages (`man`)
### Contact
For any queries or feedback, feel free to reach out to:
**Antonio Hernandez:** tonyhernandez24@boisestate.edu


