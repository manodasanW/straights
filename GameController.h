#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_

#include "Game.h"

class GameController {
public:
    GameController(Game *);
    ~GameController();
    bool gameInProgress() const;
    
    void startGame(int, bool*);
    void endGame();
    bool playCard(const Card &);
    void rageQuit();
private:
    Game *g_;
    bool game_in_progress_;
};

#endif
