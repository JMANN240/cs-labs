#include "logger.hpp"

void foo() {
    Logger::instance().report("In Foo\n");
}

void bar() {
    Logger::instance().report("In Bar\n");
}

int main() {
    Logger::instance().report("In Main\n");
    foo();
    bar();
}