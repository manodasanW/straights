/*
 Game.h
 
 Declaration of Game class.
 */

#ifndef _GAME_H_
#define _GAME_H_

#include "Card.h"
#include "CardList.h"
#include "Deck.h"
#include "Observer.h"
#include <vector>

class Player;

class Game {

public:
	Game();
	~Game();

	//Accessors
    int getCurrentPlayerId() const;
    int getScore(int) const;
    const CardList &getPlayerHand(int) const;
    const CardList &getTable() const;
    
	//Mutators
	void seed(int);
	void setPlayerType(int,bool);
	void playerRageQuit(int);
	void playCard(int id, const Card& card);
	void discardCard(int id, const Card& card);
	void playCard(const Card*);
	void startNewGame();
	void endGame();
	void newRound();
	void endRound();
	void notify();
	void subscribeView(Observer* observer);
	
private:
    const int MAX_TURNS;				// maximum number of plays
    const int ENDGAME_SCORE ;			// score at which game ends

	int seed_;							// value used in shuffling algorithm
	int currPlayer_;					// the player who is currently playing cards
	int currTurn_;						// the turn number to keep track of when game is over
    std::vector<Player*> players_;		// list of the players who are in the game
    Deck game_deck_;					// Deck of cards used to play the game
	CardList table_; 	            	// played cards
	
	void gameOver();
};

#endif
