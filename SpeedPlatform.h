#pragma once
#ifndef SPEEDPLATFORM_H
#define SPEEDPLATFORM_H
#include "Platform.h"

class SpeedPlatform : public Platform {

public:
	SpeedPlatform(int x = 0, int y = 0, int bounceSpeed=-16, std::string textureName = "platformSpeed.png", int w = 64, int h = 16) :Platform(x, y,bounceSpeed, textureName, w, h) {};
	void specialAbility(Player &player);
};

#endif