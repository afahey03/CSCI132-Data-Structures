/***************************
* CSCI132
* 9/2/22
* Aidan Fahey
* Run the functions imported from the Student.h file
****************************/

#include "Student.h"
#include <iostream>
#include <string>

int main() {
  Student s;	// an object to hold info about a student

  // Ask user to set the graduation date
  int yr;
  std::cout << "Enter graduation year: ";
  std::cin >> yr;
  s.setGradDate(yr);

  Student greatStudent("Aidan Fahey", 2025);
 
  // Ask user to enter courses
  while (true) {
    std::string course;
    std::cout << "Enter name of course to be added (or type \"done\" to stop): ";
    std::cin >> course;
    if (course == "done")
      break;
    s.addCourse(course);
  }
    greatStudent.addCourse("CSCI132");
    greatStudent.addCourse("GERM101");
    greatStudent.addCourse("SOCL101");
    greatStudent.addCourse("PHYS100");
  // Print out a summary
  s.printInfo();
  s.printCourses();
  greatStudent.printInfo();
  greatStudent.printCourses();

  return 0;
} // end main

  
 
