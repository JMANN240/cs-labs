#include "logger.hpp"
#include <fstream>
#include <iostream>

Logger& Logger::instance() {
    static Logger l;
    return l;
}

void Logger::report(const string& s) {
    os.open("log.txt", std::fstream::out | std::fstream::app);
    os << s;
    os.close();
}