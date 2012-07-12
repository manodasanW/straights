#include "HumanRole.h"
#include <iostream>

using namespace std;

/**
	Constructor/Destructor
**/
HumanRole::HumanRole(Player* player)
		:Role(player) {
}

HumanRole::~HumanRole()
{
}

// does nothing as GUI takes care of playing
Card* HumanRole::play(const CardList& table)
{
	triggerPlayerUpdate(false);
	return NULL;
}

