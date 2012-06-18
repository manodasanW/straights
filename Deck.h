/*
 Deck.h
 
 Declaration of deck class.
 */

#ifndef _DECK_H_
#define _DECK_H_

#include "CardOps.h"
#include <ostream>

#include "Card.h"

class Deck {
	
	public:
		Deck();
		~Deck();
        void repopulate();
		void shuffle();
        CardList dealPlayerHand();
		friend std::ostream &operator<<(std::ostream &, const Deck &);

	private:
        int cards_left_;
        CardList cards_;
};

#endif /* _DECK_H_ */
