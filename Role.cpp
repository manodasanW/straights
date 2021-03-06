#include "Role.h"
#include "Game.h"

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
	player_ = NULL;														// deinitalizes the variable to remove references to it
}

/**
	Functions related to game logic
**/

// Plays the given card in the game
void Role::playCard(const Card& card) {
	const CardList legalCards = legalMoves();							// gets the card which are legal to play

	// Determines whether the card being played is legal to play, otherwise exception is thrown
	int cardIndex = legalCards.find(card);
    
	if(cardIndex == -1)	{
		throw IllegalPlayException();
	}
	
	//Removes the card from the hand, and returns it so it can be added to the table
	const Card* played = player_->hand_.remove(card);
	player_->getGame()->addToTable(played);
	triggerPlayerUpdate(true);
}

// Discards the given card
void Role::discardCard(const Card& card) {
	const CardList legalCards = legalMoves();							// Gets the cards which are legal to play
	
	// Determines whether the user is in a situation that they had to discard, if not throws exception
	if(legalCards.size() != 0) {
		throw IllegalDiscardException();
	}

	// Removes card from hand, and adds to discard pile
	const Card* deletedCard = player_->hand_.remove(card);
	player_->discards_.add(deletedCard);
	triggerPlayerUpdate(true);
}
	
// Gets the players hand, to use to determine legalMoves	
const CardList& Role::playerHand() const {
	return player_->playerHand();
}

// Gets the card which are legal to play
const CardList& Role::legalMoves() const {
	return player_->legalMoves_;
}

// makes player notify all the elements subscribed to it
void Role::triggerPlayerUpdate(bool notifyGame) {
	player_->notify(notifyGame);
}

//Given the cards already played by all players and a player's hand, determines the legal cards which can be played by the player
CardList GameLogic::legalMoves(const CardList& table, const CardList& hand) {
	CardList legalMoves;									// used to store legal cards

	// In the case the table is empty, this means this play has 7 of spades, so he has to be forced to play it
	if(table.size() == 0) {
		// finds the 7S card, so we only got one instance of it
		int index = hand.find(Card(SPADE, SEVEN));
		const Card* sevenSpades = hand[index];
		legalMoves.add(sevenSpades);
		return legalMoves;
	}
 
	// loops through hand to determine which ones are legal to play
	for (int index = 0; index < hand.size(); index++) {
		const Card * card = hand[index];

		// Stores the index of lower rank and higher rank card to determine whether it exists or not
		int lowerRankIndex = -1;
		int higherRankIndex = -1;

		// Determines whether a lower rank or higher rank card exists
		if (card->getRank() != ACE) {
			Card lowerRank = Card(card->getSuit(), (Rank) (card->getRank() - 1));
			lowerRankIndex = table.find(lowerRank);
		}
		
		if (card->getRank() != KING) {
			Card higherRank = Card(card->getSuit(), (Rank)(card->getRank() + 1));
			higherRankIndex = table.find(higherRank);
		}

		// Determines whether the current card is legal to play
		if (card->getRank() == SEVEN || lowerRankIndex !=-1 || higherRankIndex != -1) {
			legalMoves.add(card);
		}
	}

	return legalMoves;
}

/**
	Exception classes
**/

// constructor
Role::IllegalPlayException::IllegalPlayException () {
}

// Reason for exception
const char* Role::IllegalPlayException::what() const throw () {
	return "This is not a legal play.";
}

// constructor
Role::IllegalDiscardException::IllegalDiscardException () {
}

// Reason for exception
const char* Role::IllegalDiscardException::what() const throw () {
	return "You have a legal play. You may not discard.";
}
