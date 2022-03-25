#ifndef _UTILITIES_
#define _UTILITIES_



#include "string.hpp"
#include <iostream>

String infix_to_postfix(String);
void postfix_to_assembly(String, std::ostream&);
String evaluate(String, String, String, std::ostream&, int);



#endif
