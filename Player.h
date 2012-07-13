/*
 Player.h
 
 Declaration of Player class.
 */

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Card.h"
#include "Role.h"
#include "CardList.h"
#include "Subject.h"

class Role;             // forward dec.

class Player : public Subject {
	public:
        // constructor
        // first parameter: player id (1-4)
        // second parameter: is human?
		Player(int, bool, Game*);
		~Player();                              // destructor

		void setRole(bool);

		void newRound(const CardList&);         // tells the player to setup for a new round
        void endRound();                        // tells the player to perform end-round housekeeping
		void rageQuit();						// switches the role of the player from human to computer
        bool has7OfSpades() const;              // for determining who goes first

		int id() const;                         // id get accessor
		int score() const;                      // score get accessor
		int discardCount() const;				// gets the number of discards
        const CardList &playerHand() const;     // player hand get accessor
		void updateLegalMoves(const CardList&);	// updates the player's legal moves
		bool hasLegalMoves() const;				// whether player has legal moves
		const CardList& legalMoves() const;		// gets the legal moves
        void makeHintRequest();                 // makes a hint request

		void won(bool);							// sets the current player won
		bool won() const;						// accessor to check if current player won
    
        void resetScore();						// resets the score stored in the player class
    
		void notifyTurn(const CardList&);		// notifies player it is thier turn
		void playCard(const Card& card);		// plays the given card
		void discardCard(const Card& card);		// discards the given card
    
		friend class Role;

	private:
        void updateScore();                     // helper function; updates own score
    
		Role *role_;                            // role; human or AI
		CardList hand_;                         // player hand
		CardList discards_;                     // player discards
		CardList legalMoves_;					// legal moves able to be done by player
		int id_;                                // player id (1-4)
		int score_;                             // player score
		bool won_;								// whether player won game
};

#endif /* _PLAYER_H_ */
