#ifndef SCREEN_H
#define SCREEN_H
#include <SFML\Graphics.hpp>
#define ITEMS 4

class Screen {
protected:
	int selectedIndex;
	sf::Font font;
	sf::Text menu[ITEMS];
public:
	Screen(float width = 1000, float height = 1000);
	void moveUp();
	void moveDown(int item = ITEMS);
};


#endif