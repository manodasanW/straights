#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cassert>

#include "Command.h"
#include "Card.h"
#include "CardOps.h"
#include "Deck.h"
#include "Player.h"

using namespace std;

namespace helper {
	// Converts the given string to a int
	int strToNum(string strNum)
	{
		stringstream streamNum (strNum);
		int num;
		if (!(streamNum >> num)) {
			num = 0;
		}

		return num;
	}
}


int main(int argc, char * argv[])
{
    const int MAX_TURNS = 13;
    
	// check for if optional parameter is given
	if (argc > 1) {
		// initalize pseudocode random generator
		string strSeed = argv[1];
		int seed = helper::strToNum(strSeed);
		
		srand48(seed);
	}
	
    // add players
    vector<Player> players;
    
    for (int i = 1; i <= 4; i++) {
        cout << "Is player " << i << " a human(h) or a computer(c)?" << endl;
        char input;
		cout << ">";
        cin >> input;
        assert(input == 'c' || input == 'C' || input == 'H' || input == 'h');
        players.push_back(Player(i, input == 'h' || input == 'H'));
    }
    
    // round loop
    Deck game_deck;
    bool game_over = false;
    while (!game_over) {
        // (re)populate deck
        game_deck.repopulate();
        
        // shuffle deck once
        game_deck.shuffle();
        
        // deal out cards
        int curr_player = 1;
        for (unsigned int i = 0; i < players.size(); i++) {
            players[i].newRound(game_deck.dealPlayerHand());
            if (players[i].has7OfSpades()) {
                curr_player = i;
            }
        }
        
        // start game loop
        cout << "A new round begins. It's player " << curr_player << "'s turn to play." << endl;
        
        CardList table;             // played cards
        // a round lasts a fixed number of turns since a player can only
        // play or discard exactly one card each turn
        for (int i = 0; i < MAX_TURNS; i++) {
            // get action from player
            Command cmd = players[curr_player].play(table);
            
            if (cmd.type == PLAY) {
                // play the card
                table.push_back(&cmd.card);
            }
            
            else if (cmd.type == DECK) {
                // print out deck
                cout << game_deck << endl;
            }
            
            else if (cmd.type == QUIT) {
                // exit game immediately
                return 0;
            }
            
            // other commands are handled by the player objects
            
            // next player's turn
            curr_player++;
            curr_player %= players.size();
        }
        
        // update players' score
        // also check to see if any player has score >= 80
        for (unsigned int i = 0; i < players.size(); i++) {
            players[i].endRound();
            
            // mark game as over if score >= 80
            if (players[i].score() >= 80) {
                game_over = true;
            }
            
        }
    }
    
    // see who has the minimum score
    int min_score = players[0].score();
    vector<int> winners;
    for (unsigned int i = 0; i < players.size(); i++) {
        if (players[i].score() < min_score) {
            winners.clear();
            winners.push_back(i);
        }
        else if (players[i].score() == min_score) {
            winners.push_back(i);
        }
    }
    
    // congratulate them
    for (unsigned int i = 0; i < winners.size(); i++) {
        cout << "Player " << i << " wins!" << endl;
    }
    
    return 0;
}
