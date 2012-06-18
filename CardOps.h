/*
 CardOps.h
 
 Declaration of CardOps which contains functions to manipulate vector of cards and a typedef.
 */

#ifndef _CARDOPS_H_
#define _CARDOPS_H_

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

#endif /* _CARDOPS_H_ */
