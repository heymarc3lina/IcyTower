#pragma once
#ifndef BONUSPLATFORM_H
#define BONUSPLATFORM_H
#include "Platform.h"

class BonusPlatform : public Platform {
	int firstJump;
public:
	BonusPlatform(int x = 0, int y = 0, int bounceSpeed = -8, std::string textureName = "PlatformBonus.png", int w = 66, int h = 14, bool draw = 1) :firstJump(0),Platform(x, y,bounceSpeed, textureName, w, h) {};
	void specialAbility(Player & player);
};

#endif
