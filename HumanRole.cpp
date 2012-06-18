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
	// Updates the legal moves as it is a new round
	Role::updateLegalMoves(table);

    // get info about hand and legal moves available
	const CardList legalCards = legalMoves();
	const CardList hand = playerHand();

	Command command;
    
    // present game info and player data to human player
	cout << "Cards on the table:" << endl;
	CardOperations::printFormatted(table);
	cout << "Your hand:";
	CardOperations::printUnFormatted(hand);
	cout << "Legal plays:";
	CardOperations::printUnFormatted(legalCards);

	while(true) {
        // get command from user
		cout << ">";
		cin >> command;

		try {
            // if a play command, play the card
			if (command.type == PLAY) {
				command.card = *Role::playCard(command.card);
            // if a discard command, discard the card
			} else if(command.type == DISCARD) {
				Role::discardCard(command.card);
			} // if
            // and we are done
			break;
		} catch (exception& e) {
            // user move was illegal, print error message and retry
			cout << e.what() << endl;
		} // catch
	} // while

	return command;
}
