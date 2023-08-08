# Advanced-Unix-Shell-with-Pipelines-and-Command

This project implements an advanced Unix shell that supports pipelines and command assignment. The shell provides features such as running multiple commands in pipelines and assigning the output of one command as the input of another. It leverages concepts from Unix systems programming and demonstrates the use of various system calls and C programming features.

## Features

- Pipelines: The shell supports the execution of multiple commands in a pipeline, where the output of one command is used as the input of the next command.
- Command Assignment: Commands can be assigned to variables using the assignment operator "=".
- Random Quotes: The shell displays a random quote before each prompt, providing an element of surprise and motivation.

## How It Works

The shell reads user input and processes it based on the presence of pipeline symbols "|" or assignment symbols "=" within the input line. The project utilizes advanced C concepts, such as pipes and the execvp function, to execute commands and manage communication between processes. Child processes are created to execute the individual commands within pipelines.

## Usage

1. Compile the project using a C compiler (e.g., `gcc`).

```bash
gcc -o shell shell.c
