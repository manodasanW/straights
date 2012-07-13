#include "GameController.h"

// ctor
GameController::GameController(Game *g) : g_(g), game_in_progress_(false), hint_requested_(false) {
}

// dtor
GameController::~GameController() {
}

// game in progress accessor
bool GameController::gameInProgress() const {
    return game_in_progress_;
}

// hint requested getter
bool GameController::hintRequested() const {
    return hint_requested_;
}

// hint requested setter
void GameController::setHintRequestedFlag(bool flag) {
    hint_requested_ = flag;
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

// play a given card
bool GameController::playCard(const Card &c) {
    return g_->play(c);
}

// ragequit
void GameController::rageQuit() {
    g_->playerRageQuit();
}

