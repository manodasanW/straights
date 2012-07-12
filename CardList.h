/*
 CardList.h
 
 Declaration of CardList which is basically an enscapulation of vectors with control over the functions used, and what they do.
 */

#ifndef _CARDLIST_H_
#define _CARDLIST_H_

#include <vector>
#include "Card.h"
#include "Subject.h"

class CardList : public Subject {

public:
	CardList();
	virtual ~CardList();
	void add(const Card *);
	void reserve(int);
	const Card* remove(const Card&);
	void clear ();
	int find(const Card&) const;
	int size() const;
	void swap(int, int);
	const Card* operator[](int);
	const Card* operator[](int) const;
private:
	std::vector<const Card*> cardList_;
};

#endif
