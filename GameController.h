#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_

#include <sstream>
#include <string>

#include "Game.h"

// helper name space
namespace helper {
	// converts number to string
    std::string num2str(int n);
	// converts string to number
    int str2num(std::string s);
}

class GameController {
public:
    GameController(Game *);				// constructor
    ~GameController();					// destructor
    bool gameInProgress() const;		// checks whether game is in progress
    bool hintRequested() const;			// checks whether a hint was requested
    void setHintRequestedFlag(bool);	// sets that a hint was requested
    
    void startGame(int, bool*);			// called when start button clicked
    void endGame();						// called when end button clicked
    bool playCard(const Card &);		// called when card is played
    void rageQuit();					// called when rage quit is clicked
private:
    Game *g_;							// Stores access to facade to call on gui events
    bool game_in_progress_;				// whether game is occuring
    bool hint_requested_;				// whether the user requested a hint
};

#endif /* _GAMECONTROLLER_H_ */

