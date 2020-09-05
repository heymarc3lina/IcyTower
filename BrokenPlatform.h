#pragma once
#ifndef BROKENPLATFORM_H
#define BROKENPLATFORM_H
#include "Platform.h"

class BrokenPlatform : public Platform {
	
public:
	BrokenPlatform(int x = 0, int y = 0, int bounceSpeed = -5, std::string textureName = "PlatformBroken.png", int w = 60, int h = 14, bool draw = 1) : Platform(x, y,  bounceSpeed,textureName, w, h, draw) {} ;
	void specialAbility(Player & player);
	void disapear();
	
};

#endif
