#pragma once
#ifndef DEFAULTPLATFORM_H
#define DEFAULTPLATFORM_H
#include "Platform.h"



class DefaultPlatform : public Platform {
	
public:
	DefaultPlatform(int x = 0, int y = 0, int bounceSpeed= -8, std::string textureName = "platform.png", int w = 64, int h = 16) :Platform(x, y,  bounceSpeed,textureName, w, h) {};
	void specialAbility(Player &player);
};

#endif