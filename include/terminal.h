#ifndef TERMINAL_H
#define TERMINAL_H

#include <vector>

// terminal.h

// run_cmd:
// Takes a vector of C-style strings (char*), representing the command and its arguments.
// Forks a child process, redirects its standard output, and executes the command.
// Captures the output using a custom pipe (mypipe) and prints it to the terminal.
// Returns 0 on success, non-zero on failure.
int run_cmd(std::vector<char*> argv);

// terminal_app:
// Implements a simple interactive terminal loop.
// Continuously prompts the user for input, parses it into command and arguments,
// and executes the command using run_cmd().
// Exits the loop when the user types "exit".
void terminal_app();

#endif // TERMINAL_H