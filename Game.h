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

class Player;		// forward declaration to prevent circular dependencies

// Game class - fascade class
class Game {

public:
	Game();											// constructor
	~Game();										// destructor

	//Accessors
    int getCurrentPlayerId() const;					// gets the id of the current player
    int getScore(int) const;						// gets the score of the given player
	int getDiscardCount(int) const;					// gets the number of discards by the given player
    const CardList &getCurrentPlayerHand() const;	// gets the hand of the current player
    const CardList &getTable() const;				// gets the table which is the cards already played
	bool roundOver() const;							// whether a round is over or not
    
	//Mutators
	void seed(int);									// allows to set seed value
	void setPlayerType(int,bool);					// sets what type (AI, HUMAN) the given player is
	void playerRageQuit();							// performs a rage quit on the current player
	bool play(const Card& card);					// makes the current player play the given card, returns false if can not be played
	void addToTable(const Card*);					// adds the given card to the table (card was played)
	void startNewGame();							// starts a new game - resets variables and table
	void endGame();									// ends the current game
	void newRound();								// resets the deck and hands out new cards
	void endRound();								// ends the current round as cards are done (updates score)
	void notify();
	void subscribeView(Observer* observer);			// Adds view to be observers of the Subject classes
	
private:
    const int MAX_TURNS;							// maximum number of plays
    const int ENDGAME_SCORE ;						// score at which game ends

	int seed_;										// value used in shuffling algorithm
	int currPlayer_;								// the player who is currently playing cards
	int currTurn_;									// the turn number to keep track of when game is over
	bool roundOver_;								// whether the current round is over
    std::vector<Player*> players_;					// list of the players who are in the game
    Deck game_deck_;								// Deck of cards used to play the game
	CardList table_; 	            				// played cards
	
	void gameOver();								// Calculates winner
};

#endif
