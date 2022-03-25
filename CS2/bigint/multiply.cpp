//==============================================================================
// Basics for openning a file for milestone 2 of Project 1.
//
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "bigint.hpp"

int main() {
    std::ifstream in("data1-2.txt");    // Define stream for input
    if(!in) {                           // Make sure it opened correctly.
        std::cerr << "Could not open data1-1.txt, exiting." << std::endl;
        exit(1);
    }
    
    //Until end of file
       //Read two bigints
       //Print them out
       //Add them together
       //Print out results
    bigint b1;
    bigint b2;
    bigint b3;
    bigint empty;
    while(!in.eof()) {
      in >> b1;
      in >> b2;
      if(!(b1==empty) || !(b2==empty)) {
        std::cout << "b1=";
        b1.debugPrint(std::cout);
        std::cout << std::endl << "b2=";
        b2.debugPrint(std::cout);
        b3 = b1 * b2;
        std::cout << std::endl << "b3=";
        b3.debugPrint(std::cout);
        std::cout << std::endl;
      }
    }
    in.close();
    return 0;
}

