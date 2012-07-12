/*
 Subject.h
 
 Declaration of Subject class.
 */

#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include "Observer.h"
#include <vector>

class Game;

class Subject {

public:
	Subject(Game*);
	virtual ~Subject();
	void subscribe(Observer*);
	Game* getGame();
	
	friend class Role;
protected:
	void notify(bool notifyGame = false);
private:
	std::vector<Observer*> observers_;
	Game* gameObserver_;
};

#endif
