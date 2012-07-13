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

    // if legal moves available, play the first available legal move
	if(legalCards.size() != 0) {
		Role::playCard(*legalCards[0]);
    // otherwise discard first available card
	} else {
		Role::discardCard(*hand[0]);
	}
}

