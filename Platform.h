#pragma once
#ifndef PLATFORM_H
#define PLATFORM_H
#include <SFML\Graphics.hpp>
#include <string>
#include "Player.h"



class Platform {
protected:
	float x, y;
	int hight, width;
	sf::Sprite platformSprite;
	sf::Texture platformTexture;
	int bounceSpeed;
	bool draw;
	

public:
	Platform(int x= 250 ,int y=700, int bounceSpeed = -8, std::string textureName = "platform.png", int w=64, int h=16,bool draw = 1);
	inline int getBounceSpeed() {
		return bounceSpeed;
	}
	inline float getX() {
		return x;
	}

	inline float getY() {
		return y;
	}
	inline int getWidth() {
		return width;
	}

	inline int getHight() {
		return hight;
	}
	inline bool ifDraw() {
		return draw;
	}

	void setXY(float x, float y);
	void setY(float y);
	void drawPlatform(sf::RenderWindow &win);
	virtual void specialAbility(Player & player) = 0;
	virtual ~Platform() = default;
	
};


#endif