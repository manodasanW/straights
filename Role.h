/*
 Role.h
 
 Declaration of Role class.
 */

#ifndef _ROLE_H_
#define _ROLE_H_

#include <exception>
#include "Player.h"
#include "Card.h"
#include "Command.h"
#include "CardOps.h"

class Player;

class Role {

	public:
		Role(Player*);												// constructor - takes player who is using this role
		virtual ~Role();											// destructor

		virtual const Command play(const CardList&) = 0;			// Performs action based on whether the player is a human or AI

	protected:
		const Card* playCard(const Card&);							// Plays the card given card, throws exception if illegal move
		void discardCard(const Card&);								// Discards the card, throws exception will player can play
		const CardList& playerHand() const;							// Gets the hand of the player to calculate legal moves
		const CardList& legalMoves() const;							// Gets the legal moves for the current round
		void updateLegalMoves(const CardList&);						// updates the legal moves for the current round and takes the table as parameter

		// Exception classes
		class IllegalPlayException : public std::exception {	

			public:
				IllegalPlayException();								// constructor of exception class
				const char* what() const throw();					// reason for exception
		};

		class IllegalDiscardException : public std::exception {

			public:
				IllegalDiscardException();							// constructor of exception class
				const char* what() const throw();					// reason for exception
		};
	private:
		void printMove(const Card&, bool);							// prints the result of the play action

		Player* player_;											// the player who is using this role
		CardList legalMoves_;									// stores the legal moves for the current round
};

// Helper functions to the logic of the game
namespace GameLogic {

	CardList legalMoves(const CardList&, const CardList&);	// Determines the legal moves given the table, and hand
}

#endif /* _ROLE_H_ */
