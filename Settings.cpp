#include "Settings.h"

void Settings::drawMenu(sf::RenderWindow &window, Audio & audio, bool isGame, bool & level) {
	
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
					moveDown(ITEMS);
					break;
				case sf::Keyboard::Right:
					rightKeyManage(selectedIndex,  audio,  isGame, level);
					break;
					window.clear();
				case sf::Keyboard::Left:
					leftKeyManage(selectedIndex, audio, isGame, level);
					break;
				case sf::Keyboard::Escape:
					return;
				}
			}
		}
		window.display();
	}
}

void Settings::leftKeyManage(int selectedIndex, Audio & audio, bool isGame, bool & level) {
	if (selectedIndex == 0)
	{
		audio.turnDownTheVolume();
		volume = ceil(audio.getVolume());
		menu[0].setString("Volume    " + std::to_string((int)volume));
	}
	else if (selectedIndex == 1)
	{
		audio.setIsMusicPlaying(0);
		menu[1].setString("Music    OFF");
		audio.stopMusic();
	}
	else if (selectedIndex == 2) {
		if (!isGame) {
			menu[2].setString("Level    EASY");
			level = 0;
		}
	}
}

void Settings::rightKeyManage(int selectedIndex, Audio & audio, bool isGame, bool & level) {
	if (selectedIndex == 0) {
		audio.turnUpTheVolume();
		volume = ceil(audio.getVolume());
		menu[0].setString("Volume    " + std::to_string((int)volume));
	}
	else if (selectedIndex == 1)
	{
		audio.setIsMusicPlaying(1);
		menu[1].setString("Music    ON");
		if (isGame) {
			audio.playMusic();
		}
	}
	else if (selectedIndex == 2) {
		if (!isGame) {
			menu[2].setString("Level    HARD");
			level = 1;
		}
	}
}


Settings::Settings(float volume, float width, float height) :Screen(width, height)
{
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Yellow);
	menu[0].setString("Volume    " + std::to_string((int)volume));
	menu[0].setPosition(sf::Vector2f(width / 2 - menu[0].getLocalBounds().width / 2, height / (ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Music    ON");
	menu[1].setPosition(sf::Vector2f(width / 2 - menu[1].getLocalBounds().width / 2, height / (ITEMS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Level    EASY");
	menu[2].setPosition(sf::Vector2f(width / 2 - menu[2].getLocalBounds().width / 2, height / (ITEMS + 1) * 3));
}