#include "HumanRole.h"
#include <iostream>

using namespace std;

/**
	Constructor/Destructor
**/
HumanRole::HumanRole(Player* player)
		:Role(player) {
}

HumanRole::~HumanRole()
{
}

/**
	Game Logic
**/

const Command HumanRole::play(const vector<const Card*>& table) {
	const vector<const Card*> hand = Role::getPlayerHand();
	const vector<const Card*> legalMoves =  GameLogic::legalMoves(table, hand);
	Command command;

	cout << "Cards on the table:" << endl;
	CardSet::printFormatted(table);
	cout << "Your hand:";
	CardSet::printUnFormatted(hand);
	cout << "Legal plays:";
	CardSet::printUnFormatted(legalMoves);

	while(true) {
		cin >> command;

		try {
			if (command.type == PLAY) {
				command.card = *Role::playCard(table, command.card);
			} else if(command.type == DISCARD) {
				Role::discardCard(table, command.card);
			}
			break;
		} catch (exception& e) {
			cout << e.what() << endl;
		}
	}

	return command;
}

