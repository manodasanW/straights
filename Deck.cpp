/*
 Deck.cpp
 
 Definitions for Deck class.
 */

#include <cstdlib>

#include "Deck.h"

using namespace std;

namespace {
    const int CARD_COUNT = 52;
    const int HAND_SIZE = 13;
}

// Deck constructor
Deck::Deck() : cards_left_(CARD_COUNT) {
    // add all standard playing cards to deck in order
    for (int s = 0; s < SUIT_COUNT; s++) {
        for (int r = 0; r < RANK_COUNT; r++) {
            Card *c = new Card((Suit)s, (Rank)r);
            cards_.add(c);
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
		cards_.swap(n,k);
	}
}

// returns a vector of 13 cards for a player to use
CardList Deck::dealPlayerHand() {
    CardList hand;
    
    // grab next 13 cards and copy them to hand vector
    for (int i = 0; i < HAND_SIZE; i++) {
        int index = CARD_COUNT - cards_left_ + i;
        if (index >= 0) {
            hand.add(cards_[index]);
        }
    }
    
    // mark those 13 cards as used
    cards_left_ -= HAND_SIZE;
    
    return hand;
}
