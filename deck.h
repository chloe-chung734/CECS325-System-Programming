#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <string>

using namespace std;

class Deck
{
    private:
        Card newDeck[52];
        int top = 0;
    public:
        Deck();
        Card deal();
        void displayDeck();
        void shuffle();
};

#endif