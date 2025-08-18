// Aidan Fahey
// 10/21/22
// Implemented findPath()

#include "ArraySet.h"
#include "ArrayList.h"
#include <iostream>
#include <string>

using namespace std;

// This program is designed for a map containing nine cities,
// named "A" through "I", as shown in Figure 5-6 of the textbook.
static const int NUM_CITIES = 9;

// Given a city name, returns the number of that city. For example,
// getCityNumber("A") returns 0, 
// getCityNumber("C") returns 2, and
// getCityNumber("I") returns 8.
int getCityNumber(string city) {
  assert(city.length() == 1 && 'A' <= city.at(0) && city.at(0) < 'A'+NUM_CITIES);
  return (int)city.at(0) - 'A';
}

// Given a city number, returns the name of that city. For example,
// getCityName(0) returns "A", 
// getCityName(2) returns "C", and
// getCityName(8) returns "I".
string getCityName(int cityNumber) {
  assert(0 <= cityNumber && cityNumber < NUM_CITIES);
  string cityname = "";
  cityname += (char)('A' + cityNumber);
  return cityname;
}

// This initializes the flightMap[] array so it contains information about the
// flights available, as shown in Figure 5-6 of the textbook.
//
// Each element in the array represents a single city's info. That is,
// flightMap[i] is an ArrayList<string>, and that ArrayList cotnains all the
// cities that can be reached by direct flight from city number i.
//
// For example, flightMap[getCityNumber("C")].contains("E") is true,
// because there is a direct flight from city "C" to city "E".
void initializeFlightMap(ArrayList<string> flightMap[]) {
  flightMap[getCityNumber("A")].append("B"); // direct flight A to B
  flightMap[getCityNumber("A")].append("C"); // direct flight A to C
  flightMap[getCityNumber("B")].append("H"); // direct flight B to H
  flightMap[getCityNumber("B")].append("D"); // direct flight B to D
  flightMap[getCityNumber("C")].append("B"); // direct flight C to B
  flightMap[getCityNumber("C")].append("D"); // direct flight C to D
  flightMap[getCityNumber("C")].append("E"); // direct flight C to E
  flightMap[getCityNumber("D")].append("H"); // direct flight D to H
  flightMap[getCityNumber("D")].append("E"); // direct flight D to E
  flightMap[getCityNumber("D")].append("F"); // direct flight D to F
  flightMap[getCityNumber("H")].append("G"); // direct flight H to G
  flightMap[getCityNumber("G")].append("C"); // direct flight G to C
  flightMap[getCityNumber("E")].append("I"); // direct flight E to I
  flightMap[getCityNumber("I")].append("C"); // direct flight I to C
  flightMap[getCityNumber("F")].append("G"); // direct flight F to G
  flightMap[getCityNumber("F")].append("I"); // direct flight F to I
}


// This finds a path from one city (current) to another (dest). The path could
// be a single direct flight (if one is available), or a multi-hop itinerary
// involving stops in several other cities.
bool findPath(string current, string dest, const ArrayList<string> flightMap[], ArraySet<string>& visited, ArrayList<string>& solution) {

  if (current == dest) {
    return true;
  } else if (visited.contains(current)) {
      return false;
  } else {
      visited.add(current);
      for (int i = 1; i <= flightMap[getCityNumber(current)].getLength(); i++) {
        string city = flightMap[getCityNumber(current)].getEntry(i);
        if (findPath(city, dest, flightMap, visited, solution)) {
          solution.insert(1, city);
          return true;
        }
      }
  }

  cout << "Traveler is at " << current << " trying to reach " << dest
    << " with itinerary so far: " << solution.toStringWithSeparator(" -> ") << endl;

  return false;
}

int main(int argc, char **argv) {

  ArrayList<string> flightMap[NUM_CITIES];
  initializeFlightMap(flightMap);

  string start; // starting city
  string dest; // destination city
  
  if (argc == 3) {
    start = argv[1][0];
    dest = argv[2][0];
  } else {
    cout << "Enter a starting city: ";
    cin >> start;
    cout << "Enter a destination city: ";
    cin >> dest;
  }

  cout << "Searching for a path from "
    << start << " (city #" << getCityNumber(start) << ") to "
    << dest << " (city #" << getCityNumber(dest) << ")...\n";

  ArraySet<string> visited; // set of cities traveler has visited to so far
  
  // TODO: You may want to have this next line of code. Or not. It depends on
  // how you write the findPath() function.
  // visited.add(start); // The traveler starts in this city, so maybe add it to
                         // the set of already-visited cities?

  ArrayList<string> solution; // an ordered list of cities connecting start to dest

  if (findPath(start, dest, flightMap, visited, solution)) {
    solution.insert(1, start);
    cout << "Path found: " << solution.toStringWithSeparator(" -> ") << endl;
  } else {
    cout << "Sorry, you can't get from " << start << " to " << dest << ".\n";
  }

  return 0;
}
