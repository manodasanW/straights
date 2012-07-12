/*
 Subject.h
 
 Declaration of Subject class.
 */

#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include "Observer.h"
#include "Game.h"

class Subject {

public:
	Subject(Game*);
	~Subject();
	void subscribe(Observer&);
protected:
	void notify(bool notifyGame = false);
	Game* getGame();
private:
	vector<Observer&> observers_;
	Game* gameObserver_;
};

#endif
