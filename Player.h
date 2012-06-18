/*
 Player.h
 
 Declaration of Player class.
 */

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Command.h"
#include "Card.h"
#include "Role.h"
#include "CardOps.h"

class Role;

class Player {
	public:
		Player(int, bool);
		~Player();

        const Command play(const CardList&);
		void newRound(const CardList&);
        void endRound();
        bool has7OfSpades() const;

		int id() const;
		int score() const;

		friend class Role;

	private:
        void updateScore();
    
		Role *role_;
		CardList hand_;
		CardList discards_;
		int id_;
		int score_;
};

#endif /* _PLAYER_H_ */
