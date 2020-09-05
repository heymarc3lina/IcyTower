#include "BrokenPlatform.h"
void BrokenPlatform:: specialAbility(Player & player) {
	player.setSpeed(bounceSpeed);
};

void BrokenPlatform::disapear() {
	draw = 0;
}

