#include "Heart.h"

Heart::Heart(float x , float y, int hight , int width ) {
	this->x = x;
	this->y = y;
	this->hight = hight;
	this->width = width;
	try {
		if (!HeartTexture.loadFromFile("heart.png")) {
			throw 1;
		}
		HeartSprite.setTexture(HeartTexture, true);
		HeartSprite.setPosition(x, y);
	}
	catch (int) {
		exit(1);
	}
}

void Heart::drawHeart(sf::RenderWindow &window) {
	window.draw(HeartSprite);
}