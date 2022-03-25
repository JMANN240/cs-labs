#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include <string>
#include <fstream>

using std::string; using std::ofstream;

class Logger {
public:
    static Logger& instance();
    void report(const string&);
private:
    Logger() {}
    Logger(const Logger&) {}
    Logger& operator=(const Logger&) {}
    ofstream os;
};

#endif