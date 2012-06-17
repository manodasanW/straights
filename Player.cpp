/*
 Player.cpp
 
 Definitions for Player.h.
 */

#include "Card.h"
#include "Player.h"
#include "AIRole.h"
#include "HumanRole.h"

#include <iostream>

using namespace std;

// Player constructor
Player::Player(int id, bool is_human) : id_(id), score_(0) {
    if (is_human) {
        role_ = new HumanRole();
    }
    else {
        role_ = new AIRole();
    }
}

// Player destructor
Player::~Player() {
    delete role_;
}

// handle played card
const Command Player::play() {
    Command c = role_->play();
    // handle ragequit on its own
    if (c.type == RAGEQUIT) {
        cout << "Player " << id_ << " ragequits. A computer will now take over." << endl;
        delete role_;
        role_ = new AIRole();
    }
    // in any case, pass results to main
    return c;
}

// start a new round by giving the player a new set of cards
void Player::newRound(vector<const Card *> new_cards) {
    hand_ = new_cards;
}

// tells Player object to take the cards in its discard pile
// and add them for points
void Player::updateScore() {
    for (int i = 0; i < discards_.size(); i++) {
        score_ += ((int)discards_[i]->getRank()) + 1;
    }
}

// id get accessor
int Player::id() const {
    return id_;
}

// score get accessor
int Player::score() const {
    return score_;
}
