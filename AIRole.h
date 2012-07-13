/*
 AIRole.h
 
 Declaration of AIRole class.
 */

#ifndef _AIROLE_H_
#define _AIROLE_H_

#include "Role.h"
#include "Player.h"
#include "Card.h"
#include "CardList.h"

class AIRole : public Role {

	public:
		AIRole(Player*);                        // constructor
		~AIRole();                              // destructor

		void play();							// gets AI move given the table
	private:
		int getSpecialIndex(const CardList&, bool); // index of highest or lowest card depending on bool
};

#endif /* _AIROLE_H_ */

