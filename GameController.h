#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_

class GameController {
public:
    GameController();
    ~GameController();
    bool gameInProgress() const;
    
    void startGame();
    void endGame();
private:
    bool game_in_progress_;
};

#endif
