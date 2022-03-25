#include "utilities.hpp"
#include "string.hpp"
#include "stack.hpp"
#include <iostream>
#include <vector>

String infix_to_postfix(String input) {
  if (input.findch(0,';') == -1) {
    return input;
  }
  std::vector<String> split_string = input.split(' ');
  std::vector<String>::iterator iter = split_string.begin();
  stack<String> st;
  String right, oper, left;
  while ((*iter)[0] != ';') {
    if (*iter == ')') {
      right = st.pop();
      oper = st.pop();
      left = st.pop();
      st.push(left + " " + right + " " + oper);
    } else if (*iter != '(') {
      st.push(*iter);
    }
    ++iter;
  }
  return st.pop();
}

void postfix_to_assembly(String input, std::ostream & out) {
  std::vector<String> split_string = input.split(' ');
  std::vector<String>::iterator iter = split_string.begin();
  stack<String> st;
  String right, left, token;
  int tmpNum = 0;
  while (iter != split_string.end()) {
    token = (*iter);
    if (token != '+' and token != '-' and token != '*' and token != '/') {
      st.push(token);
    } else {
      right = st.pop();
      left = st.pop();
      ++tmpNum;
      st.push(evaluate(left, token, right, out, tmpNum));
    }
    ++iter;
  }
}

String evaluate(String l, String t, String r, std::ostream & out, int tmpNum) {
  String oper;
  if (t == '+') {
    oper = "AD";
  } else if (t == '-') {
    oper = "SB";
  } else if (t == '*') {
    oper = "MU";
  } else if (t == '/') {
    oper = "DV";
  }
  out << "   LD     " << l << "\n   " << oper << "     " << r << "\n   ST     TMP" << tmpNum << std::endl;
  String ret = String("TMP") + String(char(tmpNum + '0'));
  return ret;
}
