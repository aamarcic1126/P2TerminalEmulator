#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "terminal.h"
#include "utility.h"
#include <sstream>
#include <vector>
#include <string>

TEST_CASE("cmd2vec splits a simple command line", "[utility]") {
    auto v = cmd2vec("ls -l /home/user", ' ');
    REQUIRE(v.size() == 3);
    REQUIRE(v[0] == "ls");
    REQUIRE(v[1] == "-l");
    REQUIRE(v[2] == "/home/user");
}

TEST_CASE("cmd2vec collapses extra spaces", "[utility]") {
    auto v = cmd2vec("   echo    hello   world  ", ' ');
    REQUIRE(v.size() == 3);
    REQUIRE(v[0] == "echo");
    REQUIRE(v[1] == "hello");
    REQUIRE(v[2] == "world");
}

TEST_CASE("castArgs produces a null‑terminated argv array", "[utility]") {
    std::vector<std::string> in = {"foo", "bar", "baz"};
    auto argv = castArgs(in);

    // Expect 4 pointers: 3 args + terminating nullptr
    REQUIRE(argv.size() == 4);
    REQUIRE(std::string(argv[0]) == "foo");
    REQUIRE(std::string(argv[1]) == "bar");
    REQUIRE(std::string(argv[2]) == "baz");
    REQUIRE(argv[3] == nullptr);
}

TEST_CASE("run_cmd captures stdout of echo", "[terminal]") {
    std::vector<std::string> parts = { "echo", "hello" };
    auto argv = castArgs(parts);

    // 1) swap out cout’s buffer for an ostringstream
    std::ostringstream oss;
    auto*  old_buf = std::cout.rdbuf(oss.rdbuf());

    // 2) run the command
    int code = run_cmd(argv);

    // 3) restore cout’s original buffer
    std::cout.rdbuf(old_buf);

    REQUIRE(code == 0);
    REQUIRE(oss.str() == "hello\n");
}

TEST_CASE("run_cmd returns non-zero on invalid command", "[terminal]") {
    std::vector<std::string> parts = { "no_such_cmd" };
    auto argv = castArgs(parts);

    // redirect to swallow output
    std::ostringstream oss;
    auto* old_buf = std::cout.rdbuf(oss.rdbuf());

    int code = run_cmd(argv);

    std::cout.rdbuf(old_buf);

    REQUIRE(code != 0);
    // output is in oss.str(), if you want to inspect it
}