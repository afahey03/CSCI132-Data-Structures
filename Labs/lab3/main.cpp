// Lab 3 code for playing with pointers and memory management
// Author: K. Walsh
// Date: July 25, 2020

#include "Student.h"
#include "Course.h"
#include "ArrayBag.h"
#include "LinkedSet.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void enrollRandomCourses(LinkedSet<Course *> &courses, Student *stu, int count) {
  for (int i = 0; i < count; i++)
  {
    Course *c = courses.pickRandom();
    while (stu->isEnrolled(c))
    {
      c = courses.pickRandom();
    }
    cout << "Enrolling " << stu->getName() << " in " << c->getDescription() << "\n";
    c->enroll(stu);
  }
}

int main(void)
{
  // Create some students records
  Student *a = new Student("Salif Kieta", 2024);
  Student *b = new Student("Bojana Novakovic", 2022);
  Student *c = new Student("Judith Gutierrez", 2023);

  // Create a list of available courses
  LinkedSet<Course*> courses;
  courses.add(new Course("CSCI 131", "Techniques of Programming", 32));
  courses.add(new Course("MUSC 242", "Coding Music", 19));
  courses.add(new Course("CLAS 151", "History of Ancient Rome", 16));
  courses.add(new Course("THEA 229", "Virtual Realities", 16));
  courses.add(new Course("CSCI 328", "Coding Music", 16));
  courses.add(new Course("VAST 105", "Digital Arts Studio 1", 16));

  // Enroll students in some random courses
  // TODO: Update the number of courses for each student
  // after diagramming memory
  enrollRandomCourses(courses, a, 5);
  enrollRandomCourses(courses, b, 5);
  enrollRandomCourses(courses, c, 5);

  // Print the student schedules
  cout << "==== Schedules for all students ====\n";
  a->printInfo();
  a->printCourses();
  b->printInfo();
  b->printCourses();
  c->printInfo();
  c->printCourses();

  // Print the course rosters
  // Note: ArrayBag doesn't have an easy way to enumerate the items, so
  // we allocate a new simple array here and fill it with the courses.
  cout << "==== Rosters for all courses ====\n";
  int n = courses.size();
  for (int i = 0; i < n; i++) {
    courses.get(i)->printRoster();
  }

  cout << "READY!\n";

  cout << "Judith's new friend is ... " << c->getSchedule().pickRandom()->getRoster().pickRandom()->getName() << "\n";

  a->remove(a->getSchedule().pickRandom());
  b->remove(b->getSchedule().pickRandom());
  c->remove(c->getSchedule().pickRandom());

  cout << "==== Revised schedules for all students ====\n";
  cout << "Salif Kieta:" << "\n";
  a->printCourses();
  cout << "Bojana Novakovic:" << "\n";
  b->printCourses();
  cout << "Judith Gutierrez:" << "\n";
  c->printCourses();

  ArrayBag <Course*> favorite;
  favorite.add(a->getSchedule().pickRandom());
  favorite.add(b->getSchedule().pickRandom());
  favorite.add(c->getSchedule().pickRandom());
  cout << "==== Tallies for each course ====\n";
  for (int i = 0; i < courses.size(); i++) {
    cout << favorite.getFrequencyOf(courses.get(i)) << " " << courses.get(i)->getDescription() << "\n";
  }

}
