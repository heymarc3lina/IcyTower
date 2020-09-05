#include "Platform.h"

Platform::Platform(int x, int y,int bounceSpeed, std::string textureName, int w, int h, bool draw) {
	this->x = x;
	this->y = y;
	width = w;
	hight = h;
	this->bounceSpeed = bounceSpeed;
	this->draw = draw;
	
	try {
		if (!platformTexture.loadFromFile(textureName)) {
			throw 1;
		}
		//platformSprite = sf::Sprite(platformTexture);
		platformSprite.setTexture(platformTexture, true);
		platformSprite.setPosition(x, y);
	}
	catch (int) {
		exit(1);
	}
}

void Platform::setXY(float x, float y) {
	this->x = x;
	this->y = y;

}

void Platform::setY(float y) {
	this->y = y;
}


void Platform::drawPlatform(sf::RenderWindow &win) {
	platformSprite.setPosition(x, y);
	win.draw(platformSprite);
	
}

