/*
 AIRole.h
 
 Declaration of AIRole class.
 */

#ifndef _AIROLE_H_
#define _AIROLE_H_

#include "Role.h"
#include "Command.h"
#include "Player.h"
#include "Card.h"
#include "CardOps.h"

class AIRole : public Role {

	public:
		AIRole(Player*);
		~AIRole();

		const Command play(const CardList&);	
};

#endif /* _AIROLE_H_ */

