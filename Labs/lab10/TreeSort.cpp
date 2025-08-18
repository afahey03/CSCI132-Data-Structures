/*******************************************************************
 * Name: Aidan Fahey
 * Date: 11/17/22
 * Course: CSCI 132
 * Assignment: Lab 10
 * Instructor: Z. Fitzsimmons
 * File: TreeSort.cpp
 * Purpose: Implementation of treesort for arrays.
 ***************************************************************************/
#include "TreeSort.h"
#include "BinarySearchTree.h"

template<class ItemType>
void treeSort(ItemType arr[], int n) {
  BinarySearchTree<ItemType> tree;
  for (int i = 0; i < n; i++) {
    tree.add(arr[i]);
  }
  tree.fillArray(arr);
}
