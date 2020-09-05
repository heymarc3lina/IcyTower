#pragma once
#ifndef SETTINGS_H
#define SETTINGS_H
#include "Screen.h"
#include "Audio.h"
#define ITEMS 3

class Settings :public Screen {
	float volume;
public:
	void drawMenu(sf::RenderWindow &window, Audio & audio, bool isGame, bool & level);
	Settings(float volume = 100, float width = 1000, float height = 1000);
	//metoda obslugujaca klikniecie prawej strzalki
	void rightKeyManage(int selectedIndex, Audio & audio, bool isGame, bool & level);
	//metoda obslugujaca klikniecie lewej strzalki
	void leftKeyManage(int selectedIndex, Audio & audio, bool isGame, bool & level);
};
#endif