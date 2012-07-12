/*
 Game.h
 
 Declaration of Game class.
 */

#ifndef _GAME_H_
#define _GAME_H_

#include "Card.h"
#include "CardList.h"
#include "Deck.h"
#include "Player.h"
#include <vector>

class Game {

public:
	Game();
	~Game();

	//Accessors
	Player* getPlayer(int);

	//Mutators
	void seed(int);
	void setPlayerType(int,bool);
	void playerRageQuit(int);
	void playCard(Card*);
	void startNewGame();
	void endGame();
	void newRound();
	void endRound();
	void notify();
	
private:
    const int MAX_TURNS = 52;			// maximum number of plays
    const int ENDGAME_SCORE = 80;		// score at which game ends

	int seed_;							// value used in shuffling algorithm
	int currPlayer_;					// the player who is currently playing cards
	int currTurn_;						// the turn number to keep track of when game is over
    vector<Player*> players_;			// list of the players who are in the game
    Deck game_deck_;					// Deck of cards used to play the game
	CardList table_; 	            	// played cards
	
	void gameOver();
};

#endif
