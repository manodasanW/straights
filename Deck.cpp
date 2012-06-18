/*
 Deck.cpp
 
 Definitions for Deck class.
 */

#include <cstdlib>
#include <ostream>
#include <vector>

#include "Card.h"
#include "Deck.h"

using namespace std;

namespace {
    const int CARD_COUNT = 52;
    const int HAND_SIZE = 13;
}

// Deck constructor
Deck::Deck() : cards_left_(CARD_COUNT) {
    cards_.reserve(CARD_COUNT);
    // add all standard playing cards to deck in order
    for (int s = 0; s < SUIT_COUNT; s++) {
        for (int r = 0; r < RANK_COUNT; r++) {
            Card *c = new Card((Suit)s, (Rank)r);
            cards_.push_back(c);
        }
    }
}

// Deck destructor
Deck::~Deck() {
    // get rid of all playing cards
    for (int i = 0; i < cards_.size(); i++) {
        delete cards_[i];
    }
}


// repopulate deck
void Deck::repopulate() {
    cards_left_ = CARD_COUNT;
}

// copied and pasted from given shuffle.cpp

/* To ensure that the your cards are ordered the same way as
 the given program, use this shuffling algorithm.
 
 CARD_COUNT is the constant 52
 cards_ is an array of pointers to cards
 */

void Deck::shuffle(){
	int n = CARD_COUNT;
    
	while ( n > 1 ) {
		int k = (int) (lrand48() % n);
		--n;
		const Card *c = cards_[n];
		cards_[n] = cards_[k];
		cards_[k] = c;
	}
}

// returns a vector of 13 cards for a player to use
vector<const Card *> Deck::dealPlayerHand() {
    vector<const Card *> hand;
    hand.reserve(HAND_SIZE);
    
    // grab next 13 cards and copy them to hand vector
    for (int i = 0; i < HAND_SIZE; i++) {
        int index = CARD_COUNT - cards_left_ + i;
        if (index >= 0) {
            hand.push_back(cards_[index]);
        }
    }
    
    // mark those 13 cards as used
    cards_left_ -= HAND_SIZE;
    
    return hand;
}

// for use with cout and family
ostream & operator<<(ostream &o, const Deck &d) {
    int index = 0;
    // 13 cards/line
    for (int i = 0; i < SUIT_COUNT; i++) {
        for (int j = 0; j < RANK_COUNT; j++) {
            if (j == 0) {
                o << d.cards_[index];
            }
            else {
                o << " " << d.cards_[index];
            }
            index++;
        }
        o << endl;
    }
    return o;
}
