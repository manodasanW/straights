//	Helper functions used to manipulate vector of cards

#include "Card.h"
#include "CardOps.h"
#include <iostream>

using namespace std;

// Adds the specified card to the list of cards
void CardOperations::add(CardList& list, const Card* card) {
	list.push_back(card);
}

// Removes the specified card from the list of cards
// Assumes the given card is in the list of cards
// Returns the card which was deleted
const Card* CardOperations::remove(CardList& list, const Card& card) {
	int indexToDelete = find(list, card);
	const Card* ret = list[indexToDelete];

	list.erase(list.begin() + indexToDelete);
	return ret;
}

//Given a card, determines the index of the card in the list passed
//Returns -1 if card is not found, otherwise the index of the card in the list
int CardOperations::find(const CardList& list, const Card& card) {
	// loops through all cards in list, and determines if this is the card being looked for
	for (unsigned int index = 0; index < list.size(); index++) {
		if (*list[index] == card) {
			return index;
		}
	}

	// card not found
	return -1;
}

void CardOperations::printFormatted(const CardList &list) {
    const char *suit_strs[] = {"Clubs:", "Diamonds:", "Hearts:", "Spades:"};
    
    for (int i = 0; i < SUIT_COUNT; i++) {
        cout << suit_strs[i];
        for (int j = 0; j < RANK_COUNT; j++) {
            Card test_card = Card((Suit)i, (Rank)j);
            if (CardOperations::find(list, test_card) != -1) {
                cout << " " << j+1;
            }
        }
        cout << endl;
    }
}

void CardOperations::printUnFormatted(const CardList& list) {
	
	for (unsigned int index = 0; index < list.size(); index +=1) {
		if (index == 0) {
			cout << list[index];
		} else {
			cout << " " << list[index];
		}
	}
}
