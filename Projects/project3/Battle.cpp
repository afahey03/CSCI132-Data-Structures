// Name: Aidan Fahey
// Email: amfahe25@g.holycross.edu
// Assignment: Project 3
// Runs the "Battle" game

#include "ArrayStack.h"
#include <iostream>
#include "Deck.h"
#include <string>
using namespace std;

int main() {

    srand(65);

    Deck deck; // deck of cards
    ArrayStack<Card> playerCards; // players card pile
    ArrayStack<Card> CPUCards; // computers card pile
    ArrayStack<Card> prizePile; // prize pile when a round ends in a tie
    ArrayStack<Card> playerWinPile; // players win pile
    ArrayStack<Card> CPUWinPile; // computers win pile

    for (int i = 0; i < 4; i++) { // shuffles the deck 4 times
        deck.shuffle();
    }
    
    int cards; // number of dealt cards
    cout << "Welcome to Battle." << "\n";
    cout << "Shuffling cards." << "\n";
    cout << "How many cards in each hand (not more than 26)? ";
    cin >> cards;

    // Preconditions: int cards is greater than 0 and less than 27
    // Post conditions: deals each player int cards number of cards
    while (true) {
        if (cards > 26) {
            cout << "Please enter a number less than 27: ";
            cin >> cards;
        }
        if (cards < 1) {
            cout << "Please enter a number greater than zero: ";
            cin >> cards;
        }
        if (cards < 27 && cards >= 1) {
            break;
        }
    } // end of number of cards while loop

    cout << "Dealing " << cards << " cards to each player" << "\n";
    for (int i = 0; i < cards; i++) {
        playerCards.push(deck.dealCard());
        CPUCards.push(deck.dealCard());
    }
    cout << "\n";
    
    int round = 0; // number of rounds
    char continueOrNot = 'y'; // dictactes whether a round happens or not, initialized to 'y' to start the first round
    while (continueOrNot == 'y') {

        if (playerCards.isEmpty()) { // replenishes player pile with winnings
            cout << "User replenishes draw pile using winnings:" << "\n";
            while (!playerWinPile.isEmpty()) {
                playerCards.push(playerWinPile.peek());
                cout << "Moving ";
                playerWinPile.peek().printCard();
                cout << "\n";
                playerWinPile.pop();
            }
        }

        if (CPUCards.isEmpty()) { // replenishes computer pile with winnings
            cout << "Computer replenishes draw pile using winnings:" << "\n";
            while (!CPUWinPile.isEmpty()) {
                CPUCards.push(CPUWinPile.peek());
                cout << "Moving ";
                CPUWinPile.peek().printCard();
                cout << "\n";
                CPUWinPile.pop();
            }
        }

        round++;
        Card playerCard = playerCards.peek();
        Card CPUCard = CPUCards.peek();

        cout << "User has " << playerCards.size() << " cards and draws ";
        playerCard.printCard();
        cout << "." << "\n";
        cout << "Computer has " << playerCards.size() << " cards and draws ";
        CPUCard.printCard();
        cout << "." << "\n";

        if (playerCard.getValue() > CPUCard.getValue()) { // Player wins the round
            cout << "User wins round " << round << "." << "\n";
            playerWinPile.push(playerCards.peek());
            playerWinPile.push(CPUCards.peek());
            playerCards.pop();
            CPUCards.pop();
            if (!prizePile.isEmpty()) { // Adds prizepile to player deck after winning subsequent tie round
                cout << "User moves " << prizePile.size() << " to winnings:" << "\n";
                while (!prizePile.isEmpty()) {
                    cout << "Moving ";
                    prizePile.peek().printCard();
                    cout << "\n";
                    playerWinPile.push(prizePile.peek());
                    prizePile.pop();
                }
            }
        } // end of player win if statement
        
        if (CPUCard.getValue() > playerCard.getValue()) { // Computer wins the round
            cout << "Computer wins round " << round << "." << "\n";
            CPUWinPile.push(playerCards.peek());
            CPUWinPile.push(CPUCards.peek());
            playerCards.pop();
            CPUCards.pop();
            if (!prizePile.isEmpty()) { // Adds prizepile to computer deck after winning subsequent tie round
                cout << "Computer moves " << prizePile.size() << " to winnings:" << "\n";
                while (!prizePile.isEmpty()) {
                    cout << "Moving ";
                    prizePile.peek().printCard();
                    cout << "\n";
                    CPUWinPile.push(prizePile.peek());
                    prizePile.pop();
                }
            }
        } // end of computer win if statement

        if (playerCard.getValue() == CPUCard.getValue()) { // Puts player and computer card in prizepile when tie
            prizePile.push(playerCards.peek());
            prizePile.push(CPUCards.peek());
            playerCards.pop();
            CPUCards.pop();
            cout << "Nobody wins round " << round << "." << "\n";
        }
        
        // Preconditions: char continueOrNot is 'y' or 'n'
        // Postconditions: A new round will start or the game will end
        cout << "Do you want to continue (y/n)? ";
        while (true) {
            cin >> continueOrNot;
            if (continueOrNot != 'y' && continueOrNot != 'n') {
                cout << "Please enter either 'y' or 'n': ";
            }
            if (continueOrNot == 'y' || continueOrNot == 'n') {
                break;
            }
        } // end of 'y' or 'n' while loop
        cout << "\n";
        if (continueOrNot == 'n')
        break;

    } // end of round while loop

    cout << "User has " << playerWinPile.size() << " cards total." << "\n";
    cout << "Computer has " << CPUWinPile.size() << " cards total" << "\n";
    cout << "There are " << prizePile.size() << " cards in the prize pile." << "\n";

    if (playerWinPile.size() > CPUWinPile.size()) { // User wins
        cout << "User wins!" << "\n";
    }
    if (playerWinPile.size() < CPUWinPile.size()) { // Computer wins
        cout << "Computer wins!" << "\n";
    }
    if (playerWinPile.size() == CPUWinPile.size()) { // Tie
        cout << "It's a tie!" << "\n";
    }

} // end of main