#include "mypipe.h"
#include <unistd.h>
#include <iostream>
#include <sys/wait.h>

mypipe::mypipe() {
	auto status{ pipe(fd.data()) };
	if (status < 0) {
		exit(1);
	}
}

mypipe::~mypipe() {
	::close(fd[0]);
	::close(fd[1]);
}

void mypipe::redirect() {
	if (::dup2(fd[1], STDOUT_FILENO) == -1) {
		std::exit(1);
	}
	::close(fd[0]);
	::close(fd[1]);
}

std::string mypipe::read() {
    ::close(fd[1]);               // close write end in parent
    std::array<char,256> buf;
    std::string out;
    ssize_t n;
    // loop if you want to drain fully
    while ((n = ::read(fd[0], buf.data(), buf.size())) > 0) {
        out.append(buf.data(), n);
    }
    ::close(fd[0]);
    return out;
}