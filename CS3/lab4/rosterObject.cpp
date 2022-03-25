// vector and list algorithms with objects in containers
// Mikhail Nesterenko
// 9/10/2018

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
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
     string repr = string(firstName_ + ' ' + lastName_);
     for (const string &course: classes_) {
        repr += ' ' + course;
     }
     return repr;
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

   void add_course(string coursename) {
      classes_.push_back(coursename);
   }
private:
   string firstName_;
   string lastName_;
   list<string> classes_;
};



int main(int argc, char* argv[]){

   if (argc <= 1){ cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" << endl; exit(1);}

   // master list of all students
   list<Student> allStudents;
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
            alreadyPresent = false;
            for (Student &studentEntry: allStudents) { // for all of the students we already have
                if (studentEntry == student) { // if the current student has the same name as one we already have
                    studentEntry.add_course(coursename); // add the course name to the student entry
                    alreadyPresent = true; // set the present flag to true
                    break; // stop looking
                }
            }

            if (!alreadyPresent) { // if they are not present
                isDropout = false;
                for (const auto &dropout: dropouts) { // look through the dropouts
                    if (student == dropout) { // if the student is in the dropout list
                        isDropout = true; // set the dropout flag to true
                        break; // stop looking
                    }
                }
                if (!isDropout) { // if they arent a dropout, make a new entry and add them to the roster
                    Student newStudent = Student(first, last); // create the new student
                    newStudent.add_course(coursename); // add the course
                    allStudents.push_back(newStudent); // add the new student to the master list
                }
            }
        }
        course.close();
    }


   allStudents.sort(); // sort the list

    // print all of the students
    for (auto &studentEntry: allStudents) {
        std::cout << studentEntry.print() << std::endl;
    }

}