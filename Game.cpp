#include <vector>
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
	:seed(0)
{
	for (int playerId = 0; playerId < 4; playerId++) {
		players.push_back(new Player(playerId, true));
	}
}

Game::~Game()
{
	helper::cleanVectorMem(players);
}

Game::seed(int newSeed)
{
	seed = newSeed;	
}

Player* Game::getPlayer(int id)
{
	return players[id];
}

void Game::playCard(Card* card)
{
	table.push_back(card);	
}

void Game::startNewGame()
{
	srand48(seed);
	newRound();
}

void Game::newRound()
{
	// clear the table as cards are returned to deck
	table.clear();

	// (re)populate deck
	game_deck.repopulate();
        
	// shuffle deck once
	game_deck.shuffle();

	// deal out cards
    for (unsigned int i = 0; i < players.size(); i++) {
		players[i]->newRound(game_deck.dealPlayerHand());
		if (players[i]->has7OfSpades()) {
			currPlayer = i;
		}
	}

}

void Game::endRound()
{
	// update players' score
	// also check to see if any player has score >= 80
	for (unsigned int i = 0; i < players.size(); i++) {
		players[i]->endRound();
            
		// mark game as over if score >= 80
		if (players[i]->score() >= ENDGAME_SCORE) {
			gameOver();
		}    
	}
}

void Game::gameOver()
{
	// see who has the minimum score
	int min_score = players[0]->score();
	vector<int> winners;
	for (unsigned int i = 0; i < players.size(); i++) {
		if (players[i]->score() < min_score) {
			winners.clear();
			winners.push_back(i+1);
			min_score = players[i]->score();
		}
		else if (players[i]->score() == min_score) {
			winners.push_back(i+1);
		}
	}
    
    // inform them they won
    for (unsigned int i = 0; i < winners.size(); i++) {
        players[winners[i]-1].won();
    }

	// clear table
	table.clear();
}
