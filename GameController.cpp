#include "GameController.h"

// ctor
GameController::GameController(Game *g) : g_(g), game_in_progress_(false) {
}

// dtor
GameController::~GameController() {
}

// game in progress accessor
bool GameController::gameInProgress() const {
    return game_in_progress_;
}

// starts a new game
void GameController::startGame(int gseed, bool *playerTypes) {
    g_->seed(gseed);
    for (int i = 0; i < 4; i++) {
        g_->setPlayerType(i, !playerTypes[i]);
    }
    g_->startNewGame();
    game_in_progress_ = true;
}

// ends current game
void GameController::endGame() {
    g_->endGame();
    game_in_progress_ = false;
}
