/*
 HumanRole.h
 
 Declaration of HumanRole class.
 */

#ifndef _HUMANROLE_H_
#define _HUMANROLE_H_

#include "Role.h"
#include "Player.h"
#include "Card.h"
#include "CardList.h"

class HumanRole : public Role {

	public:
		HumanRole(Player*);                         // constructor
		~HumanRole();                               // destructor

		void play();								// Used to pass control over to the GUI for human to play
};

#endif /* _HUMANROLE_H_ */
