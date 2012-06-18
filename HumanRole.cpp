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

const Command HumanRole::play(const CardList& table) {
	const CardList hand = Role::getPlayerHand();
	const CardList& legalMoves =  GameLogic::legalMoves(table, hand);
	Command command;

	cout << "Cards on the table:" << endl;
	CardOperations::printFormatted(table);
	cout << "Your hand:";
	CardOperations::printUnFormatted(hand);
	cout << "Legal plays:";
	CardOperations::printUnFormatted(legalMoves);

	while(true) {
		cout << ">";
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
