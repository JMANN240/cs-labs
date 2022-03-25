//
//
// File:        logentry.cpp  
//       
// Version:     1.0
// Date:        
// Author:      
//
// Description: Class implementation for a log entry.
//
//

////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>

#include "string.hpp" 
#include "logentry.hpp"

////////////////////////////////////////////////////////// 
// REQUIRES:  
// ENSURES: 
//
LogEntry::LogEntry(String s) {
    vec = s.split(' ');
    if (vec.size() == 10) {
        std::vector<String> dt = vec[3].split(':');
        std::vector<String> d = dt[0].split('/');
        host = vec[0];
        date.setDay(d[0].substr(1,2));
        date.setMonth(d[1]);
        date.setYear(d[2].toint());
        time.setHour(dt[1].toint());
        time.setMinute(dt[2].toint());
        time.setSecond(dt[3].toint());
        request = vec[5] + vec[6] + vec[7];
        status = vec[8];
        if (vec[9]=='-') {
            number_of_bytes = 0;
        } else {
            number_of_bytes = vec[9].toint();
        }
    } else {
        number_of_bytes = 0;
    }
}

////////////////////////////////////////////////////////// 
// REQUIRES:  
// ENSURES: 
//
std::vector<LogEntry> parse(std::istream& in) {
    std::vector<LogEntry> result;
    char tmpCharArray[10000];
    while (!in.eof()) {
        in.getline(tmpCharArray, 10000);
        LogEntry tmpLogEntry(tmpCharArray);
        result.push_back(tmpLogEntry);
    }
    return result;
}

////////////////////////////////////////////////////////// 
// REQUIRES:  
// ENSURES: 
//
void output_all(std::ostream& out, const std::vector<LogEntry>& v) {
    for(size_t i = 0; i < v.size(); ++i) {
        out << v[i] << std::endl;
    }
}

////////////////////////////////////////////////////////// 
// REQUIRES:  
// ENSURES: 
//
void by_host(std::ostream& out, const std::vector<LogEntry>& v) {
    for(size_t i = 0; i < v.size(); ++i) {
        out << v[i].host << std::endl;
    }
}

////////////////////////////////////////////////////////// 
// REQUIRES:  
// ENSURES: 
//
int byte_count(const std::vector<LogEntry> & v) {
    int bytes = 0;
    for(size_t i = 0; i < v.size(); ++i) {
        bytes+=v[i].number_of_bytes;
    }
    return bytes;
}

std::ostream& operator<<(std::ostream& out, const LogEntry& log) {
    for(size_t i = 0; i < log.vec.size();++i) {
        out << log.vec[i] << ' ';
    }
    return out;
}

void Date::setDay(String d) {
    day = d;
}

void Date::setMonth(String m) {
    month = m;
}

void Date::setYear(int y) {
    year = y;
}

void Time::setHour(int h) {
    hour = h;
}

void Time::setMinute(int m) {
    minute = m;
}

void Time::setSecond(int s) {
    second = s;
}