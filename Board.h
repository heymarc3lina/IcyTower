#pragma once
#ifndef BOARD_H
#define BOARD_H
#include <SFML\Graphics.hpp>

class Board {
	sf::Sprite BoardSprite;
	sf::Texture boardTexture;
		
public:
	
	Board();
	inline sf::Sprite getSprite() {
		return BoardSprite;
	}
	
	void drawBoard(sf::RenderWindow &window);
};
#endif