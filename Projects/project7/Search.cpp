/*******************************************************************
 * Name: Aidan Fahey
 * Date: 11/8/22
 * Implemented ternary search recursively
 * Course: CSCI 132
 * Assignment: Homework 7
 * Instructor: Fitzsimmons
 * Program: Search.cpp
 * Purpose: Program to count the number of comparisons and copies made in 
 * different search algorithms.
 ***************************************************************************/

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include "Record.h"

using namespace std;


// sequentialSearch searches a sorted array for a target value, and if found,
// returns the index of the value. If the target is not found, it returns -1.
// Preconditions:
//   n is zero or a positive number
//   arr contains n elements, already sorted in ascending order.
int sequentialSearch(const Record arr[], int n, const Record &target) {
  for (int i = 0; i < n; i++)
    if (arr[i] == target)
      return i;
  return -1;
}
/**
 * Searches the array arr[first] through arr[last]
 * for a given value by using a binary search.
 *
 * Precondition:
 *     If first <= last, then both first and last are valid indexes into the
 *     array, and elements arr[first] through arr[last], inclusive, are already
 *     sorted in ascending order.  Also, if the target is anywhere in the
 *     original array, it will be within the subarray arr[first] to arr[last],
 *     inclusive.
 * Postcondition:
 *     If an entry in the array arr is equal to target, then return its
 *     position in the array. Otherwise return -1.
 */
int binarySearchHelper(const Record arr[], int first, int last, const Record &target) {
  if (first > last) {
    return -1; // target not found
  } else {
    int mid = first + (last - first) / 2;
    if (target == arr[mid]) {
      return mid;
    } else if (target < arr[mid]) {
      return binarySearchHelper(arr, first, mid - 1, target);
    } else {
      return binarySearchHelper(arr, mid + 1, last, target);
    }
  }
}

/*
 * binarySearch searches a sorted array for a target value, and if found,
 * returns the index of the value. If the target is not found, it returns -1.
 * Preconditions:
 *  n is zero or a positive number
 *  arr contains n elements, already sorted in ascending order.
 * Postcondition:
 *     If an entry in the array arr is equal to target, then return its
 *     position in the array. Otherwise return -1.
 */
int binarySearch(const Record arr[], int n, const Record &target) {
  // just call our recursive helper function.
  return binarySearchHelper(arr, 0, n-1, target);
}

int ternarySearchHelper(const Record arr[], int first, int last, const Record &target) {
  if (first > last) {
    return -1;
  } else {
    int oneThird = (first + (last - first) / 3);
    int twoThird = (first + 2 * (last - first) / 3);

    if (target == arr[oneThird]) {
      return oneThird;
    }
    if (target == arr[twoThird]) {
      return twoThird;
    }

    if (target < arr[oneThird]) {
      return ternarySearchHelper(arr, first, oneThird - 1, target);
    } else if (target > arr[twoThird]) {
      return ternarySearchHelper(arr, twoThird + 1, last, target);
    } else {
      return ternarySearchHelper(arr, oneThird + 1, twoThird - 1, target);
    }
  }
  return -1;
}

int ternarySearch(const Record arr[], int n, const Record &target) {

  return ternarySearchHelper(arr, 0, n-1, target);
}


// Every search algorithm is a function that takes an array of Records, an
// integer, and a refernce to a target Record, and returns an integer.
typedef int (*searchAlgorithm)(const Record arr[], int n, const Record &target);

/*
 * A driver for testing search algorithms. This takes as parameters:
 *   title - used for printing the results
 *   search - a function pointer to the algorithm to be tested
 *   arr - the random sorted array to be used for testing
 *   n - the length of arr (must be positive)
 *   searches - the number of trial searches to be performed
 *   maxval - the largest value in the array
 */
void test_search(string title, searchAlgorithm search,
    const Record arr[], int n, int searches, int maxval) {

  cout << "Testing successful searches with " << title << ":\n";
  Record::resetStatistics();
  for (int i = 0; i < searches; i++) {
    const Record &target = arr[rand() % n];
    int pos = search(arr, n, target);
    if (pos < -1 || pos >= n)
      cout << "Error: search returned an invalid index " << pos << "\n";
    else if (pos == -1)
      cout << "Error: search failed to find " << target << " in array\n";
    else if (!target.test_verify(arr[pos]))
      cout << "Error: search for value " << target << " returned value "
        << arr[pos] << " at position " << pos << "\n";
  }
  Record::printStatistics(searches);

  cout << "Testing unsuccessful searches with " << title << ":\n";
  Record::resetStatistics();
  for (int i = 0; i < searches; i++) {
    // The array values are all even numbers between 0 and maxval,
    // so let's search for odd numbers between -maxval/4 and maxval*5/4
    Record target(1+2*(-maxval/8 + (rand() % (maxval*3/4))));
    int pos = search(arr, n, target);
    if (pos < -1 || pos >= n)
      cout << "Error: search returned an invalid result " << pos << "\n";
    else if (pos != -1)
      cout << "Error: search for nonexistent value " << target << " returned value "
        << arr[pos] << " at position " << pos << "\n";
  }
  Record::printStatistics(searches);

}

int main(int argc, char **argv) {
  int size = 50;
  int searches = 0;
  int seed = 1234; // any value, to seed the random genrator, or 0 to use time of day

  if (argc >= 2)
    size = atoi(argv[1]);
  if (argc >= 3)
    searches = atoi(argv[2]);
  if (argc >= 4)
    seed = atoi(argv[3]);

  if (searches <= 0)
    searches = max(10, (int)sqrt(size));

  assert(size > 0);
  assert(searches > 0);

  int maxval = 0;
  Record *arr = Record::generateRandomSortedArray(size, maxval, seed);
  cout << "Testing using a random array of length " << size << endl;
  if (size <= 50)
    Record::printArray(arr, size);

  test_search("Sequential Search", sequentialSearch, arr, size, searches, maxval);

  test_search("Binary Search", binarySearch, arr, size, searches, maxval);

  test_search("Ternary Search", ternarySearch, arr, size, searches, maxval);

  delete[] arr;
}
