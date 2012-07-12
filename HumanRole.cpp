#include "HumanRole.h"
#include <iostream>

using namespace std;

/**
	Constructor/Destructor
**/
HumanRole::HumanRole(Player* player)
		:Role(player), inputIncomplete(false) {
}

HumanRole::~HumanRole()
{
}
