#pragma once
#ifndef PAUSESCREEN_H
#define PAUSESCREEN_H
#include "Screen.h"
#define ITEMS 4

class PauseScreen :public Screen {
public:
	PauseScreen(float width = 1000, float height = 1000);
	int drawMenu(sf::RenderWindow &window);
};

#endif