#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include "WordList.hpp"
#include <assert.h>
#include <cctype>

int main(int argc, char* argv[]) {
    if (argc != 2) { // If the correct number of arguments is not given, exit with an error
        std::cout << "Please invoke with exactly one arguments." << std::endl;
        return -1;
    }

    std::ifstream file;
    file.open(argv[1]);

    std::string line, word;
    char current_char;

    WordList wordList = WordList();

    while (!file.eof()) {
        getline(file, line);
        for (int i = 0; i < line.length(); ++i) {
            current_char = line[i];
            if (isalnum(current_char)) {
                word += current_char;
            } else if (isspace(current_char)) {
                wordList.addWord(word);
                word.clear();
            }
        }
        if (!word.empty()) {
            wordList.addWord(word);
            word.clear();
        }
    }

    wordList.print();

    return 0;
}