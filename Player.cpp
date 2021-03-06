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

// sets whether the current player is a human or ai
void Player::setRole(bool is_human) {
	// destructs the previous role if any
	delete role_;
	
	// constructs new role based on bool
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

	// removes all the cards which were discarded
	discards_.clear();
}

// handle the end of round for the player
void Player::endRound() {
	// updates players score
    updateScore();
	
	// notifies gui round is over
	notify();
}

// handles the end of the game
void Player::endGame() {
	// clears hand and notifies gui of update
	hand_.clear();
	notify();
}

// find out if the player possesses the 7 of spades
bool Player::has7OfSpades() const {
	return hand_.find(Card(SPADE, SEVEN)) != -1;
}

// tells Player object to take the cards in its discard pile
// and add them for points
void Player::updateScore() {
	// sums up the discards
	for (int i = 0; i < discards_.size(); i++) {
		score_ += ((int)discards_[i]->getRank()) + 1;
	}
}

// called when it is the players turn to play
void Player::notifyTurn(const CardList& table) {
	// updates legal moves, and depending on if AI or Human either passes control to GUI or plays
	updateLegalMoves(table);
	role_->play();
}

// Plays the given card, called from GUI
void Player::playCard(const Card& card)
{
	role_->playCard(card);
}

// Discards the given card, called from GUI
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

// returns the number of discards - accessor
int Player::discardCount() const {
	return discards_.size();
}

// hand get accessor
const CardList &Player::playerHand() const {
    return hand_;
}

// updates the cards which are legally playable
void Player::updateLegalMoves(const CardList& table) {
	legalMoves_ = GameLogic::legalMoves(table, hand_);		// calls helper function to obtain legal cards
}

// accessor to the player's legal moves
const CardList& Player::legalMoves() const {
	return legalMoves_;
}

// checks if there are any cards to play
bool Player::hasLegalMoves() const {
	return legalMoves_.size() != 0;
}

// hint request
void Player::makeHintRequest() {
    notify();
}

// score reset
void Player::resetScore() {
    score_ = 0;
	won_ = false;
}

// won mutator
void Player::won(bool newVal) {
	won_ = newVal;

	// notifies of change in winner status
	notify();
}

// won accessor
bool Player::won() const {
	return won_;
}
