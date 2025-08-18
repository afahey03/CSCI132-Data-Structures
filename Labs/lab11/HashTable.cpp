// Name: Aidan Fahey
// Date: 12/2/22
// Course: CSCI 132
// Implemented addItem, contains, and traverse
//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** @file  HashTable.cpp */
// Modifed December 2021 by Z. Fitzsimmons

// Separate chaining resolves collisions

#include "HashTable.h"
#include <cmath>    // For sqrt
#include "Hash.h"   // For hash()
#include <iostream> // For testing
#include <unordered_map>

//////////////////////////////////////////////////////////////////////
// Private helper methods
//////////////////////////////////////////////////////////////////////

template <class KeyType, class ValueType>
void HashTable<KeyType, ValueType>::destroyDictionary() {
    for (int i = 0; i < tableCapacity; i++) {
        // If there are hashed entries at this location,
        // we need to delete them
        while (table[i] != nullptr) {
            HashedEntry<KeyType, ValueType>* toDelete = table[i];
            table[i] = table[i]->getNext();
            delete toDelete;
      }  // end while
   }  // end for
   itemCount = 0;
}  // end destroyDictionary

template <class KeyType, class ValueType>
int HashTable<KeyType, ValueType>::getNextPrime(int number) const {
    bool foundPrime = false;
    if ((number % 2) == 0)
        number++;
   
    while (!foundPrime) {
        if ((number % 5 == 0) || !isPrime(number)) {
            number = number + 2;
        } else {
         foundPrime = true;
        }
   }  // end
   return number;
}  // end getNextPrime

template <class KeyType, class ValueType>
bool HashTable<KeyType, ValueType>::isPrime(int number) const {
    bool isPrimeNumber = true;          // Assume prime, prove otherwise
   
    if ((number == 2) || (number == 3)) {        // Smallest primes
        isPrimeNumber = true;
    } else {
        if ((number % 2 == 0) || (number < 2)) {  // Even number or ineligible
            isPrimeNumber = false;
        } else {
            int root = sqrt(number);             // Limit of search
            int i = 3;
            do {
                if (number % i == 0)               // Not prime
                    isPrimeNumber = false;
                else
                    i = i + 2;
            } while ((isPrimeNumber == true) && (i <= root));
        }  // end if
    }  // endif
   
    return isPrimeNumber;
}   // end isPrime

//////////////////////////////////////////////////////////////////////
// Constructors & Destructor
//////////////////////////////////////////////////////////////////////

template <class KeyType, class ValueType>
HashTable<KeyType, ValueType>::HashTable() : itemCount(0), tableCapacity(DEFAULT_CAPACITY) {
    table = new HashedEntry<KeyType, ValueType>*[tableCapacity];

    // All pointers in array initialized to nullptr
    for (int i = 0; i < tableCapacity; i++)
        table[i] = nullptr;
}   // end

template <class KeyType, class ValueType>
HashTable<KeyType, ValueType>::HashTable(int maxNumberOfEntries) : itemCount(0) {
    tableCapacity = getNextPrime(maxNumberOfEntries);
    table = new HashedEntry<KeyType, ValueType>*[tableCapacity];

    // All pointers in array initialized to nullptr
    for (int i = 0; i < tableCapacity; i++)
        table[i] = nullptr;
}   // end

template <class KeyType, class ValueType>
HashTable<KeyType, ValueType>::HashTable(const HashTable<KeyType, ValueType>& dict)
                  : itemCount(dict.itemCount), tableCapacity(dict.tableCapacity) {
    table = new HashedEntry<KeyType, ValueType>*[tableCapacity];
    for (int i = 0; i < tableCapacity; i++)
        table[i] = nullptr;

    for (int index = 0; index < dict.tableCapacity; index++) {
        // Copy linked chains...
        HashedEntry<KeyType, ValueType>* curPtr = dict.table[index];
        HashedEntry<KeyType, ValueType>* copy;

        if (curPtr != nullptr) {
            table[index] = new HashedEntry<KeyType, ValueType>(curPtr->getKey(), curPtr->getItem());
            copy = table[index];
            
            curPtr = curPtr->getNext();
            while(curPtr != nullptr) {
                copy->setNext(new HashedEntry<KeyType, ValueType>(curPtr->getKey(), curPtr->getItem()));
                copy = copy->getNext();
                curPtr = curPtr->getNext(); 
            }
        }
    }   // end for
}   // end 

template <class KeyType, class ValueType>
HashTable<KeyType, ValueType>::~HashTable() {
    destroyDictionary();
    delete[] table;
}   // end destructor

////////////////////////////////////////////////////////////////////
// Status and public maintenance (clear) methods
//////////////////////////////////////////////////////////////////////

template <class KeyType, class ValueType>
bool HashTable<KeyType, ValueType>::isEmpty() const {
    return (itemCount == 0);
}   // end isEmpty

template <class KeyType, class ValueType>
int HashTable<KeyType, ValueType>::getNumberOfItems() const {
    return itemCount;
}   // end getNumberOfItems

template <class KeyType, class ValueType>
void HashTable<KeyType, ValueType>::clear() {
    destroyDictionary();
}   // end clear

///////////////////////////////////////////////////////////////////
// Container methods (add, remove, getItem, contains, traverse)
//////////////////////////////////////////////////////////////////////

template <class KeyType, class ValueType>
bool HashTable<KeyType, ValueType>::add(const KeyType& searchKey, const ValueType& newItem) {
    // Nte: This method assumes the key is not yet anywhere in the dictionary.
    // This is a precondition to the method. It is assumed a responsible
    // client would never dare call this method with a duplicate key.

    // Create entry to add to dictionary
    HashedEntry<KeyType, ValueType>* entryToAddPtr = new HashedEntry<KeyType, ValueType>(searchKey, newItem);
   
    // Compute the hashed index into the array
    int itemHashIndex = hash(searchKey) % tableCapacity;
   
    // Add the entry to the chain at itemHashIndex
    if (table[itemHashIndex] == nullptr) {
        table[itemHashIndex] = entryToAddPtr;
    } else {
        entryToAddPtr->setNext(table[itemHashIndex]);
        table[itemHashIndex] = entryToAddPtr;
    } // end if

    itemCount++;
    return true;
} // end add

template <class KeyType, class ValueType>
bool HashTable<KeyType, ValueType>::remove(const KeyType& searchKey) {
    bool itemFound = false;
   
    // Compute the hashed index into the array
    int itemHashIndex = hash(searchKey) % tableCapacity;
    if (table[itemHashIndex] != nullptr) {
        // Special case - first node has target
        if (searchKey == table[itemHashIndex]->getKey()) {
            HashedEntry<KeyType, ValueType>*  toDelete = table[itemHashIndex];
            table[itemHashIndex] = table[itemHashIndex]->getNext();
            delete toDelete;
            toDelete = nullptr;
            itemCount--;
            itemFound = true;
        } else { // Search the rest of the chain
            HashedEntry<KeyType, ValueType>* prevPtr = table[itemHashIndex];
            HashedEntry<KeyType, ValueType>* curPtr = prevPtr->getNext();
            while ((curPtr != nullptr) && !itemFound ) {
                // Found item in chain so remove that node
                if (searchKey == curPtr->getKey()) {
                    prevPtr->setNext(curPtr->getNext());
                    delete curPtr;
                    curPtr = nullptr;
                    itemCount--;
                    itemFound = true;
                } else { // Look at next entry in chain
                    prevPtr = curPtr;
                    curPtr = curPtr->getNext();
                } // end if
            } // end while
        } // end if
    } // end if
   
    return itemFound;
}   // end remove


/** Precondition: None.
  * Postcondition: Retrieves an item with the given search key from the
  * dictionary and returns the value corresponding to this entry. If an
  * entry with the given search key is not present then a NotFoundException
  * is thrown. */
template <class KeyType, class ValueType>
ValueType HashTable<KeyType, ValueType>::getItem(const KeyType& searchKey) const
                                              throw (NotFoundException) {
    int itemHashIndex = hash(searchKey) % tableCapacity;

    if (table[itemHashIndex] != nullptr) {
        auto ptr = table[itemHashIndex];
        while (ptr != nullptr) {
            if (searchKey == ptr->getKey()) 
                return ptr->getItem();
            ptr = ptr->getNext();
        }
    }

    throw NotFoundException("Key was not found!");
}   // end getItem

/** Precondition: None.
  * Postcondition: Returns true if the dictionary contains an entry with
  * the given search key. */
template <class KeyType, class ValueType>
bool HashTable<KeyType, ValueType>::contains(const KeyType& searchKey) const {
       
    int itemHashIndex = hash(searchKey) % tableCapacity;

    if (table[itemHashIndex] != nullptr) {
        auto ptr = table[itemHashIndex];
        while (ptr != nullptr) {
            if (searchKey == ptr->getKey()) 
                return true;
            ptr = ptr->getNext();
        }
    }
    return false; 
}   // end contains

/** Precondition: None.
  * Postcondition: Traverses this dictionary and calls a given client function
  * once for each item. */
template <class KeyType, class ValueType>
void HashTable<KeyType, ValueType>::traverse(void visit(ValueType&)) const {

    for (int i = 0; i < tableCapacity; i++) {
        auto ptr = table[i];
        while (ptr != nullptr) {
            ValueType item = ptr->getItem();
            visit(item);
            ptr = ptr->getNext();
        }
    }

}   //end traverse
