#include "BonusPlatform.h"

void BonusPlatform::specialAbility(Player & player) {
	if (firstJump < 1) {
		player.setScore(player.getScore() + 1000);
		firstJump++;
	}
}