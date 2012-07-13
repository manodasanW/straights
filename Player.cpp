/*
 Player.cpp
 
 Definitions for Player
 */

#include "Card.h"
#include "AIRole.h"
#include "HumanRole.h"

using namespace std;

// Player constructor
Player::Player(int id, bool is_human, Game* game) 
	: Subject(game), role_(NULL), id_(id), score_(0), won_(false) {
	setRole(is_human);
}

// Player destructor
Player::~Player() {
    delete role_;
}

void Player::setRole(bool is_human) {
	delete role_;
	
    if (is_human) {
        role_ = new HumanRole(this);
    }
    else {
        role_ = new AIRole(this);
    }
}

// switches current player with a role of AI
void Player::rageQuit() {
	// replaces human role with ai role
	setRole(false);
}

// start a new round by giving the player a new set of cards
void Player::newRound(const CardList &new_cards) {
    hand_ = new_cards;
	discards_.clear();
	notify();
}

// handle the end of round for the player
void Player::endRound() {
    updateScore();
	notify();
}

// find out if the player possesses the 7 of spades
bool Player::has7OfSpades() const {
    return hand_.find(Card(SPADE, SEVEN)) != -1;
}

// tells Player object to take the cards in its discard pile
// and add them for points
void Player::updateScore() {
    for (int i = 0; i < discards_.size(); i++) {
        score_ += ((int)discards_[i]->getRank()) + 1;
    }
}

void Player::notifyTurn(const CardList& table) {
	role_->play(table);
}

void Player::playCard(const Card& card)
{
	role_->playCard(card);
}

void Player::discardCard(const Card& card)
{
	role_->discardCard(card);
}

// id get accessor
int Player::id() const {
    return id_;
}

// score get accessor
int Player::score() const {
    return score_;
}

// won mutator
void Player::won(bool newVal) {
	won_ = newVal;
}
// won accessor
bool Player::won() const {
	return won_;
}
