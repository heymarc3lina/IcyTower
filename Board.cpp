#include "Board.h"

Board::Board() {
		
	try {
		if (!boardTexture.loadFromFile("tlo.png")) {
			throw 1;
		}
		BoardSprite.setTexture(boardTexture);
	}
	catch (int) {
		exit(1);
	}
}

void Board::drawBoard(sf::RenderWindow &window) {
	window.draw(BoardSprite);
	
}