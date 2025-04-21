#ifndef UTILITY_H
#define UTILITY_H

#include <vector>
#include <string>

//utility.h

// Converts vector of strings to vector of char* (C-style strings)
std::vector<char*> castArgs(const std::vector<std::string>& cmd);


// Converts a command string to a vector of words
std::vector<std::string> cmd2vec(const std::string& command, char delimiter = ' ');


#endif // UTILITY_H