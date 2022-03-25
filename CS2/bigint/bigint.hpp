#ifndef _BIGINT_HPP_
#define _BIGINT_HPP_

#include <iostream>

const int CAPACITY = 400;

class bigint {
public:
  bigint();
  bigint(int);
  bigint(const char[]);
  void debugPrint(std::ostream&) const;
  bigint operator+(const bigint&) const;
  bigint timesDigit(int rhs) const;
  bigint times10(int rhs) const;
  bigint operator*(const bigint&) const;
  bool operator==(const bigint&);
  int operator[](int i);
  friend std::ostream& operator<<(std::ostream& os, const bigint& rhs);
  friend std::istream& operator>>(std::istream& is, bigint& rhs);
private:
  int value[CAPACITY] = {0};
};

#endif
