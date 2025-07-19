// Name: Chloe Chung
// CECS325
// Project 2 -- One Card War
// February 25, 2025

// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every single line of code in this program.


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
        void displayCard();
        int compareCard(Card otherCard);
};

class Deck
{
    private:
        vector<Card> newDeck;
    public:
        Deck();
        Card deal();
        void displayDeck();
        void shuffle();
        bool isEmpty();
};

Card::Card(char cardRank, char cardSuit) { 
    suit = cardSuit;

    if(cardRank == 'A') rank = 1;
    else if(cardRank == '2') rank = 2;
    else if(cardRank == '3') rank = 3;
    else if(cardRank == '4') rank = 4;
    else if(cardRank == '5') rank = 5;
    else if(cardRank == '6') rank = 6;
    else if(cardRank == '7') rank = 7;
    else if(cardRank == '8') rank = 8;
    else if(cardRank == '9') rank = 9;
    else if(cardRank == 'T') rank = 10;
    else if(cardRank == 'J') rank = 11;
    else if(cardRank == 'Q') rank = 12;
    else if(cardRank == 'K') rank = 13;

}

void Card::displayCard()
{
    const char allRanks[] = {'A', '2','3','4','5','6','7','8','9','T','J','Q', 'K'};

    if(rank == 10)
        cout << "10" << suit;
    else
        cout << allRanks[rank-1] << suit;
}

int Card::compareCard(Card otherCard)
{
    if(rank < otherCard.rank){
        return -1;
    }else if(otherCard.rank == rank){
        return 0;
    }else{
        return 1;
    }
}

// constructs default Deck (unshuffled)
Deck::Deck()
{
    // push card object into myDeck array to create array of 52 cards with 4 different suits
    //newDeck.resize(52);
    const char ranks[] = {'A', '2','3','4','5','6','7','8','9','T','J','Q', 'K'};
    const char suits[] = {'C', 'S', 'D', 'H'};

    for (int i = 0; i < 4; i++){
        for(int j = 0; j < 13; j++){
            newDeck.push_back(Card(ranks[j], suits[i])); 
        }
    }
}

// deal the card at the top of the deck and increment 
Card Deck::deal()
{
    if(isEmpty())
        throw string("Error - Deck is empty");
    Card topCard = newDeck.front();
    newDeck.erase(newDeck.begin());
    return topCard;
}

// display whole deck using display card function
void Deck::displayDeck()
{
    for(int i=0; i<52; i++){
        newDeck[i].displayCard();
        if(i<51) cout << ", ";
    }
    cout << endl;
}

// shuffle deck by randomly swapping card indices
void Deck::shuffle()
{
    srand(time(0));
    for(int i=0; i < 1000; i++){
        int a = rand() % 52;
        int b = rand() % 52;
        Card tempCard = newDeck[a];
        newDeck[a] = newDeck[b];
        newDeck[b] = tempCard;
    } 
}

bool Deck::isEmpty()
{
    return newDeck.empty();
}

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
    cout << "How many games will they play? ";
    int games;
    cin >> games;

    // display unshuffled deck, shuffle deck and redisplay it
    cout << endl << "Original Deck" << endl;
    myDeck.displayDeck();
    myDeck.shuffle();

    cout << endl << "Shuffled Deck" << endl;
    myDeck.displayDeck();
    
    // play number of rounds of the game as inputted; end when deck is empty
    for (int i = 0; i < games; i++){
        try{
            // deal card to each player and display them
            Card p1Card = myDeck.deal();
            Card p2Card = myDeck.deal();

            cout << endl << "Game " << i+1 << endl;
            cout << "--------" << endl;

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
            }else if(comparison == 1){
                cout << p1 << "=> Winner" << endl;
                p1Score += 1;
            }else{
                cout << "Tie game" << endl;
                ties += 1;
            }

        }catch(const string& errorMessage){
            cout << endl;
            cout << errorMessage << endl;
            break;
        }
    }

    // display final scores
    cout << endl << "------Final Stats------" << endl;
    cout << "       " << p1 << " vs. " << p2 << endl;
    cout << "Wins   " << p1Score << "            " << p2Score << endl;
    cout << "Losses " << p2Score << "            " << p1Score << endl;
    cout << "Ties   " << ties << "             "  << ties << endl;

    return 0;

}