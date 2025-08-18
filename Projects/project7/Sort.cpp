/*******************************************************************
 * Name: Aidan Fahey
 * Date: 11/8/22
 * Implemented iterative mergeSort
 * Course: CSCI 132
 * Assignment: Homework 7
 * Instructor: Fitzsimmons
 * Program: Sort.cpp
 * Purpose: Program to count the number of comparisons and copies made in 
 * different sort algorithms.
 * Modified:
 *   6 April 2021 - K. Walsh - use Record to track copies and comparisons
 ***************************************************************************/

#include <iostream>
#include <cassert>
#include "Record.h"

using namespace std;


// Merges two sorted array segments arr[first..mid] and arr[mid+1..last] into
// one sorted segment arr[first...last].
// Preconditions:
//   Parameters first, mid, and last are all valid array indices into the array,
//   with first <= mid <= last.
//   The subarray arr[first..mid] is already sorted in ascending order.
//   The subarray arr[mid+1..last] is already sorted in ascending order.
// Postcondtions:
//   The subarray arr[first..last] is now sorted in ascending order.
void merge(Record arr[], int first, int mid, int last) {
  // cout << "Merging arr[" << first << ".." << mid << "] with arr[" << (mid+1) << ".." << last << "]\n";
  int n = last - first + 1;
  Record *temp = new Record[n];  // a temporary array used during merging

  // Initialize the local indices to indicate the subarrays
  int first1 = first;            // Beginning of first subarray
  int last1 = mid;               // End of first subarray
  int first2 = mid + 1;          // Beginning of second subarray
  int last2 = last;              // End of second subarray

  // While both subarrays are not empty, copy the
  // smaller item into the temporary array
  int index = 0;                 // Next available location in temp
  while ((first1 <= last1) && (first2 <= last2)) {
    if (arr[first1] <= arr[first2]) {
      temp[index] = arr[first1];
      first1++;
    } else {
      temp[index] = arr[first2];
      first2++;
    }
    index++;
  }

  // Copy any remaining values from first subarray
  while (first1 <= last1) {
    temp[index] = arr[first1];
    first1++;
    index++;
  }

  // Copy any remaining values from second subarray
  while (first2 <= last2) {
    temp[index] = arr[first2];
    first2++;
    index++;
  }

  // Copy result back into original array
  for (int i = 0; i < n; i++)
    arr[first+i] = temp[i];

  delete[] temp;
}  // end merge


// Sorts the records in the subarray arr[first..last] into ascending order using
// a recursive merge-sort algorithm.
// Precondition:
//   Parameters first and last are both valid array indices into the array,
//   with first <= last. Or, first > last to indicate an empty subarray.
// Postcondtions:
//   If the subarray was not empty, then subarray arr[first..last] is now sorted
//   in ascending order.
void recursiveMergeSort(Record arr[], int first, int last) {
  if (first < last) {
    // cout << "Sorting arr[" << first << ".." << last << "] (begin recursive case)\n";
    
    // Sort each half
    int mid = (first + last)/2; // Index of approximate midpoint
    // NOTE: if the subarray length is exactly 2, the midpoint is the left value
    // in the pair, so we consider them midpoint as part of the left half.

    // Sort left half arr[first..mid]
    recursiveMergeSort(arr, first, mid);

    // Sort right half arr[mid+1..last]
    recursiveMergeSort(arr, mid + 1, last);

    // Merge the two halves
    merge(arr, first, mid, last);
   
    // cout << "Sorting arr[" << first << ".." << last << "] (done recursive case)\n";
    // Record::printSubarray(arr, first, last);
  } else {
    // cout << "Sorting arr[" << first << ".." << last << "] (base case)\n";
  }
}

void iterativeMergeSort(Record arr[], int n) {
  int size = 1;
  while (size < n) {
    for (int i = 0; i <= n-1; i += (2*size)) {
      int mid = i + size - 1;
      int last = i + (size*2) - 1;
      if (last > n-1) {
        last = n-1;
      }
      if (mid > n-1) {
        mid = n-1;
      }
      merge(arr, i, mid, last);
    }
    size *= 2;
  }
}

int main(int argc, char **argv) {
  int size = 50;
  int seed = 1234; // any value, to seed the random genrator, or 0 to use time of day

  if (argc >= 2)
    size = atoi(argv[1]);
  if (argc >= 3)
    seed = atoi(argv[2]);

  assert(size > 0);

  Record *arr1 = Record::generateRandomUnsortedArray(size, seed);
  cout << "Testing using a random array of length " << size << endl;
  if (size <= 50)
    Record::printArray(arr1, size);

  // Make an exact copy of the original array
  Record *arr2 = new Record[size];
  for (int i = 0; i < size; i++)
    arr2[i] = arr1[i];

  cout << "Sorting using recursive merge sort...\n";
  Record::resetStatistics();
  recursiveMergeSort(arr1, 0, size-1);
  Record::printStatistics();
  if (size <= 50)
    Record::printArray(arr1, size);

  cout << "Sorting using iterative merge sort...\n";
  Record::resetStatistics();
  iterativeMergeSort(arr2, size);
  Record::printStatistics();
  if (size <= 50)
    Record::printArray(arr2, size);

  // Compare the results to verify both are in agreement.
  int errs = 0;
  for (int i = 0; i < size; i++) {
    if (arr2[i] != arr1[i]) {
      errs++;
      if (errs <= 10)
        cout << "Error: arr1[" << i << "] = " << arr1[i] << " but arr2[" << i << "] = " << arr2[i] << endl;
      else if (errs == 11)
        cout << "... (additional errors supressed)\n";
    }
  }
  cout << "Found " << errs << " differences in sorted results between the two algorithms.\n";

  delete[] arr1;
  delete[] arr2;
}
