#include "PauseScreen.h"

PauseScreen::PauseScreen(float width, float hight) :Screen(width, hight) {
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Yellow);
	menu[0].setString("Resume");
	menu[0].setPosition(sf::Vector2f(width / 2 - menu[0].getLocalBounds().width / 2, hight / (ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Settings");
	menu[1].setPosition(sf::Vector2f(width / 2 - menu[1].getLocalBounds().width / 2, hight / (ITEMS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("End Game");
	menu[2].setPosition(sf::Vector2f(width / 2 - menu[2].getLocalBounds().width / 2, hight / (ITEMS + 1) * 3));

	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setString("Exit");
	menu[3].setPosition(sf::Vector2f(width / 2 - menu[3].getLocalBounds().width / 2, hight / (ITEMS + 1) * 4));
}

int PauseScreen::drawMenu(sf::RenderWindow &window) {
	while (window.isOpen()) {
		window.clear();
		for (int i = 0; i < ITEMS; i++) {
			window.draw(menu[i]);
		}
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyReleased:
				switch (event.key.code) {
				case sf::Keyboard::Up:
					moveUp();
					break;
				case sf::Keyboard::Down:
					moveDown();
					break;
				case sf::Keyboard::Enter:
					window.clear();
					return selectedIndex;
					break;
				}
			}
		}
		window.display();
	}
	return selectedIndex;

}