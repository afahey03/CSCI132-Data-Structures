//Name: Aidan Fahey
//Date: 9/21/22
//Assignment: Project 2
//Implementing Code
#include "ArrayBag.h"
#include <iostream>
#include <iomanip>
#include <fstream>
 
using namespace std;
 
// A list of common punctuation characters that might separate words in a title.
const string PUNCTUATION = " ,:;\t.()&";
 
// most of the papers are from 1967 - 2007, a 41-year span
const int OLDEST = 1967;
const int NEWEST = 2007;
 
int main() {
  ifstream data;
  data.open("papers.lst");
  if (!data) {
    cout << "Sorry, could not open file: papers.lst\n";
    return 1;
  }
 
  ArrayBag<string>* years = new ArrayBag<string>[41]; // 41 arrays, one for each year
  ArrayBag<string>* popWords = new ArrayBag<string>; // for the Trends section
  while (true) {
    int year;
    data >> year;
    if (!data)
      break;
 
    string authors;
    getline(data, authors, ',');
    if (!data)
      break;
 
    string title;
    getline(data, title);
    if (!data)
      break;
 
    // ignore papers outside the range OLDEST to NEWEST
    if (year < OLDEST || year > NEWEST)
      continue;
 
    // ignore papers if the arraybag is already full
    if (years->isFull())
      continue;
 
    bool moreWords = true;
    
    while (moreWords) {
      size_t pos = title.find_first_of(PUNCTUATION);
      string word;
      if (pos == string::npos) {
        word = title;
        moreWords = false;
      } else {
        word = title.substr(0, pos);
        title.erase(0, pos+1);
      }
 
      // ignore short words, like "A", or "the", which are mostly boring
      if (word.length() < 5)
        continue;
 
      // process word
      if (!years[year-1967].add(word)) {
        cout << "Oops, ArrayBag is now full.\n";
        break;
      }
    }
  }

  for (int i = 1967; i < 2008; i++) {
    int maxFreq = 0; // Max frequency
    string freqWord; // Most frequently occurring word
    string word; // Word
    int wordFreq = 0; // Frequency of word
    for (int j= 0; j < years[i-1967].getCurrentSize(); j++) {
      word = years[i-1967].get(j);
      wordFreq = years[i-1967].getFrequencyOf(word);
      if (wordFreq > maxFreq) {
        maxFreq = wordFreq;
        freqWord = word;
      }
    }
    std::cout << "Most popular word for " << i << " is " << freqWord << " which appeared " << maxFreq << " times, among " << years[i-1967].getCurrentSize() << " total words for that year." << "\n";
    if (!popWords->contains(freqWord)) {
      popWords->add(freqWord); // ArrayBag contains all popular words
    }
  }

  std::cout << "YEARS ";
  for (int i = 0; i < popWords->getCurrentSize(); i++) {
    string currPopWord = popWords->get(i);
    std::cout << currPopWord << "            "; // Prints out all the popular words
  }

  std::cout << "\n";
  for (int i = 0; i < 41; i++) {
    std::cout << i + 1967 << " ";
    for (int j = 0; j < popWords->getCurrentSize(); j++) {
      string numPopWord = popWords->get(j);
      int currPopWordFreq = years[i].getFrequencyOf(numPopWord);
      std::cout << currPopWordFreq << "                    "; // Prints out the frequency of each word in the year that it happens
    }
    std::cout << "\n";
  }

  return 0;

} // I cannot for the life of me figure out why this program is not working