#include "GameController.h"
#include <iostream>

using namespace std;

// ctor
GameController::GameController() : game_in_progress_(false) {
}

// dtor
GameController::~GameController() {
}

// game in progress accessor
bool GameController::gameInProgress() const {
    return game_in_progress_;
}

// starts a new game
void GameController::startGame() {
    cout << "Starting game..." << endl;
    game_in_progress_ = true;
}

// ends current game
void GameController::endGame() {
    cout << "Ending game..." << endl;
    game_in_progress_ = false;
}
