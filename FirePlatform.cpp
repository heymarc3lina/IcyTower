#include "FirePlatform.h"

void FirePlatform::specialAbility(Player & player) {
	player.setLife(player.getLife()-1);
	player.getHeartList()->deleteElement();
}