#include "terminal.h"
#include "mypipe.h"
#include "utility.h"

#include <iostream>
#include <vector>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>

// run_cmd:
// Takes a vector of C-style strings (char*), representing the command and its arguments.
// Forks a child process, redirects its standard output, and executes the command.
// Captures the output using a custom pipe (mypipe) and prints it to the terminal.
// Returns 0 on success, non-zero on failure.
int run_cmd(std::vector<char*> argv) {
    mypipe p;
    pid_t pid = fork();
    if (pid < 0) {
        return 1;
    }
    if (pid == 0) {
        p.redirect();
        execvp(argv[0], argv.data());
        std::exit(1);
    } else {
        std::string out = p.read();
        int status = 0;
        waitpid(pid, &status, 0);
        std::cout << out;
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        } else {
            return 1;
        }
    }
}

// terminal_app:
// Implements a simple interactive terminal loop.
// Continuously prompts the user for input, parses it into command and arguments,
// and executes the command using run_cmd().
// Exits the loop when the user types "exit".
void terminal_app() {
    std::string line;
    while (true) {
        std::cout << "> " <<std::flush;
        if (!std::getline(std::cin, line)) {
            break;
        }
        if (line.empty()) {
            continue;
        }
        if (line == "exit") {
            break;
        }

        auto parts = cmd2vec(line);
        auto argv = castArgs(parts);
        run_cmd(argv);
    }
}