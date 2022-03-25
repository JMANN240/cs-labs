#include <iostream>
#include <cassert>
#include "string.hpp"

String::String() {
  stringSize = 1;
  str = new char[stringSize];
  str[0] = '\0';
}

String::String(char c) {
  if(c != '\0') {
    stringSize = 2;
    str = new char[stringSize];
    str[0] = c;
    str[1] = '\0';
  } else {
    stringSize = 1;
    str = new char[stringSize];
    str[0] = '\0';
  }
}

String::String(const char cArray[]) {
  stringSize = 0;
  while(true) {
    ++stringSize;
    if(cArray[stringSize-1]=='\0') {
      break;
    }
  }
  str = new char[stringSize];
  for(int i = 0;i < stringSize;++i) {
    str[i] = cArray[i];
    if(cArray[i]=='\0') {
      break;
    }
  }
}

String::String(const String& old) {
  stringSize = old.stringSize;
  str = new char[stringSize];
  for(int i = 0;i < stringSize;++i) {
    str[i] = old.str[i];
  }
}

String::~String() {
  delete [] str;
}

void String::swap(String& rhs) {
  char *tmpPtr = str;
  int tmpSize = stringSize;
  str = rhs.str;
  stringSize = rhs.stringSize;
  rhs.str = tmpPtr;
  rhs.stringSize = tmpSize;
}

String& String::operator=(String rhs) {
  stringSize = rhs.stringSize;
  str = new char[stringSize];
  for(int i = 0;i < stringSize;++i) {
    str[i] = rhs.str[i];
  }
  return (*this);
}

char String::operator[](int index) const {
  if(index < 0) {
    index = 0;
  }
  if(index >= length()) {
    index = length() - 1;
  }
  return str[index];
}

char & String::operator[](int index) {
  if(index < 0) {
    index = 0;
  }
  if(index >= length()) {
    index = length() - 1;
  }
  return str[index];
}

int String::capacity() const {
  return stringSize - 1;
}

int String::length() const {
  int tmpLength = 0;
  while(true) {
    if(str[tmpLength]=='\0') {
      break;
    }
    ++tmpLength;
  }
  return tmpLength;
}

String String::substr(int start, int end) const {
  if(start < 0) {
    start = 0;
  }
  if(start > length() - 1) {
    start = length() - 1;
  }
  if(end < 0) {
    end = 0;
  }
  if(end > length() - 1) {
    end = length() - 1;
  }
  if(start > end) {
    String ret;
    return ret;
  }
  String ret(end-start+1);

  for(int i = start;i <= end;++i) {
    ret.str[i - start] = str[i];
  }
  ret.str[end-start+1] = '\0';
  return ret;
}

int String::findch(int pos, char c) const {
  int end = length() - 1;
  if(pos < 0) {
    pos = 0;
  }
  if(pos > end) {
    pos = end;
  }
  int index = -1;
  for(int i = pos;i <= end;++i) {
    if(str[i] == c) {
      index = i;
      break;
    }
  }
  return index;
}

int String::findstr(int pos, const String& st) const {
  int end = length() - st.length();
  if(pos < 0) {
    pos = 0;
  }
  if(pos > end) {
    return -1;
  }
  for(int i = pos;i <= end;++i) {
    if(substr(i,i+(st.length()-1)) == st) {
      return i;
    }
  }
  return -1;
}

String String::operator+(const String& rhs) const {
  int len1 = length();
  int len2 = rhs.length();
  int lenT = len1 + len2;

  String ret(lenT);
  
  for(int i = 0; i < len1;++i) {
    ret.str[i] = str[i];
  }
  
  for(int i = len1; i < lenT; ++i) {
    ret.str[i] = rhs.str[i - len1];
  }
  ret.str[lenT] = '\0';
  return ret;
}

String operator+(const char c, const String& s) {
  return String(c) + s;
}

String operator+(const char cArray[], const String& s) {
  return String(cArray) + s;
}

String& String::operator+=(const String& rhs) {
  int len1 = length();
  int len2 = rhs.length();
  int lenT = len1 + len2;
  resetCapacity(lenT);
  for(int i = len1; i < lenT; ++i) {
    str[i] = rhs.str[i - len1];
  }
  str[lenT] = '\0';
  return (*this);
}

bool String::operator==(const String& rhs) const {

  if(length() != rhs.length()) {
    return false;
  }
  for(int i = 0;i < stringSize;++i) {
    if(str[i] != rhs.str[i]) {
      return false;
    } else if (str[i] == '\0') {
      return true;
    }
  }
  return true;
}

bool operator==(const char c, const String& s) {
  return String(c) == s;
}

bool operator==(const char cArray[], const String& s) {
  return String(cArray) == s;
}

bool operator!=(const String& lhs, const String& rhs) {
  return !(lhs==rhs);
}

bool String::operator<(const String& rhs) const {
  for(int i = 0;i < stringSize;++i) {
    if(str[i] > rhs.str[i]) {
      return false;
    } else if(str[i] < rhs.str[i]) {
      return true;
    }
  }
  return false;
}

bool operator<(const char c, const String& s) {
  return String(c) < s;
}

bool operator<(const char cArray[], const String& s) {
  return String(cArray) < s;
}

bool operator>(const String& lhs, const String& rhs) {
  return (!(lhs < rhs) && (lhs!=rhs));
}

bool operator<=(const String& lhs, const String& rhs) {
  return ((lhs<rhs) || (lhs==rhs));
}

bool operator>=(const String& lhs, const String& rhs) {
  return !(lhs < rhs);
}

std::istream& operator>>(std::istream& in, String& s) {
  char buf[1000];
  in >> buf;
  int bufferLength = 0;
  for(;buf[bufferLength]!='\0';++bufferLength);
  s.resetCapacity(bufferLength);
  for(int i = 0;i < bufferLength;++i) {
    s.str[i] = buf[i];
  }
  return in;
}

std::ostream& operator<<(std::ostream& out, const String& s) {
  for(int i = 0;i < s.length();++i) {
    out << s[i];
  }
  return out;
}

String::String(int cap) {
  stringSize = cap + 1;
  str = new char[stringSize];
  str[cap] = '\0';
}

String::String(int cap, const char cArray[]) {
  stringSize = cap + 1;
  str = new char[stringSize];
  str[cap] = '\0';
  int cArraySize = 0;
  while(true) {
    if(cArray[cArraySize]=='\0' or cArraySize == cap) {
      break;
    }
    ++cArraySize;
  }

  if (cArraySize == 0) {
    str[0] = '\0';
  }

  for(int i = 0;i < cArraySize;++i) {
    if(cArray[i]=='\0') {
      break;
    }
    str[i] = cArray[i];
  }
}

void String::resetCapacity(int cap) {
  stringSize = cap + 1;
  char *newStr = new char[stringSize];
  newStr[cap] = '\0';

  for(int i = 0;i < stringSize - 1;++i) {
    newStr[i] = str[i];
  }
  delete [] str;
  str = newStr;
}

std::vector<String> String::split (char splitChar) const {
  std::vector<String> ret;
  String tmp;
  String empty;
  for(int i = 0; i < length() + 1; ++i) {
    if (str[i] == splitChar or str[i] == '\0') {
      ret.push_back(tmp);
      tmp = empty;
    } else {
      tmp+=str[i];
    }
  }
  return ret;
}

int String::toint() const {
  int ret = 0;
  for (int i = 0;i < length();++i) {
    ret = (ret * 10) + (str[i] - '0');
  }
  return ret;
}