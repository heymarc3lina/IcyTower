#pragma once
#ifndef GAME_H
#define GAME_H
#include "Board.h"
#include "Player.h"
#include "Settings.h"
#include "Platform.h"
#include "WelcomeScreen.h"
#include "DefaultPlatform.h"
#include "SpeedPlatform.h"
#include "PauseScreen.h"
#include "FirePlatform.h"
#include "BrokenPlatform.h"
#include "BonusPlatform.h"
#include <random>
#include <iostream>

class Game{
	Player player;
	Board board;
	WelcomeScreen screen;
	sf::Event event;
	sf::RenderWindow window;
	int amountOfPlatform;
	Platform * platformTable[15];
	Audio audio;
	Settings settings;
	PauseScreen pauseScreen;
	bool isRunning;
	bool isLevelHard;
public:
	Game();
	~Game();
	//metoda zawieraj¹ca pêtle gty
	void gameLoop();
	//metoda tworz¹ca startowe platfromy
	void createStartPlatforms();
	//metoda s³u¿¹ca do losowania randomowych licz z podanego przedzialu
	int getRandomNumber(int number1, int number2);
	//metoda powoduj¹ca efekt przesuwania ekranu
	void getDownPlayerAndPlatform();
	//metoda zmieniaj¹ca pozycje platform, które wysz³y poza ekran
	void changePositionOfDisapearedPlatform();
	//metoda zwracaj¹ca odleg³osc euklidesow¹ na podstawie podanych wspolrzednych 
	//podane wspolrzedne to xi y jedenj platformy oraz wylosowane nowe
	float getEuclideanDistance(float x1, float x2, float y1, float y2);
	//metoda usuwajaca wszystkie platfromy z tablicy
	void deletePlatforms();
	//metoda tworzaca now¹ platformê na podanej pozycji w tablicy
	void setRandomPlatform(int position);
	//metoda sluzaca do zmiany typu platformy. Usuwa stara, a w jej miejsce tworzy nowa
	//wspolrzzedne nowej to x =0 oraz y taki jaki miala platforma przed jej usunieciem
	void changePlatformType(int position);
	//metoda odbijajaca graza od platformy wtedy kiedy on spada
	//dodatkowo metoda ta wywoluje metode ze specjalna umiejetnoscia kazdej z platform
	void bouncePlatform();
	//metoda sprawdzajaca czy gracz udezyl w platforme
	bool hitThePlatform(int index);
	//metoda zwracajaca dystans do najblizszej platformy od platformy na podanej pozycji w tablicy
	float distanceToNearestPlatform(int position,int newX,int amount);
	//metoda sluzaca do obslugi pauzy w grze
	void pauseManage();
};

#endif