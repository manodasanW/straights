/*
 Player.cpp
 
 Definitions for Player.h.
 */

#include "Card.h"
#include "AIRole.h"
#include "HumanRole.h"

#include <iostream>

using namespace std;

// Player constructor
Player::Player(int id, bool is_human) : id_(id), score_(0) {
    if (is_human) {
        role_ = new HumanRole(this);
    }
    else {
        role_ = new AIRole(this);
    }
}

// Player destructor
Player::~Player() {
    delete role_;
}

// switches current player with a role of AI
void Player::rageQuit() {
		// replaces human role with ai role
        delete role_;
        role_ = new AIRole(this);
		role_->play(table);					// makes the ai play again as rage quit isn't a game command
}

// start a new round by giving the player a new set of cards
void Player::newRound(const CardList &new_cards) {
    hand_ = new_cards;
	discards_.clear();
}

// handle the end of round for the player
void Player::endRound() {
    int old_score = score_;
    updateScore();
    // print player info
    cout << "Player " << id_ << "'s discards: ";
    CardOperations::printUnFormatted(discards_);
    cout << "Player " << id_ << "'s score: " << old_score << " + ";
    cout << (score_ - old_score) << " = " << score_ << endl;
}

// find out if the player possesses the 7 of spades
bool Player::has7OfSpades() const {
    return CardOperations::find(hand_, Card(SPADE, SEVEN)) != -1;
}

// tells Player object to take the cards in its discard pile
// and add them for points
void Player::updateScore() {
    for (unsigned int i = 0; i < discards_.size(); i++) {
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
