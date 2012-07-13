/*
 Subject.h
 
 Declaration of Subject class.
 */

#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include "Observer.h"
#include <vector>

class Game;

// Base class of models which need to notify other observers of changes
class Subject {

public:
	Subject(Game*);								// constructor
	virtual ~Subject();							// destructor
	void subscribe(Observer*);					// adds observer to be one which requires updates of changes
	Game* getGame();							// accessor for the facade
	
	friend class Role;							// friend declaration
protected:
	void notify(bool notifyGame = false);		// used to notify observers and game if bool set of updates
private:
	std::vector<Observer*> observers_;			// stores all the observers
	Game* gameObserver_;						// stores facade sepeartely as it only needs update when changing turns
};

#endif /* _SUBJECT_H_ */
