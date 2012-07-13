/*
 CardList.h
 
 Declaration of CardList which is basically an enscapulation of vectors with control over the functions used, and what they do.
 */

#ifndef _CARDLIST_H_
#define _CARDLIST_H_

#include <vector>
#include "Card.h"

// CardList class
class CardList {

public:
	CardList();										// constructor
	virtual ~CardList();							// destructor
	void add(const Card *);							// adds the given card to the list of cards
	const Card* remove(const Card&);				// removes the given card from the list of cards
	void clear ();									// removes all the cards
	int find(const Card&) const;					// searches for the requested card
	int size() const;								// number of cards in vecotr
	void swap(int, int);							// given two indexes swaps those cards
	const Card* operator[](int);					// opeartor [] for modification
	const Card* operator[](int) const;				// opeartor [] for access
private:
	std::vector<const Card*> cardList_;				// stores the cards
};

#endif /* _CARDLIST_H_ */

