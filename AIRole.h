/*
 AIRole.h
 
 Declaration of AIRole class.
 */

#ifndef _AIROLE_H_
#define _AIROLE_H_

#include "Role.h"
#include "Command.h"
#include <vector>
#include "Player.h"
#include "Card.h"

class AIRole : public Role {

	public:
		AIRole(Player*);
		~AIRole();

		const Command play(const std::vector<const Card*>&);	
};

#endif /* _AIROLE_H_ */

