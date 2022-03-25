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
	std::cout << "Infix Expression: " << tmp_char_array << "\nPostfix Expression: " << infix_to_postfix(tmp_char_array) << std::endl;
        postfix_to_assembly(infix_to_postfix(tmp_char_array), std::cout);
      } else if (argc == 3) {
        outfile << "Infix Expression: " << tmp_char_array << "\nPostfix Expression: " << infix_to_postfix(tmp_char_array) << std::endl;
	postfix_to_assembly(infix_to_postfix(tmp_char_array),outfile);
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
