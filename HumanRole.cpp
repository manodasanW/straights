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
    // get info about hand and legal moves available
	const CardList hand = Role::getPlayerHand();
	const CardList& legalMoves =  GameLogic::legalMoves(table, hand);
	Command command;
    
    // present game info and player data to human player
	cout << "Cards on the table:" << endl;
	CardOperations::printFormatted(table);
	cout << "Your hand:";
	CardOperations::printUnFormatted(hand);
	cout << "Legal plays:";
	CardOperations::printUnFormatted(legalMoves);

	while(true) {
        // get command from user
		cout << ">";
		cin >> command;

		try {
            // if a play command, play the card
			if (command.type == PLAY) {
				command.card = *Role::playCard(table, command.card);
            // if a discard command, discard the card
			} else if(command.type == DISCARD) {
				Role::discardCard(table, command.card);
			}
            // and we are done
			break;
		} catch (exception& e) {
            // user move was illegal, print error message and retry
			cout << e.what() << endl;
		}
	}

	return command;
}
