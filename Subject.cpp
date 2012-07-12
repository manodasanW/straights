#include "Game.h"
#include "Subject.h"

Subject::Subject(Game* game)
	:gameObserver_(game) {
}

Subject::~Subject()
{}

Game* Subject::getGame()
{
	return gameObserver_;
}

void Subject::subscribe(Observer* observer) {
	observers_.push_back(observer);
}

void Subject::notify(bool notifyGame) {
	for (unsigned int index = 0; index < observers_.size(); index++) {
		observers_[index]->notify();
	}
	
	if(notifyGame && gameObserver_!= NULL)
		gameObserver_->notify();
}
