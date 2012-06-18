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
// table - set of cards which have been played
const Command AIRole::play(const CardList& table) {
	// updates the legal moves as this is a new round
	Role::updateLegalMoves(table);
    // get info about hand and legal moves available
	const CardList legalCards = legalMoves();
	const CardList hand = playerHand();

	Command command;	

    // if legal moves available, play the first available legal move
	if(legalCards.size() != 0) {
		command.type = PLAY;
		command.card = *Role::playCard(*legalCards[0]);
    // otherwise discard first available card
	} else {
		command.type = DISCARD;
		command.card = *hand[0];

		Role::discardCard(*hand[0]);
	}
    
	return command;
}

