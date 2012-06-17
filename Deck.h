/*
 Deck.h
 
 Declaration of deck class.
 */

#ifndef _DECK_H_
#define _DECK_H_

#include <ostream>
#include <vector>

#include "Card.h"

class Deck {
	
	public:
		Deck();
		~Deck();
		void shuffle();
        std::vector<const Card*> dealPlayerHand();
		friend std::ostream &operator<<(std::ostream &, const Deck &);

	private:
        int cards_left_;
        std::vector<const Card*> cards_;
};

std::ostream &operator<<(std::ostream &, Deck &);

#endif /* _DECK_H_ */
