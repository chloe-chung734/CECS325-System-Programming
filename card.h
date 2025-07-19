#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>

using namespace std;

class Card
{
    private:
        int rank;
        char suit;
    public:
        Card(char cardRank, char cardSuit);
        Card();
        void displayCard();
        int compareCard(Card otherCard);
};

#endif
