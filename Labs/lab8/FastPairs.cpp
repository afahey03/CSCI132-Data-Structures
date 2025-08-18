/*******************************************************************
 * Name: Aidan Fahey
 * Date: 11/4/22
 * Implemented findClosestPair with O(n log n) running time
 * Date: Fall 2021
 * Course: CSCI 132
 * Assignment: Lab 8
 * Instructor: Fitzsimmons
 * Program: Pairs.cpp
 * Purpose: A program that finds a closest pair of integers in a given list.
 * Modified:
 *   K. Walsh, 23 March 2021 - Added command-line args and timing code.
 ***************************************************************************/
#include <iostream>
#include <ctime>
#include "ArrayList.h"
#include "MergeSort.h"
using namespace std;

// Given a list of integers, find and return the distance between the closest
// two numbers. Also print a pair of numbers having that distance (if there are
// ties, only one "closest pair" is printed).
int findClosestPair(const ArrayList<int>& nums) {

  int n = nums.size();

  ArrayList<int> *list = new ArrayList<int>(nums);
  mergeSort(list, 1, n);

  int x = list->getEntry(1);
  int y = list->getEntry(2);

  for (int i = 2; i < n; i++) {
    int a = list->getEntry(i);
    int b = list->getEntry(i + 1);
    if (abs(b - a) < abs(y - x)) {
      x = a;
      y = b;
    }
  }

  cout << "A closest pair is: " << x << " and " << y << endl;
  return abs(y - x);
}

int main(int argc, char **argv) {
  ArrayList<int> nums;

  int n;
  if (argc == 2) {
    // With one command-line argument, generate a random list of the given size.
    n = atoi(argv[1]);
    cout << "Initializing a list of " << n << " random numbers...\n";
    srand(1234);
    // srand(time(NULL));
    int limit = RAND_MAX;
    if (n < 100)
      limit = 20 * n * n;
    for(int i = 0; i < n; i++) {
      nums.append(rand() % limit); // this limits the range of random values
      // nums.append(rand()); // this does not limit the range
    }
    if (n <= 30) {
      cout << "nums = " << nums.toPrettyString() << endl;
    } else {
      cout << "List is too large to display here.\n";
    }
  } else if (argc > 2) {
    // With two or more command-line arguments, use those as the list values.
    n = argc - 1;
    for(int i = 0; i < n; i++) {
      int val = atoi(argv[i+1]);
      nums.append(val);
    }
  } else {
    // Otherwise prompt user for list size and values.
    cout << "Enter a number of values greater than two: ";
    cin >> n;
    cout << "Enter a space-delimited sequence of " << n << " integers: ";
    for(int i = 0; i < n; i++) {
      int val;
      cin >> val;
      nums.append(val);
    }
  }

  cout << "Finding the closest pair...\n";
  clock_t start  = clock();
  int d = findClosestPair(nums);
  clock_t finish = clock();
  double elapsedTime = static_cast<double>(finish - start) / CLOCKS_PER_SEC;

  cout << "Closest distance is: " << d << endl;
  printf("Elapsed time for length %d: about %.6f seconds\n", n, elapsedTime);
  
  // This next line is needed by the plot.sh script to plot this data point.
  printf("PLOT %d %0.6f\n", n, elapsedTime);

  return 0;
}
