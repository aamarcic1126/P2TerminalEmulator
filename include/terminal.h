#ifndef TERMINAL_H
#define TERMINAL_H

#include <vector>

// Forks+execs argv, captures its stdout via mypipe, prints it.
// Returns child’s exit code or non-zero on error.
int run_cmd(std::vector<char*> argv);

// Simple REPL: prompt “> ”, read line, split/exec, loop until “exit”.
void terminal_app();

#endif  // TERMINAL_H