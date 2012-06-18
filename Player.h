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

class Role;             // forward dec.

class Player {
	public:
        // constructor
        // first parameter: player id (1-4)
        // second parameter: is human?
		Player(int, bool);
		~Player();                              // destructor

        const Command play(const CardList&);    // gets user command given cards on the table
		void newRound(const CardList&);         // tells the player to setup for a new round
        void endRound();                        // tells the player to perform end-round housekeeping
        bool has7OfSpades() const;              // for determining who goes first

		int id() const;                         // id get accessor
		int score() const;                      // score get accessor

		friend class Role;

	private:
        void updateScore();                     // helper function; updates own score
    
		Role *role_;                            // role; human or AI
		CardList hand_;                         // player hand
		CardList discards_;                     // player discards
		int id_;                                // player id (1-4)
		int score_;                             // player score
};

#endif /* _PLAYER_H_ */
