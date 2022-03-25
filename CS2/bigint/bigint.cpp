#include "bigint.hpp"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const bigint& rhs) {
  bool floating = true;
  int digitCount = 0;
  for(int i = CAPACITY-1;i>=0;--i) {
    if(rhs.value[i]!=0) {
      floating = false;
    }
    if(floating==false || i==0) {
      os << rhs.value[i];
      ++digitCount;
      if(digitCount%80==0) {
	os << "\n";
      }
    }
  }
  return os;
}

std::istream& operator>>(std::istream& is, bigint& rhs) {
  char c = ' ';
  char tempString[CAPACITY];
  int index = 0;
  for(int i = 0;i < CAPACITY;++i) {
    rhs.value[i] = 0;
  }
  while(c!=';' && !is.eof()) {
    is.get(c);
    if(c-'0' >= 0 && c-'0' <= 9) {
      tempString[index] = c-'0';
      ++index;
    }
  }
  for(int i = 0;i < index;++i) {
    rhs.value[i] = tempString[index-1-i];
  }
  return is;
}

bigint::bigint() {
  
}

bigint::bigint(int n) {
  for(int i = 0;n>0;++i) {
    value[i] = n%10;
    n/=10;
  }
}

bigint::bigint(const char n[]) {
  int charLen = 0;
  for(int i = 0;*(n+i);++i) {
    charLen = i;
  }
  for(int i = charLen;i>=0;--i) {
    value[i] = n[charLen-i] - '0';
  }
}

void bigint::debugPrint(std::ostream& out) const {
  for(int i = CAPACITY-1;i>=0;--i) {
    out << value[i] << "|";
  }
  out << std::endl;
}

bool bigint::operator==(const bigint& rhs) {
  for(int i = 0;i<CAPACITY;++i) {
    if(value[i]!=rhs.value[i]) {
      return false;
    }
  }
  return true;
}

bigint bigint::operator+(const bigint& rhs) const{
  int carry = 0;
  bigint ret;
  for(int i = 0;i<CAPACITY;++i) {
    ret.value[i] = (value[i] + rhs.value[i] + carry)%10;
    carry = (value[i] + rhs.value[i] + carry)/10;
  }
  return ret;
}

bigint bigint::timesDigit(int rhs) const {
  int carry = 0;
  bigint ret;
  for(int i = 0;i<CAPACITY;++i) {
    ret.value[i] = (value[i] * rhs + carry)%10;
    carry = (value[i] * rhs + carry)/10;
  }
  return ret;
}

bigint bigint::times10(int rhs) const {
  bigint ret;
  for(int i = 0;i < CAPACITY - rhs;++i) {
    ret.value[i+rhs] = value[i];
  }
  return ret;
}

bigint bigint::operator*(const bigint& rhs) const{
  bool bothBlank = true;
  for(int i = 0;i < CAPACITY;++i) {
    if(value[i]!=0 || rhs.value[i]!=0) {
      bothBlank = false;
      break;
    }
  }
  bigint product;
  if(bothBlank==false) {
    bigint temp;
    int maxLength;
    for(int i = 0;i < CAPACITY;++i) {
      if(value[i]!=0 || rhs.value[i]!=0) {
        maxLength = i + 1;
      }
    }
    for(int i = 0;i < maxLength;++i) {
      temp = timesDigit(rhs.value[i]);
      product = product + temp.times10(i);
    }
  }

  
  return product;
}

int bigint::operator[](int i) {
  return value[i];
}
