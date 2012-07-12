#include "GameController.h"
#include <iostream>

using namespace std;

// ctor
GameController::GameController() {
}

// dtor
GameController::~GameController() {
}

// starts a new game
void GameController::startGame() {
    cout << "Starting game..." << endl;
}

// ends current game
void GameController::endGame() {
    cout << "Ending game..." << endl;
}
