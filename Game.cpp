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
	:MAX_TURNS(52), ENDGAME_SCORE(80), seed_(0), currPlayer_(0), currTurn_(0)   {
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

void Game::playerRageQuit(int id) {
	players_[id]->rageQuit();
	players_[id]->notifyTurn(table_);
	
}

Player* Game::getPlayer(int id) const {
	return players_[id];
}

void Game::playCard(int id, const Card& card)
{
	players_[id]->playCard(card);
}

void Game::discardCard(int id, const Card& card)
{
	players_[id]->discardCard(card);
}

void Game::playCard(const Card* card) {
	table_.add(card);	
}

void Game::startNewGame() {
	srand48(seed_);
	newRound();
}

void Game::newRound() {
	currTurn_ = 0;
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

void Game::notify() {
	currTurn_ += 1;
	if(currTurn_ == MAX_TURNS) {
		endRound();
		return;		
	}

	currPlayer_ = (currPlayer_ + 1) % players_.size();
	players_[currPlayer_]->notifyTurn(table_);
}

void Game::endRound() {
	// update players' score
	// also check to see if any player has score >= 80
	for (unsigned int i = 0; i < players_.size(); i++) {
		players_[i]->endRound();
            
		// mark game as over if score >= 80
		if (players_[i]->score() >= ENDGAME_SCORE) {
			gameOver();
			return;
		}    
	}
	newRound();
}

// if user wants to end game prematurely
void Game::endGame() {
    table_.clear();
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
	table_.clear();
}
