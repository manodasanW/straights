#include "Game.h"
#include "Subject.h"

// constructor
Subject::Subject(Game* game)
	:gameObserver_(game) {
}

// destructor
Subject::~Subject()
{}

// accessor to fascade
Game* Subject::getGame()
{
	return gameObserver_;
}

// adds observers to list of objects which require to be notified of changes
void Subject::subscribe(Observer* observer) {
	observers_.push_back(observer);
}

// informs observers of changes
void Subject::notify(bool notifyGame) {
	// loops through all observers
	for (unsigned int index = 0; index < observers_.size(); index++) {
		observers_[index]->notify();
	}
	
	// notifies facade if it is also required to be notified - only when new turn
	if(notifyGame && gameObserver_!= NULL)
		gameObserver_->notify();
}
