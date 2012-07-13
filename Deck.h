/*
 Deck.h
 
 Declaration of deck class.
 */

#ifndef _DECK_H_
#define _DECK_H_

#include "CardList.h"
#include <ostream>

#include "Card.h"

class Deck {
	
	public:
		Deck();															//constructor
		~Deck();														//destructor
        void repopulate();												//Refills the deck with cards 
		void shuffle();													//Shuffles the deck of cards
        void reset();                                                   // resets deck to sorted state
        CardList dealPlayerHand();										//Gives out 13 cards to the play

	private:
        int cards_left_;												// number of cards left in the decl
        CardList cards_;												// stores the cards
};

#endif /* _DECK_H_ */
