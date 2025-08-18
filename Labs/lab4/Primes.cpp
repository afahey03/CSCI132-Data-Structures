// Starter code for Lab 4
//Compute prime factors of input number
// Implemented further functions

#include <iostream>
#include "LinkedStack.h"

using namespace std;
int main(void) {
  int number;
  int factor, result;
  LinkedStack<int> primeStack;

  cout << "Enter an integer: ";
  cin >> number;

  result = number;
  factor = 2;

  while (result != 1) {
    if (result % factor == 0) {
      primeStack.push(factor);
      result = result / factor;
    }
    if (result % factor != 0) {
      factor++;
    }
  }
  cout << "The prime factors of " << number << " are" << "\n";
  while (!primeStack.isEmpty()) {
    cout<< primeStack.peek() << " ";
    primeStack.pop();
  }
  cout << endl;

  return 0;
} //main
