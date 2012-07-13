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

// passes control to the GUI
void HumanRole::play()
{
	// notifies gui only to update
	triggerPlayerUpdate(false);
}
