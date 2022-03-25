#include "utilities.hpp"
#include "string.hpp"
#include <iostream>
#include <fstream>


int main(int argc, char* argv[]) {
  std::ifstream infile;
  std::ofstream outfile;
  infile.open(argv[1],std::ios::in);
  if (argc == 3) {
    outfile.open(argv[2],std::ios::out);
  }
  char tmp_char_array[1000];
  if (infile.is_open()) {
    while (!infile.eof()) {
      infile.getline(tmp_char_array,1000);
      if (argc == 2) {
        std::cout << infix_to_postfix(tmp_char_array) << std::endl;
      } else if (argc == 3) {
	outfile << infix_to_postfix(tmp_char_array) << '\n';
      }
    }
    infile.close();
    if (argc == 3) {
      outfile.close();
    }
  } else {
    std::cout << "Could not open file." << std::endl;
  }
}
