#include "utility.h"
#include <sstream>

// Converts vector of strings to vector of char* (C-style strings)
std::vector<char*> castArgs(const std::vector<std::string>& cmd) {
    std::vector<char*> argv;
    argv.reserve(cmd.size() + 1);
    for (const auto& s : cmd) {
        argv.push_back(const_cast<char*>(s.c_str()));
    }
    argv.push_back(nullptr);
    return argv;
}


// Converts a command string to a vector of words
std::vector<std::string> cmd2vec(const std::string& command, char delimiter) {
    std::vector<std::string> result;
    std::istringstream iss(command);
    std::string token;
    while (std::getline(iss, token, delimiter)) {
        if (!token.empty()) {
            result.push_back(token);
        }
    }
    return result;
}