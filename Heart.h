#ifndef HEART_H
#define HEART_H
#include <SFML\Graphics.hpp>
class Heart {
	float x, y;
	int hight, width;
	sf::Sprite HeartSprite;
	sf::Texture HeartTexture;
public:
	inline int getWidth() {
		return width;
	}
	Heart(float x = 950, float y = 0, int hight = 50, int width = 45);
	void drawHeart(sf::RenderWindow &window);

};


#endif