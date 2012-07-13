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

Game::Game()
	:MAX_TURNS(52), ENDGAME_SCORE(80), seed_(0), currPlayer_(0), currTurn_(0), roundOver_(true)   {
	for (int playerId = 0; playerId < 4; playerId++) {
		players_.push_back(new Player(playerId, true, this));
	}
}

Game::~Game() {
	helper::cleanVectorMem(players_);
}

void Game::seed(int seed) {
	seed_ = seed;	
}

void Game::setPlayerType(int id, bool isHuman) {
	players_[id]->setRole(isHuman);
}

void Game::subscribeView(Observer* observer) {
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

// Given a card determines whether the user should be playing it or discarding it, and performs the appropriate action
bool Game::play(const Card& card)
{
	// check for legal moves, if there is the player is playing otherwise discarding
	if(players_[currPlayer_]->hasLegalMoves()) {
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

// adds the given card to the table
void Game::addToTable(const Card* card) {
	table_.add(card);	
}

// shuffles the deck, and starts a new game
void Game::startNewGame() {
	srand48(seed_);			// shuffle algorithm randomizer
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
    
	players_[currPlayer_]->notifyTurn(table_);
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
	// signifies round is over
	roundOver_ = true;
	bool over = false;

	// update players' score
	// also check to see if any player has score >= 80
	for (unsigned int i = 0; i < players_.size(); i++) {
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

void Game::gameOver() {
	// see who has the minimum score
	int min_score = players_[0]->score();
	vector<int> winners;
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
        players_[winners[i]-1]->won(true);
    }

	// clear table
	endGame();
}
