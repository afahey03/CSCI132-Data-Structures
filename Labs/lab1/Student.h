// File: Student.h
// Description: Specification for the Student class.
// Author: K. Walsh
// Edited by: Aidan Fahey on 9/5/22
// Class: CSCI 132
// Date: 12 July 2020
// Modified: 21 January 2021 by K. Walsh - updated some comments
// Initializes constructors and functions used in main.cpp

#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>

// A Student object holds information about a single student and the courses
// they are enrolled in.
class Student
{

public:

  // Adds a new course to this Student's list of courses.
  // Precondition:
  // 	There are less than 6 courses in the course list already.
  // Postcondition:
  // 	The given course is added to the list.
  void addCourse(std::string courseName);
  
  // Prints this Student's list of courses to standard output, one course per
  // line, with one blank line at the end.
  void printCourses(void) const;
 
  // Prints this Student's name and graduation date to standard output, each on a
  // separate line, with one blank line at the end.
  void printInfo(void) const;
 
  // Changes this Student's graduation.
  // Postcondition:
  //   The Student's graduation year is set to the given year.
  void setGradDate(int year);
 
  // Default constructor.
  // Postcondition:
  //	Initializes this Student's name to "Jane Doe".
  //	Initializes this Student's graduation date to 0,
  //	Initializes this Student's course list to be empty.
  Student();
 
  // Constructor with name and year.
  // Precondition:
  //   name is not empty
  //   year is positive
  // Postcondition:
  //	 Initializes this Student's name to the given name.
  //	 Initializes this Student's graduation date to the given year.
  //	 Initializes this Student's number list to be empty.
  Student(std::string name, int year);
    
private:

  std::string name;         // Name of the student, or "Jane Doe" by default.
  int gradDate;             // Graduation date, or zero if no date has been set.
  std::string courseOne;
  std::string courseTwo;
  std::string courseThree;
  std::string courseFour;
  std::string courseFive;
  std::string courseSix;
                            // List of courses the student is enrolled in.
  int numCourses;           // Number of courses student is enrolled in.

};

#endif
