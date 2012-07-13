#include "Game.h"

#include <cstdlib>
#include "Player.h"

using namespace std;

namespace helper {
    // deletes all the elements in a vector
    template <typename T>
    void cleanVectorMem(vector<T> v) {
        for (unsigned int i = 0; i < v.size(); i++) {
            delete v[i];
        }
    }
}

// constructor - initalizes everything
Game::Game()
	:MAX_TURNS(52), ENDGAME_SCORE(80), seed_(0), currPlayer_(0), currTurn_(0), roundOver_(true)   {
	// sets up 4 players
	for (int playerId = 0; playerId < 4; playerId++) {
		players_.push_back(new Player(playerId, true, this));
	}
}

// destructor
Game::~Game() {
	// deallocates all players
	helper::cleanVectorMem(players_);
}

// sets the seed value
void Game::seed(int seed) {
	seed_ = seed;	
}

// sets what of the player is the given player
void Game::setPlayerType(int id, bool isHuman) {
	players_[id]->setRole(isHuman);
}

// adds the given view to be an observer for the player model
void Game::subscribeView(Observer* observer) {
	// loops through all players
	for (unsigned int id = 0; id < players_.size(); id++) {
		players_[id]->subscribe(observer);
	}
}

// swaps the current player's human role with ai role
void Game::playerRageQuit() {
	players_[currPlayer_]->rageQuit();
	players_[currPlayer_]->notifyTurn(table_);
	
}

// player id get accessor
int Game::getCurrentPlayerId() const {
    return currPlayer_;
}

// whether given player is a winner
bool Game::winner(int id) const {
	return players_[id]->won();
}

// returns a card as a hint
const Card* Game::hint() const {
	// checks if there are any legal plays, if there is returns one of them, otherwise discard
	if(players_[currPlayer_]->hasLegalMoves()) {
		return players_[currPlayer_]->legalMoves()[0];
	}
	else {
		return players_[currPlayer_]->playerHand()[0];
	}
}

// Given a card determines whether the user should be playing it or discarding it, and performs the appropriate action
bool Game::play(const Card& card)
{
	// check for legal moves, if there is the player is playing otherwise discarding
	if(players_[currPlayer_]->hasLegalMoves()) {
		// catches any exceptions and passes it to GUI to say its illegal move
        try {
            players_[currPlayer_]->playCard(card);
        }
        catch (Role::IllegalPlayException &e) {
            return false;
        }
	}
	else {
		players_[currPlayer_]->discardCard(card);
	} 

	// valid move
	return true;
}

// get score by player id
int Game::getScore(int id) const {
    return players_[id]->score();
}

// returns the number of discards for the given player
int Game::getDiscardCount(int id) const {
	return players_[id]->discardCount();
}

// get current player hand
const CardList &Game::getCurrentPlayerHand() const {
    return players_[currPlayer_]->playerHand();
}

// get game table
const CardList &Game::getTable() const {
    return table_;
}

// gets whether the round is over
bool Game::roundOver() const {
	return roundOver_;
}

// gets whether the game is over
bool Game::gameDone() const {
	return gameOver_;
}

// adds the given card to the table
void Game::addToTable(const Card* card) {
	table_.add(card);	
}

// shuffles the deck, and starts a new game
void Game::startNewGame() {
	srand48(seed_);			// shuffle algorithm randomizer
	gameOver_ = false;		// resets flag
	// resets all players score
    for (unsigned int i = 0; i < players_.size(); i++) {
        players_[i]->resetScore();
    }
	newRound();
}

// Starts a new round in the game
void Game::newRound() {
	// resets variables
	currTurn_ = 0;
	roundOver_ = false;

	// clear the table as cards are returned to deck
	table_.clear();

	// (re)populate deck
	game_deck_.repopulate();
        
	// shuffle deck once
	game_deck_.shuffle();

	// deal out cards
    for (unsigned int i = 0; i < players_.size(); i++) {
		players_[i]->newRound(game_deck_.dealPlayerHand());
		if (players_[i]->has7OfSpades()) {
			currPlayer_ = i;
		}
	}
    
	// notifies player with 7 of spades to start
	players_[currPlayer_]->notifyTurn(table_);
}

// makes a hint request to the current player
void Game::makeHintRequest() {
    players_[currPlayer_]->makeHintRequest();
}

// Called to move onto next player/turn
void Game::notify() {
	// increments turn and checks whether round is over
	currTurn_ += 1;
	if(currTurn_ == MAX_TURNS) {
		endRound();
		return;		
	}

	// increments player, and has the player play if round is not over
	currPlayer_ = (currPlayer_ + 1) % players_.size();
	players_[currPlayer_]->notifyTurn(table_);
}

// Called when all players are done playing their cards
void Game::endRound() {
	// signifies is game is over
	bool over = false;

	// update players' score
	// also check to see if any player has score >= 80
	for (unsigned int i = 0; i < players_.size(); i++) {
		// on last player update round is set to be over
		if(i == 3)	{
			// signifies round is over
			roundOver_ = true;
		}

		// informs each player round is over
		players_[i]->endRound();
            
		// mark game as over if score >= 80
		if (players_[i]->score() >= ENDGAME_SCORE) {
			over = true;
		}    
	}

	// checks if game is over, if so ends otherwise another round
	if(over) {
		gameOver();
	}
	else {
		newRound();
	}
}

// if user wants to end game prematurely
void Game::endGame() {
    table_.clear();
    game_deck_.reset();
}

// Called when game is over - determines winner
void Game::gameOver() {
	roundOver_ = false;
	// see who has the minimum score
	int min_score = players_[0]->score();
	vector<int> winners;

	// loop through all players and determine the lowest score
	for (unsigned int i = 0; i < players_.size(); i++) {
		if (players_[i]->score() < min_score) {
			winners.clear();
			winners.push_back(i+1);
			min_score = players_[i]->score();
		}
		else if (players_[i]->score() == min_score) {
			winners.push_back(i+1);
		}
	}
    
    // inform them they won
    for (unsigned int i = 0; i < winners.size(); i++) {
		// sets the game is over when the last player is being set so GUI doesnt get informed multiple times
		if (i == winners.size() - 1)
			gameOver_ = true;

        players_[winners[i]-1]->won(true);
    }

	// clear table
	endGame();
}
