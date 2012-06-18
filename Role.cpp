#include "Role.h"
#include "Card.h"
#include <iostream>

using namespace std;

/**
	Constructor/Destructor
**/

//Constructs the object which will handle the logic of the game
//Player variable is used to access fields in player such as the cards
Role::Role(Player* player)
	:player_(player) {
}

// Destructor
Role::~Role() {
	player_ = NULL;
}

/**
	Functions related to game logic
**/

// Plays the given card
const Card* Role::playCard(const CardList& table, const Card& card) {
	const CardList legalCards = GameLogic::legalMoves(table, getPlayerHand());

	int cardIndex = CardOperations::find(legalCards, card);
	if(cardIndex == -1)	{
		throw IllegalPlayException();
	}
	
	printMove(card, true);

	const Card* played = CardOperations::remove(player_->hand_, card);
	return played;
}


void Role::discardCard(const CardList& table, const Card& card) {
	const CardList legalCards = GameLogic::legalMoves(table, getPlayerHand());
	
	if(legalCards.size() != 0) {
		throw IllegalDiscardException();
	}

	printMove(card, false);

	const Card* deletedCard = CardOperations::remove(player_->hand_, card);
	CardOperations::add(player_->discards_, deletedCard);
}
		
const CardList& Role::getPlayerHand() const {
	return player_->hand_;
}

void Role::printMove(const Card& card, bool play) {
	int playerId = player_->id();
	string move = play ? " plays " : " discards ";

	cout << "Player " << playerId << move << card << "." << endl;
}


//Given the cards already played by all players and a player's hand, determines the legal moves which can be done by the player
const CardList GameLogic::legalMoves(const CardList& table, const CardList& hand) {
	CardList legalMoves;

	for (unsigned int index = 0; index < hand.size(); index++) {
		const Card * card = hand[index];

		int lowerRankIndex = -1;
		int higherRankIndex = -1;

		if (card->getRank() != ACE) {
			Card lowerRank = Card(card->getSuit(), (Rank) (card->getRank() - 1));
			lowerRankIndex = CardOperations::find(table, lowerRank);
		}
		
		if (card->getRank() != KING) {
			Card higherRank = Card(card->getSuit(), (Rank)(card->getRank() + 1));
			higherRankIndex = CardOperations::find(table, higherRank);
		}

		if (card->getRank() == SEVEN || lowerRankIndex !=-1 || higherRankIndex != -1) {
			CardOperations::add(legalMoves, card);
		}
	}

	return legalMoves;
}

/**
	Exception classes
**/

Role::IllegalPlayException::IllegalPlayException () {
}

const char* Role::IllegalPlayException::what() const throw () {
	return "This is not a legal play.";
}

Role::IllegalDiscardException::IllegalDiscardException () {
}

const char* Role::IllegalDiscardException::what() const throw () {
	return "You have a legal play. You may not discard.";
}
