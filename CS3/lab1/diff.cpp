#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

struct file { // Create a struct to hold members of the files that we will use
    std::string name; // File name
    int nameLength; // Length of the file name
    std::ifstream stream; // The stream to read from
    std::string currentLine; // The line we are currently on
};

void updateCurrentLine(file &f) {
    if (!f.stream.eof()) { // If we haven't reached the end of file
        getline(f.stream, f.currentLine); // Get the next line
    } else { // Otherwise
        f.currentLine = ""; // Put an empty string in the current line variable
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) { // If the correct number of arguments is not given, exit with an error
        std::cout << "Please invoke with exactly two arguments." << std::endl;
        return -1;
    }

    int line = 1; // Initial line number

    file file1; // Initialize file 1
    file1.name = argv[1];
    file1.nameLength = file1.name.length();
    file1.stream.open(file1.name);

    file file2; // Initialize file 2
    file2.name = argv[2];
    file2.nameLength = file2.name.length();
    file2.stream.open(file2.name);

    int errorcolumn; // Declare an integer to store the column number of the difference

    while (!file1.stream.eof() || !file2.stream.eof()) { // While we haven't reached the end of file for both files
        updateCurrentLine(file1); // Update the line stored in file 1
        updateCurrentLine(file2); // Update the line stored in file 2

        if (file1.currentLine.compare(file2.currentLine) != 0) { // If the two current lines are not equal
            errorcolumn = 0; // Reset the error column
            for (int i = 0; i < file1.currentLine.length(); ++i) { // Go through every character in file 1's current line
                if (file1.currentLine[i] != file2.currentLine[i]) { // If the character doesn't match the corresponding character in file 2, break
                    break;
                }
                ++errorcolumn; // If we haven't found the error yet, try the next column
            } // If we get here without finding the error, it means that file 2's line is larger than file 1's line and the carrot goes right after file 1's line terminates
            std::cout << file1.name << ": " << line << ": " << file1.currentLine << std::endl; // Print file 1's line
            std::cout << file2.name << ": " << line << ": " << file2.currentLine << std::endl; // Print file 2's line
            std::cout << std::string(file1.nameLength + log10(line) + 5 + errorcolumn, ' ') << '^' << std::endl; // Print the carrot at the correct location
        }
        
        ++line; // Increase the line number
    }
    return 0;
}