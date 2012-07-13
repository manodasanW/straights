#include "AIRole.h"

using namespace std;

/**
	Constructor/Destructor
**/
AIRole::AIRole(Player* player)
		:Role(player) {
}

AIRole::~AIRole()
{
}

/**
	Game Logic
**/

// Decides what move to make, and performs the move
void AIRole::play() {
    // get info about hand and legal moves available
	const CardList legalCards = legalMoves();
	const CardList hand = playerHand();
	int cardIndex;

    // if legal moves available, play the first available legal move
	if(legalCards.size() != 0) {
		// gets the highest card and puts 7 as last case
		cardIndex = getSpecialIndex(legalCards, true);
			
		// plays the best card to play
		Role::playCard(*legalCards[cardIndex]);
    // otherwise discard first available card
	} else {
		// gets the lowest card and puts 7 as the last case
		cardIndex = getSpecialIndex(hand, false);

		// discards the best card to discard
		Role::discardCard(*hand[cardIndex]);
	}
}

// gets the highest or lowest card index depending on bool arg, and puts 7s as the last case 
int AIRole::getSpecialIndex(const CardList& list, bool highest) {
	// Find highest or lowest card in list
	int cardIndex = 0;
	int nextCardIndex = -1;
	// finds first two highest or lowest card;
	for(int a = 1; a < list.size(); a++) {
		if ((list[a]->getRank() > list[cardIndex]->getRank() && highest) || 
					(list[a]->getRank() < list[cardIndex]->getRank() && !highest)) {
			nextCardIndex = cardIndex;
			cardIndex = a;
		}
	}

	// checks if it is a 7, try to choose next best
	if(list[cardIndex]->getRank() == 7 && nextCardIndex != -1) {
		cardIndex = nextCardIndex;
	}

	return cardIndex;
}
