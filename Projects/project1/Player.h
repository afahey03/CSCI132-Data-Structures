// Name: Aidan Fahey
// Date: 09/13/2022
// Project 1
// Initializes functions

#ifndef PLAYER_H_
#define PLAYER_H_

#include "ArrayBag.h"
#include <string>

/** randInRange produces a pseudo-random integer between lo and hi,
 * inclusive. For example, randInRange(1, 100) may pick 1, 100, or
 * any number between them.
 * @precondition  lo <= hi
 * @return  A number r, such that lo <= r and r <= hi
 */
int randInRange(int lo, int hi);

class Player
{
public:
  Player(std::string name);
  void clearHand();
  void clearPrizes();
  void throwDice();
  void showHand();
  std::string getHand();
  int countPrizes();
  bool addPrize(std::string prize);
  std::string getName();
  void addGameWin();
  int getGamesWon();

private:
  void computeHand();

  static const int NUM_DICE = 5;
  ArrayBag<int> diceBag;
  ArrayBag<std::string> prizeBag;
  std::string hand;
  int gamesWon;
  std::string name;
};

#endif
