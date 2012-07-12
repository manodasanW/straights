#include "HumanRole.h"

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
void HumanRole::play(const CardList& table)
{
	triggerPlayerUpdate(false);
}
