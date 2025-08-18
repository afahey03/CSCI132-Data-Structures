/***************************
* CSCI132
* 9/2/22
* Aidan Fahey
* Initialize a student variable, assign courses, set a graduation year, print out both.
* Copy of Student.cpp before changes were made to the addCourse and printCourses functions
****************************/

#include "Student.h"
#include <string>
#include <iostream>

Student::Student() {
  // Postcondition:
  //	 Initializes this Student's name to "Jane Doe".
  //	 Initializes this Student's graduation date to 0.
  //	 Initializes this Student's course list to be empty.
  name = "Jane Doe";
  gradDate = 0;
  numCourses = 0;
} // end default constructor

Student::Student(std::string name, int year) {
  // Precondition:
  //   name is not empty
  //   year is positive
  // Postcondition:
  //	 Initializes this Student's name to the given name.
  //	 Initializes this Student's graduation date to the given year.
  //	 Initializes this Student's number list to be empty.
  this -> name=name;
  gradDate = year;
  numCourses = 0;

} // end two-argument constructor

void Student::addCourse(std::string courseName) {
  // Precondition:
  // 	 There are less than 6 courses in the course list already.
  // Postcondition:
  // 	 The given course is added to the list.
  courses[numCourses] = courseName; 
  numCourses++;
} // end addCourses

void Student::printInfo(void) const {

  std::cout << gradDate << "\n";

} // end printInfo

void Student::printCourses(void) const {
  
  int n = 0;
  while (n < numCourses) {
    std::cout << courses[n] << "\n";
    n++;
  }

} //end printCourses

void Student::setGradDate(int year) {
  gradDate = year;
} // end setGradDate

