#include "Screen.h"

Screen::Screen(float width, float hight) {
	try {
		if (!font.loadFromFile("Antaro.ttf")) {
			throw 1;
		}
	}
	catch (int i) {
		exit(1);
	}
	selectedIndex = 0;
}

void Screen::moveUp() {
	if (selectedIndex > 0) {
		menu[selectedIndex].setFillColor(sf::Color::White);
		selectedIndex--;
		menu[selectedIndex].setFillColor(sf::Color::Yellow);
	}
}

void Screen::moveDown(int item) {
	if (selectedIndex < item - 1) {
		menu[selectedIndex].setFillColor(sf::Color::White);
		selectedIndex++;
		menu[selectedIndex].setFillColor(sf::Color::Yellow);
	}
}