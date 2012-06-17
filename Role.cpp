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

// Does nothing as it doesn't own player and has no other attributes
Role::~Role() {
}

/**
	Functions related to game logic
**/

// Plays the given card
const Card* Role::playCard(const vector<const Card*> table, const Card& card) {
	vector<const Card*> legalCards = GameLogic::legalMoves(table, getPlayerHand());

	int cardIndex = CardSet::find(legalCards, card);
	if(cardIndex == -1)	{
		throw IllegalPlayException();
	}
	
	printMove(card, true);

	const Card* played = CardSet::remove(player_->hand_, card);
	return played;
}


void Role::discardCard(const vector<const Card*> table, const Card& card) {
	vector<const Card*> legalCards = GameLogic::legalMoves(table, getPlayerHand());
	
	if(legalCards.size() != 0) {
		throw IllegalDiscardException();
	}

	printMove(card, false);

	const Card* deletedCard = CardSet::remove(player_->hand_, card);
	CardSet::add(player_->discards_, deletedCard);
}
		
const vector<const Card*> Role::getPlayerHand() const {
	return player_->hand_;
}

void Role::printMove(const Card& card, bool play) {
	int playerId = player_->id();
	string move = play ? " plays " : " discards ";

	cout << "Player " << playerId << move << card << "." << endl;
}

/**
	Helper functions
**/

// Adds the specified card to the list of cards
void CardSet::add(vector<const Card*>& set, const Card* card) {
	set.push_back(card);
}

// Removes the specified card from the list of cards
// Assumes the given card is in the list of cards
// Returns the card which was deleted
const Card* CardSet::remove(vector<const Card*>& set, const Card card) {
	int indexToDelete = find(set, card);
	const Card* ret = set[indexToDelete];

	set.erase(set.begin() + indexToDelete);
	return ret;
}

//Given a card, determines the index of the card in the set passed which can be the table or player's hand
//Returns -1 if card is not found, otherwise the index of the card in the hand
int CardSet::find(vector<const Card*> set, const Card& card) {
	// loops through all cards in set, and determines if this is the card being looked for
	for (unsigned int index = 0; index < set.size(); index++) {
		if (*set[index] == card) {
			return index;
		}
	}

	// card not found
	return -1;
}

//Given the cards already played by all players and a player's hand, determines the legal moves which can be done by the player
vector<const Card*> GameLogic::legalMoves(vector<const Card*> table, vector<const Card*> hand) {
	vector<const Card*> legalMoves;

	for (unsigned int index = 0; index < hand.size(); index++) {
		const Card * card = hand[index];

		int lowerRankIndex = -1;
		int higherRankIndex = -1;

		if (card->getRank() != ACE) {
			lowerRankIndex = CardSet::find(table, Card(card->getSuit(), (Rank) (card->getRank() - 1)));
		}
		
		if (card->getRank() != KING) {
			higherRankIndex = CardSet::find(table, Card(card->getSuit(), (Rank)(card->getRank() + 1)));
		}

		if (card->getRank() == SEVEN || lowerRankIndex !=-1 || higherRankIndex != -1) {
			CardSet::add(legalMoves, card);
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
