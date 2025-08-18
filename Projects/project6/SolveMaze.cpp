/*********************************************************************************
 * Name: Aidan Fahey
 * Date: 10/30/22
 * Implemented solveMaze()
 * Date: Fall 2021
 * Course: CSCI 132
 * Assignment: Lab 8
 * Instructor: Fitzsimmons
 * Program: SolveMaze.cpp
 * Purpose: Create a random maze and solves it recursively.
 ********************************************************************************/

#include <iostream>
#include "Maze.h"
using namespace std;

// Precon: Maze has dimensions greater than or equal to x = 0; y = 0
// Postcon: Returns true if exit is found, returns false if exit isn't found
bool solveMaze(Maze &m, int x, int y) {

  int q = m.getMarker(x, y); 
  if (q == 2) {
    return true;
  }
  if (q == 1) {
    return false;
  }
  if (q == 0) {
    m.markPosition(x, y, 1);
    if (!m.hasWallRight(x, y)) {
      if (solveMaze(m, x + 1, y)) {
        return true;
      }
    }
    if (!m.hasWallBelow(x, y)) {
      if (solveMaze(m, x, y + 1)) {
        return true;
      }
    }
    if (!m.hasWallLeft(x, y)) {
      if (solveMaze(m, x - 1, y)) {
        return true;
      }
    }
    if (!m.hasWallAbove(x, y)) {
      if (solveMaze(m, x, y - 1)) {
        return true;
      }
    }
    m.markPosition(x, y, 0);
    return false;
  }
  return false;
} // end solveMaze

int main(int argc, char **argv)  {

  // Modify the default behavior for Maze class, if desired.
  // Maze::printInColor = false;
  // Maze::animated = false;
  Maze::animationSlowness = 30; // lower is quicker
  // Maze::allowCycles = true;
  // Maze::allowUnsolvable = true;

  int width, height, seed;

  if (argc == 4) {
    // Use command-line parameters, if provided
    width = atoi(argv[1]);
    height = atoi(argv[2]);
    seed = atoi(argv[3]);
  } else {
    cout << "Enter width and height for maze: ";
    cin >> width >> height;
    cout << "Enter a seed for the random generator (or 0 for varying): ";
    cin >> seed;
  }

  Maze m(width, height, seed);

  cout << "Maze to be solved:\n";
  m.print();

  bool success = solveMaze(m, 0, 0);

  if (success)
    cout << "Maze is solved:\n";
  else
    cout << "Maze could not be solved:\n";
  m.print();

  return 0;
}  // end main
