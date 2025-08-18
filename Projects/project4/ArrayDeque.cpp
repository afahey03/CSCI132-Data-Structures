// File Name: ArrayDeque.cpp
// Author: Zack Fitzsimmons
// Course: CSCI 132
// Date: Fall 2020
// Purpose: Array-based implementation of ArrayDeque ADT
// Revisions
//   4 March 2021 - K. Walsh - Updated as new project for spring 2021

#include "ArrayDeque.h"
#include "PrecondViolatedExcept.h"

template<class ItemType>
ArrayDeque<ItemType>::ArrayDeque()
{
  capacity = DEFAULT_CAPACITY;
  items = new ItemType[capacity]; // dyanamically allocate array
  front = 0;
  back = capacity - 1;
  count = 0;
}  // end default constructor

template<class ItemType>
ArrayDeque<ItemType>::ArrayDeque(int maxItems)
{
  capacity = maxItems;
  items = new ItemType[capacity]; // dyanamically allocate array
  front = 0;
  back = capacity - 1;
  count = 0;
}  // end one-argument constructor

template<class ItemType>
ArrayDeque<ItemType>::ArrayDeque(const ArrayDeque<ItemType>& other)
{
  capacity = other.capacity;
  items = new ItemType[capacity];
  count = 0;
  front = 0;
  back = capacity - 1;
  for (int i = 0; i < other.count; i++) {
    this->enqueueBack(other.items[other.front + i]);
  }
  front = 0;
  back = count - 1;
}  // end copy constructor

template<class ItemType>
ArrayDeque<ItemType>::~ArrayDeque()
{
  delete[] items;
}  // end destructor

template<class ItemType>
bool ArrayDeque<ItemType>::isEmpty() const
{
  return count == 0;
}  // end isEmpty

template<class ItemType>
bool ArrayDeque<ItemType>::isFull() const
{
  return count == capacity;
}  // end isFull

template<class ItemType>
bool ArrayDeque<ItemType>::dequeueFront()
{
  if (isEmpty()) {
    return false;
  } else {
    // Increment front, being careful to wrap around to the start
    front = (front + 1) % capacity;
    count--;
    return true;
  }
} // end dequeueFront

template<class ItemType>
ItemType ArrayDeque<ItemType>::peekFront() const
{
  // Check precondition, just to be safe.
  if (isEmpty())
    throw PrecondViolatedExcept("peekFront() called with empty deque");

  // ArrayDeque is not empty, so return the front entry
  return items[front];
} // end peekFront

template<class ItemType>
bool ArrayDeque<ItemType>::enqueueBack(const ItemType &newEntry)
{
  if (isFull()) {
    return false;
  } else {
    // There is room for another item.
    // Increment back, being careful to wrap around to the start
    back = (back + 1) % capacity;
    items[back] = newEntry;
    count++;
    return true;
  }
} // end enqueueBack

  template<class ItemType>
bool ArrayDeque<ItemType>::enqueueFront(const ItemType &newEntry)
{
  if (isFull()) {
    return false;
  }
  if (front < 1) {
    front = capacity - 1;
    items[front] = newEntry;
    count++;
  } else {
    front = (front - 1) % capacity;
    items[front] = newEntry;
    count++;
  }

  return true;
} // end enqueueFront

template<class ItemType>
bool ArrayDeque<ItemType>::dequeueBack()
{
  if (isEmpty()) {
    return false;
  } else {
    // Increment front, being careful to wrap around to the start
    back = (back - 1) % capacity;
    count--;
    return true;
  }
} // end dequeueBack

template<class ItemType>
ItemType ArrayDeque<ItemType>::peekBack() const
{
  if (isEmpty())
    throw PrecondViolatedExcept("peekFront() called with empty deque");

  // ArrayDeque is not empty, so return the front entry
  return items[back];
} // end peekBack

