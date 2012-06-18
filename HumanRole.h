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
		HumanRole(Player*);
		~HumanRole();

		const Command play(const CardList&);
};

#endif /* _HUMANROLE_H_ */
