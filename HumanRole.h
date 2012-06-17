/*
 HumanRole.h
 
 Declaration of HumanRole class.
 */

#ifndef _HUMANROLE_H_
#define _HUMANROLE_H_

#include "Role.h"
#include "Player.h"
#include "Card.h"
#include <vector>

class HumanRole : public Role {

	public:
		HumanRole(Player*);
		~HumanRole();

		const Command play(const std::vector<const Card*>&);
};

namespace CardSet {

	void printUnFormatted(const std::vector<const Card*>);
	void printFormatted(const std::vector<const Card*>);

}

#endif /* _HUMANROLE_H_ */
