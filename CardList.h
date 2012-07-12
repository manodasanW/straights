/*
 CardList.h
 
 Declaration of CardList which is basically an enscapulation of vectors with control over the functions used, and what they do.
 */

#ifndef _CARDLIST_H_
#define _CARDLIST_H_

#include <vector>
#include "card.h"

class CardList : public Subject {

public:
	void add(const Card *);
	void reserve(int);
	const Card* remove(const Card&);
	void clear ();
	int find(const Card&);
	int size();
	Card* operator[](int);
private:
	std::vector<const Card*> cardList_;
};

#endif
