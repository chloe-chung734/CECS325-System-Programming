// Name: Chloe Chung
// CECS325
// Project 1 -- One Card War
// February 13, 2025

// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every single line of code in this program.

#include <iostream>
#include <string>
#include "deck.h"
#include "card.h"

using namespace std;

int main()
{
    // create deck and initialize score counters
    Deck myDeck;
    int p1Score = 0;
    int p2Score = 0;
    int ties = 0;

    cout << "Enter the name of the first player: ";
    string p1;
    cin >> p1;
    cout << "Enter the name of the second player: ";
    string p2;
    cin >> p2;

    // display unshuffled deck, shuffle deck and redisplay it
    cout << endl << "Original Deck" << endl;
    myDeck.displayDeck();
    myDeck.shuffle();

    cout << endl << "Shuffled Deck" << endl;
    myDeck.displayDeck();
    
    // play 26 rounds of the game
    for (int i = 0; i < 26; i++){
        cout << endl << "Game " << i+1 << endl;
        cout << "--------" << endl;

        // deal card to each player and display them
        Card p1Card = myDeck.deal();
        Card p2Card = myDeck.deal();

        cout << p1 << "=>";
        p1Card.displayCard();
        cout << endl;

        cout << p2 << "=>";
        p2Card.displayCard();
        cout << endl;

        // compare the two player's cards
        int comparison = p1Card.compareCard(p2Card);

        // display winner / result of each round
        if(comparison == -1){
            cout << p2 << "=> Winner" << endl;
            p2Score += 1;
        }
        else if(comparison == 1){
            cout << p1 << "=> Winner" << endl;
            p1Score += 1;
        }
        else{
            cout << "Tie game" << endl;
            ties += 1;
        }
    }

    // display final scores
    cout << "------Final Stats------" << endl;
    cout << "       " << p1 << " vs. " << p2 << endl;
    cout << "Wins   " << p1Score << "            " << p2Score << endl;
    cout << "Losses " << p2Score << "            " << p1Score << endl;
    cout << "Ties   " << ties << "             "  << ties << endl;

    return 0;

}

