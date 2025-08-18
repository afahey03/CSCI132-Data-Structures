//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.
// Aidan Fahey
// Implemented further functions

// Listing 14-5.

/** ADT queue: Circular array-based implementation.
 @file ArrayQueue.cpp */

#include "ArrayQueue.h"  // Header file

template<class ItemType>
ArrayQueue<ItemType>::ArrayQueue()
                    : front(0), back(DEFAULT_CAPACITY - 1), count(0)
{
}  // end default constructor

template<class ItemType>
bool ArrayQueue<ItemType>::isEmpty() const
{
   return count == 0;
}  // end isEmpty

template<class ItemType>
bool ArrayQueue<ItemType>::enqueue(const ItemType& newEntry)
{
   bool result = false;
   if (count < DEFAULT_CAPACITY)
   {
      // Queue has room for another item
      back = (back + 1) % DEFAULT_CAPACITY;
      items[back] = newEntry;
      count++;
      result = true;
   }  // end if
   
   return result;
}  // end enqueue

template<class ItemType>
bool ArrayQueue<ItemType>::dequeue()
{
   bool result = false;
   if (!isEmpty())
   {
      front = (front + 1) % DEFAULT_CAPACITY;
      count--;
      result = true;
   }  // end if
   
   return result;
}  // end dequeue

template<class ItemType>
ItemType ArrayQueue<ItemType>::peekFront() const
{
   // Enforce precondition
   if (isEmpty())
      throw PrecondViolatedExcept("peekFront() called with empty queue");
      
   // Queue is not empty; return front
   return items[front];
}  // end peekFront

template<class ItemType>
void ArrayQueue<ItemType>::clear()
{
   front = 0;
   back = DEFAULT_CAPACITY - 1;
   count = 0;
}

template<class ItemType>
int ArrayQueue<ItemType>::size() const
{
   return count;
}

template<class ItemType>
bool ArrayQueue<ItemType>::inorder() const
{

   int test = front;
   ItemType comparison = items[test];
   for (int i = 1; i < count; i++) {
      test = (test + 1) % DEFAULT_CAPACITY;
      if (comparison > items[test]) {
         comparison = items[test];
      }
      if (comparison < items[test]) {
         return false;
      }
   }
   return true;
}


// End of implementation file.
