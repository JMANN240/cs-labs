// vector and list algorithms with objects in containers
// Mikhail Nesterenko
// 9/10/2018

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <map>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector; using std::map;
using std::cout; using std::endl;
using std::move;


class Student{
public:
   Student(string firstName, string lastName): 
      firstName_(firstName), lastName_(lastName) {}
 
   // move constructor, not really needed, generated automatically
   Student(Student && org):
      firstName_(move(org.firstName_)),
      lastName_(move(org.lastName_))
   {}
  
   // force generation of default copy constructor
   Student(const Student & org) = default;
   
  string print() const {
     return firstName_ + ' ' + lastName_;
   }

    // needed for unique() and for remove()
   friend bool operator== (Student left, Student right){
      return left.lastName_ == right.lastName_ &&
	     left.firstName_ == right.firstName_;
   }

   // needed for sort()
   friend bool operator< (Student left, Student right){
      return left.lastName_ < right.lastName_ ||
	     (left.lastName_ == right.lastName_ && 
	      left.firstName_ < right.firstName_);
   }
private:
   string firstName_;
   string lastName_;
};



int main(int argc, char* argv[]){

   if (argc <= 1){ cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" << endl; exit(1);}

   // master list of all students
   map<Student, list<string>> allStudents;
   string filename, coursename, first, last;
   
   // read in the dropouts
   list<Student> dropouts;
    ifstream dropoutsFile(argv[argc-1]);
    while(dropoutsFile >> first >> last) {
        Student dropout = Student(first, last);
        dropouts.push_back(move(dropout));
    }
    dropoutsFile.close(); 

   // go through every course roster
   for (int i = 1; i < argc - 1; ++i) {
        filename = string(argv[i]); // get the file name
        coursename = filename.substr(0, filename.find_first_of('.')); // get the course name from the file name
        ifstream course(filename); // open an ifstream of file name
        bool alreadyPresent, isDropout; // initialize some flags
        while (course >> first >> last) { // while there are names to read in the roster
            Student student = Student(first, last); // create the student
            isDropout = false;
            for (const auto &dropout: dropouts) { // look through the dropouts
                if (student == dropout) { // if the student is in the dropout list
                    isDropout = true; // set the dropout flag to true
                    break; // stop looking
                }
            }
            if (!isDropout) {
                allStudents[student].push_back(coursename);
            }
        }
        course.close();
    }

    // print all of the students
    for (const auto &studentEntry: allStudents) {
        std::cout << studentEntry.first.print();
        for (const string &course: studentEntry.second) {
            std::cout << ' ' << course;
        }
        std::cout << std::endl;
    }

}