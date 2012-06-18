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
		Role(Player*);
		virtual ~Role();

		virtual const Command play(const CardList&) = 0;

	protected:
		const Card* playCard(const CardList&, const Card&);
		void discardCard(const CardList&, const Card&);
		const CardList& getPlayerHand() const;

		class IllegalPlayException : public std::exception {

			public:
				IllegalPlayException();	
				const char* what() const throw();
		};

		class IllegalDiscardException : public std::exception {

			public:
				IllegalDiscardException();
				const char* what() const throw();
		};
	private:
		void printMove(const Card&, bool);

		Player* player_;
};

namespace GameLogic {

	const CardList legalMoves(const CardList&, const CardList&);
}

#endif /* _ROLE_H_ */
