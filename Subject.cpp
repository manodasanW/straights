#include "Subject.h"

Subject::Subject(Game* game)
	:gameObserver_(game) {
}

Subject::~Subject()
{}

Game* Subject::getGame()
{
	return game;
}

void Subject::subscribe(Observer& observer) {
	observers.push_back(observer);
}

void Subject::notify(bool notifyGame) {
	for (int index = 0; index < observers.size(); index++) {
		observers[index].notify();
	}
	
	if(notifyGame && game!= NULL)
		game.notify();
}
