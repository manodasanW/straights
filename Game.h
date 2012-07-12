/*
 Game.h
 
 Declaration of Game class.
 */

#ifndef _GAME_H_
#define _GAME_H_

#include "Card.h"
#include "CardOps.h"
#include "Deck.h"
#include "Player.h"

class Game {

public:
	Game();
	~Game();

	//Accessors
	Player* getPlayer(int);

	//Mutators
	void seed(int);
	void playCard(Card*);
	void startNewGame();
	void endGame();
	void newRound();
	void endRound();
	
private:
    const int MAX_TURNS = 52;			// maximum number of plays
    const int ENDGAME_SCORE = 80;		// score at which game ends

	int seed;							// value used in shuffling algorithm
	int currPlayer;						// the player who is currently playing cards
	int currTurn;						// the turn number to keep track of when game is over
    vector<Player*> players;			// list of the players who are in the game
    Deck game_deck;						// Deck of cards used to play the game
	CardList table; 	            	// played cards
	
	void gameOver();

};

#endif
