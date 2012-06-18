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
    // get info about hand and legal moves available
	const CardList& hand = Role::getPlayerHand();
	const CardList legalCards = GameLogic::legalMoves(table, hand);

	Command command;
    
    // if legal moves available, play the first available legal move
	if(legalCards.size() != 0) {
		command.type = PLAY;
		command.card = *Role::playCard(table, *legalCards[0]);
    // otherwise discard first available card
	} else {
		command.type = DISCARD;
		command.card = *hand[0];

		Role::discardCard(table, *hand[0]);
	}
    
	return command;
}

