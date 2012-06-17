/*
 Role.h
 
 Declaration of Role class.
 */

#ifndef _ROLE_H_
#define _ROLE_H_

#include <vector>
#include <exception>
#include "Player.h"
#include "Card.h"
#include "Command.h"

class Player;

class Role {

	public:
		Role(Player*);
		~Role();

		virtual const Command play(const std::vector<const Card*>&) = 0;

	protected:
		const Card* playCard(const std::vector<const Card*>, const Card&);
		void discardCard(const std::vector<const Card*>, const Card&);
		const std::vector<const Card*> getPlayerHand() const;

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

namespace CardSet {

	void add(std::vector<const Card*>&, const Card *);
	const Card* remove(std::vector<const Card*>&, const Card);
	int find(std::vector<const Card*>, const Card&);
}

namespace GameLogic {

	std::vector<const Card*> legalMoves(std::vector<const Card*>, std::vector<const Card*>);
}

#endif /* _ROLE_H_ */
