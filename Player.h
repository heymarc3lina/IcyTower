#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <SFML\Graphics.hpp>
#include <iostream>
#include <iomanip>
#include "HeartList.h"

class Player {
	float x, y;
	int hight, width;
	sf::Sprite PlayerSprite;
	sf::Texture PlayerTexture;
	int score; 
	HeartList heartList;
	float speedY, bounceSpeed;
	float  accelerationY;
	int life;
	sf::Font font;
	sf::Text scoreText;

public:
	Player(float x=200, float y=200, int hight=80, int weight=80);
	inline void setSpeed(float speedY) {
		this->speedY = speedY;
	}
	inline void setLife(int life) {
		this->life = life;
	}
	inline void setPosition(float x, float y) {
		this->x = x;
		this->y = y;
	}
	inline void setScore(int score) {
		this->score = score;
	}
	inline int getX() {
		return x;
	}
	inline int getScore() {
		return score;
	}
	inline int getY() {
		return y;
	}
	inline float getSpeedY() {
		return speedY;
	}
	inline int getHight() {
		return hight;
	}
	inline int getWidth() {
		return  width;
	}
	inline int getLife() {
		return life;
	}
	inline HeartList* getHeartList() {
		return &heartList;
	}
	void drawPlayer(sf::RenderWindow &window);
	void moveRight();
	void moveLeft();
	void move();
	bool notLose(int sizeWindowY);
	void setPlayerToNewGame();
	bool highEnough();
	void updateScore(int scoreToUpdate);
	~Player();

};

#endif