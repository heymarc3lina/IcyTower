#include "WelcomeScreen.h"


int WelcomeScreen::drawMenu(sf::RenderWindow &window) {

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


WelcomeScreen::WelcomeScreen(float width, float height) :Screen(width, height)
{	
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Yellow);
	menu[0].setString("New game");
	menu[0].setPosition(sf::Vector2f(width / 2 - menu[0].getLocalBounds().width / 2, height / (ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Settings");
	menu[1].setPosition(sf::Vector2f(width / 2 - menu[1].getLocalBounds().width / 2, height / (ITEMS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Highscores");
	menu[2].setPosition(sf::Vector2f(width / 2 - menu[2].getLocalBounds().width / 2, height / (ITEMS + 1) * 3));

	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setString("Exit");
	menu[3].setPosition(sf::Vector2f(width / 2 - menu[3].getLocalBounds().width / 2, height / (ITEMS + 1) * 4));

	lose.setFont(font);
	lose.setFillColor(sf::Color::Red);
	giveNameText.setFont(font);
	giveNameText.setFillColor(sf::Color::Cyan);
	
	for (int i = 0; i < 10; i++) {
		player temp{ "-----------" , 0 };
		highscores += temp;
	}

	int licznik = 0;
	//inicjalizacja highscores
	std::ifstream plik("highscores.txt");
	if (plik) {
		plik >> highscores;
		plik.close();
	}
}

WelcomeScreen::~WelcomeScreen(){
	highscores.~ListBestPlayer();
}

bool WelcomeScreen::compare(player p1, player p2) {
	return (p1.score > p2.score);
}

void WelcomeScreen::addHighscore(std::string nam, int scor) {

	std::string name = nam.substr(0, nam.size() - 1);
	player newPlayer{ name, scor };
	highscores += newPlayer;
	highscores.dropLast();

}

bool WelcomeScreen::checkIfGoodEnough(int score) {
	return highscores.goodEnough(score);
}

void WelcomeScreen::loseScreen(sf::RenderWindow &window, int score) {
	bool saveScore = checkIfGoodEnough(score);
	sf::Text nameText;
	sf::String name;
	nameText.setFont(*giveNameText.getFont());
	nameText.setFillColor(sf::Color::Cyan);
	lose.setPosition(sf::Vector2f(window.getSize().x / 2 - window.getSize().x / 5, window.getSize().y / 4 + 30));
	nameText.setPosition(sf::Vector2f(window.getSize().x / 2 - window.getSize().x / 5, window.getSize().y / 3 + 80));
	giveNameText.setPosition(sf::Vector2f(window.getSize().x / 2 - window.getSize().x / 5 , window.getSize().y /3 + 30));
	giveNameText.setString("Nice! Enter Your name: ");
	lose.setString("You lose! Your score: " + std::to_string(score) + "\nClick End to end this game!");

	bool running = true;
	while (window.isOpen() && running && !sf::Keyboard::isKeyPressed(sf::Keyboard::End)) {
		sf::Event event;
		window.clear();
		window.draw(lose);
		if (saveScore) {
			window.draw(giveNameText);
			window.draw(nameText);
		}
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (saveScore) {
				if (event.type == sf::Event::TextEntered && event.text.unicode != 8) {
					name += event.text.unicode;
					nameText.setString(name);
				}
				else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter) {
					nameValid.setVariables(name.substring(0, name.getSize() - 1));
					if (nameValid.check() == 0) {
						giveNameText.setString("Uncorrect form. Try again:\n\n\n*Allow letters and numbers only\nAt least 1 up to 20 signs. ");
						nameText.setString("");
						name = "";
					}
					else {
						addHighscore(name, score);
						highscores.save("highscores.txt");
						running = false;
					}
				}
				else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::BackSpace) {
					if (name.getSize() > 0) {
						name.erase(name.getSize() - 1);
						nameText.setString(name);
					}
				}
			}
		}
		window.display();
	}			
}

int WelcomeScreen::highscoresMenu(sf::RenderWindow &window) {
	return highscores.showHighscores(window, score, font);
}

