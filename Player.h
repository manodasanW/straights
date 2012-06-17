/*
 Player.h
 
 Declaration of Player class.
 */

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Role.h"

class Player {
	public:
		Player(int, bool);
		~Player();

        const Role::Message play();
		void newRound(std::vector<const Card*>);
		void updateScore();

		int id() const;
		int score() const;

	private:
		Role role_;
		std::vector<const Card*> hand_;
		std::vector<const Card*> discards_;
		int score_;
		int id_;
};

#endif /* _PLAYER_H_ */
