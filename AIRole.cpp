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
const Command AIRole::play(const vector<const Card*>& table) {
	const vector<const Card*> hand = Role::getPlayerHand();
	vector<const Card*> legalCards = GameLogic::legalMoves(table, hand);

	Command command;	

	if(legalCards.size() != 0) {
		command.type = PLAY;
		command.card = *Role::playCard(table, *legalCards[0]);
	} else {
		command.type = DISCARD;
		command.card = *hand[0];

		Role::discardCard(table, *hand[0]);
	}

	return command;
}

