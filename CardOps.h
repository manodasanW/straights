/*
 CardSet.h
 
 Declaration of CardSet namespace which contains functions to manipulate vector of cards.
 */

#ifndef _CARDSET_H_
#define _CARDSET_H_

#include <vector>
#include "Card.h"

typedef std::vector<const Card*> CardList;

namespace CardOperations {

	void add(CardList&, const Card *);
	const Card* remove(CardList&, const Card&);
	int find(const CardList&, const Card&);
	void printUnFormatted(const CardList&);
	void printFormatted(const CardList&);

}

#endif /* _CARDSET_H_ */
