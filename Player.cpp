/*
 Player.cpp
 
 Definitions for Player.h.
 */

#include "Player.h"

// Player constructor
Player::Player(int id, bool is_human) : id_(id), score_(0) {
}

// Player destructor
Player::~Player() {
}

// start a new round by giving the player a new set of cards
void newRound(vector<const Card *> new_cards) {
    hand_ = new_cards;
}

// tells Player object to take the cards in its discard pile
// and add them for points
void Player::updateScore() {
    for (int i = 0; i < discards_.size(); i++) {
        // stuff
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
