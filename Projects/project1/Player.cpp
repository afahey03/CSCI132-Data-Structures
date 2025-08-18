// Name: Aidan Fahey
// Date: 09/13/2022
// Project 1
// Implements functions

#include "Player.h"
#include <cstdlib> // for rand()
#include <iostream>

Player::Player(std::string name)
{
  this->name = name;
  gamesWon = 0;
  hand = "";
}
  
void Player::clearHand()
{
  hand = "";
}

void Player::clearPrizes()
{
  prizeBag.clear();
}

void Player::throwDice()
{
  diceBag.clear();
  for (int i = 0; i < NUM_DICE; i++) {
    int diceRoll = randInRange(1, 6);
    diceBag.add(diceRoll);
    std::cout << diceRoll << "";
  }
  computeHand();

}

void Player::showHand()
{
  std::cout << hand;
}

std::string Player::getHand()
{
  return hand;
}
  
int Player::countPrizes()
{
  
  return prizeBag.getCurrentSize();
}

bool Player::addPrize(std::string prize)
{
  if (!prizeBag.getFrequencyOf(prize)) {
    prizeBag.add(prize);
    return true;
  } 
  return false;
}

void Player::addGameWin()
{
  gamesWon++;
}

int Player::getGamesWon()
{
  return gamesWon;
}

void Player::computeHand()
{
  int currFrequency[7];
  int max = 0;
  int secondToMax = 0;

  for (int i = 1; i < 7; i++) {
    currFrequency[i] = diceBag.getFrequencyOf(i);
  }
  for (int j = 1; j < 7; j++) {
    if (currFrequency[j] > max) {
      secondToMax = max;
      max = currFrequency[j];
    } else if (currFrequency[j] > secondToMax ) {
      secondToMax = currFrequency[j];
    }
    if (max == 1) {
      hand = "Assortment";
    }
    if (max == 2) {
      hand = "One Pair";
    }
    if (max == 2 && secondToMax == 2) {
      hand = "Two Pairs";
    }
    if (max == 3 && secondToMax == 2) {
      hand = "Full House";
    }
    if (max == 3) {
      hand = "Three of a Kind";
    }
    if (max == 4) {
      hand = "Four of a Kind";
    }
    if (max == 5) {
      hand = "Five of a Kind";
    }
  }
}

std::string Player::getName()
{
  return name;
}

int randInRange(int lo, int hi)
{
  double v = (double)rand();    // 0 <= v && v <= RAND_MAX
  double f = v / ((double)RAND_MAX+1);  // 0 <= f && f < 1.0
  return lo + (int)(f * (hi - lo + 1));
}  // end randInRange

