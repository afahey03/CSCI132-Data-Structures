/***************************
* CSCI132
* 9/2/22
* Aidan Fahey
* Initialize a student variable, assign courses, set a graduation year, print out both.
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

  if (numCourses == 0) {
    numCourses++;
    courseOne = courseName;
  } else if (numCourses == 1) {
    numCourses++;
    courseTwo = courseName;
  } else if (numCourses == 2) {
    numCourses++;
    courseThree = courseName;
  } else if (numCourses == 3) {
    numCourses++;
    courseFour = courseName;
  } else if (numCourses == 4) {
    numCourses++;
    courseFive = courseName;
  } else if (numCourses == 5) {
    numCourses++;
    courseSix = courseName;
  }
  
} // end addCourses

void Student::printInfo(void) const {

  std::cout << gradDate << "\n";

} // end printInfo

void Student::printCourses(void) const {
  
  if (numCourses >= 1) {
  std::cout << courseOne << "\n";
  }
  if (numCourses >= 2) {
  std::cout << courseTwo << "\n";
  }
  if (numCourses >= 3) {
  std::cout << courseThree << "\n";
  }
  if (numCourses >= 4) {
  std::cout << courseFour << "\n";
  }
  if (numCourses >= 5) {
  std::cout << courseFive << "\n";
  }
  if (numCourses == 6) {
  std::cout << courseSix << "\n";
  }

  }
 //end printCourses

void Student::setGradDate(int year) {
  gradDate = year;
} // end setGradDate

