#pragma once
#ifndef FIREPLATFORM_H
#define FIREPLATFORM_H
#include "Platform.h"

class FirePlatform : public Platform {

public:
	FirePlatform(int x=0, int y=0, int bounceSpeed = -8, std::string textureName = "PlatformFire.png", int w = 64, int h= 14) :Platform(x, y,  bounceSpeed,textureName, w, h) {};
	void specialAbility(Player & player);
};

#endif
