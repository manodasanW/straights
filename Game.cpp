#include <cstdlib>

#include "Game.h"

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
	:seed_(0) {
	for (int playerId = 0; playerId < 4; playerId++) {
		players_.push_back(new Player(playerId, true));
	}
}

Game::~Game() {
	helper::cleanVectorMem(players_);
}

void Game::seed(int seed_) {
	seed_ = seed;	
}

void Game:setPlayerType(int id, bool isHuman) {
	players_[id].setRole(isHuman);
}

void Game::playerRageQuit(int id) {
	players_[id].rageQuit();
}

Player* Game::getPlayer(int id) {
	return players_[id];
}

void Game::playCard(int id, Card* card)
{
	players_[id].play(card);
	playCard(card);
}

void Game::playCard(Card* card) {
	table_.add(card);	
}

void Game::startNewGame() {
	srand48(seed);
	newRound();
}

void Game::newRound() {
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

	players_[currPlayer_].notify(table);
}

void Game::notify() {
	currPlayer_ = (currPlayer_ + 1) % players_.size();
	players_[currPlayer_].notify(table);
}

void Game::endRound() {
	// update players' score
	// also check to see if any player has score >= 80
	for (unsigned int i = 0; i < players_.size(); i++) {
		players[i]_->endRound();
            
		// mark game as over if score >= 80
		if (players_[i]->score() >= ENDGAME_SCORE) {
			gameOver();
		}    
	}
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
        players_[winners[i]-1].won(true);
    }

	// clear table
	table_.clear();
}
