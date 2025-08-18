// Name: Aidan Fahey
// Date: 11/17/22
// Implemented findPersonHelper, printChildren, printFriendsOf, printPrimeMinisters and PrintPrimeMinistersHelper,
// printAncestryOf, printGeneration and printGenerationHelper

#include "Tree.h"
#include "Person.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void printChildren(TreeNode<Person*> *node) {
  for (int i = 0; i < node->getNumChildren(); i++) {
    cout << node->getChild(i)->getItem()->name << "\n";
  }
}

void printFamilyTree(string prefix, TreeNode<Person*> *t) {
  if (t == nullptr) {
    cout << "oops, subtree is nullptr\n";
    return;
  }
  int n = t->getNumChildren();
  cout << prefix << t->getItem()->toString() << ", with " << n << " children\n";
  for (int i = 0; i < n; i++) {
    TreeNode<Person*> *child = t->getChild(i);
    printFamilyTree(prefix + "| ", child);
  }
}

Person *findPersonHelper(TreeNode<Person*> *node, string target) {
  if (node == nullptr) {
    return nullptr;
  }
  else if (node->getItem()->name == target) {
    return node->getItem();
  }
  else {
    for (int i = 0; i < node->getNumChildren(); i++) {
      auto child = findPersonHelper(node->getChild(i), target);
      if (child == nullptr) {
        continue;
      } else {
        return child;
      }
    }
    return nullptr;
  }
}

Person *findPerson(Tree<Person*> *tree, string target) {
  if (tree->isEmpty())
    return nullptr;
  else
    return findPersonHelper(tree->getRoot(), target);
}

void printFriendsOf(Tree<Person*> *family, string person) {
  if (family->findNode(findPerson(family, person))) {
    cout << "Siblings and cousins of " << person << " include: " << "\n";
  } else {
    cout << "Siblings and cousins of " << person << " are not known.";
  }
  TreeNode<Person*> *indiv = family->findNode(findPerson(family, person));
  TreeNode<Person*> *grandparent = indiv->getParent()->getParent();
  for (int i = 0; i < grandparent->getNumChildren(); i++) {
    for (int j = 0; j < grandparent->getChild(i)->getNumChildren(); j++) {
      string cousinSibling = grandparent->getChild(i)->getChild(j)->getItem()->name;
      if (cousinSibling != person) {
        cout << cousinSibling << "\n";
      }
    }
  }
}

bool isPrimeMinister(Person *p) {
  return p->occupation.find("Prime Minister") != string::npos;
}

void printPrimeMinistersHelper(TreeNode<Person*> *person, int& count) {
  if (isPrimeMinister(person->getItem())) {
    count++;
    cout << person->getItem()->name << " was " << person->getItem()->occupation << "." << "\n";
  }
  for (int i = 0; i < person->getNumChildren(); i++) {
    printPrimeMinistersHelper(person->getChild(i), count);
  }
}

void printPrimeMinisters(Tree<Person*> *family) {
  int numPM = 0;
  cout << "Results of search for prime ministers: " << "\n";
  printPrimeMinistersHelper(family->getRoot(), numPM);
  cout << "Found " << numPM << " family members." << "\n";
}

void printAncestryOf(Tree<Person*> *family, string name) {
  if (findPerson(family, name) != nullptr) {
    cout << "Known ancestry of " << name << ":" << "\n";
    TreeNode<Person*> *ancestor = family->findNode(findPerson(family, name));
    while (ancestor->getItem() != nullptr) {
      cout << ancestor->getItem()->name << " is the " << ancestor->getItem()->lineage << "\n";
      if (ancestor->getParent() == nullptr) {
        break;
      } else {
        ancestor = ancestor->getParent();
      }
    }
    cout << "No further information available." << "\n";
  } else {
    cout << name << " does not appear to be a member of this family." << "\n";
  }
}

void printGenerationHelper(TreeNode<Person*> *person, int gen, int &count) {
  if (gen == 1) {
    cout << person->getItem()->name << " was born in " << person->getItem()->birthYear << "." << "\n";
    count++;
  }
  for (int i = 0; i < person->getNumChildren(); i++) {
    printGenerationHelper(person->getChild(i), gen-1, count);
  }
}

void printGeneration(Tree<Person*> *family, int gen) {
  cout << "Members of generation " << gen << ": " << "\n";
  int num = 0;
  printGenerationHelper(family->getRoot(), gen, num);
  cout << "Found " << num << " family members." << "\n";
}

Tree<Person*> *parseFile(string filename) {
  ifstream data(filename.c_str());
  if (!data.is_open()) {
    cout << "Sorry, the file 'genealogy.txt' could not be opened.\n"
      << "It is needed for this program. Please make sure it\n"
      << "can be found in the current directory and has suitable\n"
      << "file permissions.\n";
    return nullptr;
  }

  Tree<Person*> *family = new Tree<Person*>();

  string line;
  while ( getline(data, line) ) {
    Person *p = Person::parseLine(line);
    if (p == nullptr)
      continue; // skip any lines that could not be parsed
    if (family->isEmpty()) {
      family->addAsRoot(p);
    } else  {
      string parentName = "Unknown";
      if (p->lineage.rfind("son of ", 0) == 0)
        parentName = p->lineage.substr(7); // everything after "son of "
      else if (p->lineage.rfind("daughter of ", 0) == 0)
        parentName = p->lineage.substr(12); // everything after "daughter of "
      Person* parent = findPerson(family, parentName);
      if (parent == nullptr || !family->addAsChild(p, parent)) {
         cout << "Oops, this person's parent, " << parentName << " doesn't appear to be part of this family:\n"
           << "  " << p->toString() << "\n";
         delete p;
      }
    }
  }

  return family;
}

int main(void) {
  Tree<Person*> *family = parseFile("genealogy.txt");

  cout << "The entire family tree:\n";
  printFamilyTree("", family->getRoot());
  cout << "\n";

  cout << "Portion of the family tree showing Indira Gandhi and her descendents:\n";
  TreeNode<Person*> *indiraNode = family->findNode(findPerson(family, "Indira Gandhi"));
  printFamilyTree("", indiraNode);
  cout << "\n";
  
  TreeNode<Person*> *vijayaNode = family->findNode(findPerson(family, "Vijaya Lakshmi Pandit"));
  cout << "Children of Vijaya Lakshmi Pandit are:\n";
  printChildren(vijayaNode);
  cout << "\n";

  printFriendsOf(family, "Balwant Kumar Nehru");
  cout << "\n";
  
  printPrimeMinisters(family);
  cout << "\n";

  printAncestryOf(family, "Anasuya Gandhi");
  printAncestryOf(family, "Prof. Fitzsimmons");
  cout << "\n";

  printGeneration(family, 4);
  cout << "\n";

  return 0;
}
