#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H
#include "Screen.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include "ListBestPlayer.h"
#include "Validator.h"
#define ITEMS 4

class WelcomeScreen : public Screen
{
	sf::String filename;
	sf::Text score[10];
	sf::Text lose;
	sf::Text giveNameText;
	ListBestPlayer highscores;
	Validator nameValid;

public:
	int highscoresMenu(sf::RenderWindow &window);
	static bool compare(player p1, player p2);
	void addHighscore(std::string nam, int scor);
	bool checkIfGoodEnough(int scor);
	int drawMenu(sf::RenderWindow &window);
	WelcomeScreen(float width = 1000 , float height = 1000);
	~WelcomeScreen();
	void loseScreen(sf::RenderWindow &window, int score);
};

#endif