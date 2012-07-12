#include "CardList.h"

using namespace std;

// Adds the specified card to the list of cards
void CardList::add(const Card* card) {
	cardList_.push_back(card);
	notify();
}

void CardList::reserve(int size) {
	cardList_.reserve(size);
}

// Removes the specified card from the list of cards
// Assumes the given card is in the list of cards
// Returns the card which was deleted
const Card* CardList::remove(const Card& card) {
	// finds the index in which the card is in
	int indexToDelete = find(cardList_, card);
	const Card* ret = cardList_[indexToDelete];

	cardList_.erase(list.begin() + indexToDelete);
	notify();
	return ret;
}

void CardList::clear() {
	cardList_.clear();
	notify();
}

//Given a card, determines the index of the card in the list passed
//Returns -1 if card is not found, otherwise the index of the card in the list
int CardList::find(const Card& card) {
	// loops through all cards in list, and determines if this is the card being looked for
	for (unsigned int index = 0; index < cardList_.size(); index++) {
		if (*cardList_[index] == card) {
			return index;
		}
	}
	// card not found
	return -1;
}

int CardList::size() {
	return cardList_.size();
}

Card* CardList::operator[](int index) {
	return cardList_[index]; 
}
