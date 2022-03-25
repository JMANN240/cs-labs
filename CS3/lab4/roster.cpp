// vector and list algorithms
// Mikhail Nesterenko
// 3/11/2014

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::list;
using std::move;
using std::string;
using std::vector;

int main(int argc, char *argv[]) {

    if (argc <= 1) {
        cout << "usage: " << argv[0] << " list of courses, dropouts last" << endl;
        exit(1);
    }

    // master list of all students
    list<list<string>> allStudents;
    string filename, coursename, studentname, first, last;

    // read all of the dropouts into a list
    list<string> dropouts;
    ifstream dropoutsFile(argv[argc-1]);
    while(dropoutsFile >> first >> last) {
        studentname = string(first + ' ' + last);
        dropouts.push_back(move(studentname));
    }
    dropoutsFile.close();

    // go through every course roster
    for (int i = 1; i < argc - 1; ++i) {
        filename = string(argv[i]); // get the file name
        coursename = filename.substr(0, filename.find_first_of('.')); // get the course name from the file name
        ifstream course(filename); // open an ifstream of file name
        bool alreadyPresent, isDropout; // initialize some flags
        while (course >> first >> last) { // while there are names to read in the roster
            studentname = string(first + ' ' + last);
            alreadyPresent = false;
            for (list<string> &studentEntry: allStudents) { // for all of the students we already have
                if (studentEntry.front() == studentname) { // if the current student has the same name as one we already have
                    studentEntry.push_back(coursename); // add the course name to the student entry
                    alreadyPresent = true; // set the present flag to true
                    break; // stop looking
                }
            }

            if (!alreadyPresent) { // if they are not present
                isDropout = false;
                for (const auto &dropoutname: dropouts) { // look through the dropouts
                    if (studentname == dropoutname) { // if the student is in the dropout list
                        isDropout = true; // set the dropout flag to true
                        break; // stop looking
                    }
                }
                if (!isDropout) { // if they arent a dropout, make a new entry and add them to the roster
                    list<string> newStudent;
                    newStudent.push_back(move(studentname));
                    newStudent.push_back(coursename);
                    allStudents.push_back(newStudent);
                }
            }
        }
        course.close();
    }

    allStudents.sort(); // sort the list

    // print all of the students
    for (auto &studentEntry: allStudents) {
        for (auto &str: studentEntry) {
            std::cout << str << ' ';
        }
        std::cout << std::endl;
    }
}