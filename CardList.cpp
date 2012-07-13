#include "CardList.h"
#include <iostream>

using namespace std;

CardList::CardList() {
}

CardList::~CardList()
{}

// Adds the specified card to the list of cards
void CardList::add(const Card* card) {
	cardList_.push_back(card);
}

// Removes the specified card from the list of cards
// Assumes the given card is in the list of cards
// Returns the card which was deleted
const Card* CardList::remove(const Card& card) {
	// finds the index in which the card is in
	int indexToDelete = find(card);
	const Card* ret = cardList_[indexToDelete];

	cardList_.erase(cardList_.begin() + indexToDelete);
	return ret;
}

void CardList::clear() {
	cardList_.clear();
}

//Given a card, determines the index of the card in the list passed
//Returns -1 if card is not found, otherwise the index of the card in the list
int CardList::find(const Card& card) const {
	// loops through all cards in list, and determines if this is the card being looked for
	for (unsigned int index = 0; index < cardList_.size(); index++) {
		if (*cardList_[index] == card) {
			return index;
		}
	}
	// card not found
	return -1;
}

int CardList::size() const {
	return cardList_.size();
}

void CardList::swap(int index1, int index2) {
	const Card *c = cardList_.at(index1);
	cardList_.at(index1) = cardList_.at(index2);
	cardList_.at(index2) = c;
}

const Card* CardList::operator[](int index) {
	return cardList_[index]; 
}

const Card* CardList::operator[](int index) const {
	return cardList_[index]; 
}
