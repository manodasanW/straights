/*
 HumanRole.h
 
 Declaration of HumanRole class.
 */

#ifndef _HUMANROLE_H_
#define _HUMANROLE_H_

#include "Role.h"
#include "Player.h"
#include "Card.h"
#include "CardOps.h"

class HumanRole : public Role {

	public:
		HumanRole(Player*);                         // constructor
		~HumanRole();                               // destructor

		const Command play(const CardList&);        // gets human move given the table
};

#endif /* _HUMANROLE_H_ */
