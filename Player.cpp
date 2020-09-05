#include "Player.h"

Player::Player(float x , float y , int hight , int width ) {
	life = 3;
	score = 0;
	this->hight = hight;
	this->x = x;
	this->y = y;
	this->speedY = 0;
	this->accelerationY = 0.1;
	this->width = width;
	heartList.createList();
	

	try {
		if (!PlayerTexture.loadFromFile("kitty.png")) {
			throw 1;
		} 
		if(!font.loadFromFile("Antaro.ttf")) {

			throw 2;
		}
		
		PlayerSprite.setTexture(PlayerTexture, true);
		PlayerSprite.setPosition(x, y);
		
		//std::string getScore = "Score:"+ std::to_string(score) ;
		scoreText.setFont(font);
		scoreText.setFillColor(sf::Color::White);
		scoreText.setString("Score:" + std::to_string(score));
		scoreText.setPosition(0, 50);

		
	}
	catch (int) {
		exit(1);
	}
	
}



void Player::drawPlayer(sf::RenderWindow &window) {
	PlayerSprite.setPosition(x, y);
	window.draw(PlayerSprite);
	heartList.drawElements(window);
	scoreText.setString("Score:" + std::to_string(score));
	window.draw(scoreText);

}

void Player::moveRight() {
	x += 3;
}

void Player::moveLeft() {
	x -= 3;
}


void Player::move() {
	y += speedY;
	PlayerSprite.setPosition(x, y);
	speedY += accelerationY;
}

bool Player::notLose(int sizeWindowY) {
	//sprawdzamy czy gracz wyszed³ za okno, czy ma ¿ycia oraz czy spada
	if (y > sizeWindowY- hight && life > 0 && speedY >0) {
		y = sizeWindowY-hight;
		speedY = -8;
		life -= 1;
		heartList.deleteElement();
		std::cout << "Trace  zycie " << std::endl;
		return true;
	}
	//sprawdzamy czy (nie spada lub czy jest na planszy) i czy ma zycia
	else if ((speedY <=0 ||y <= sizeWindowY - hight) && life > 0) {
		return true;
	}else {
		std::cout << "Umarlem" << std::endl;
		return false;
	}
}

void Player::setPlayerToNewGame() {
	life = 3;
	score = 0;
	x = 200;
	y = 200;
	this->speedY = 0;
	this->accelerationY = 0.1;
	heartList.createList();

}


bool Player::highEnough() {
	if (y <= 50) {
		return true;
	}
	return false;
}

void Player::updateScore(int scoreToUpdate) {
	score += scoreToUpdate;
}
 
Player::~Player() {
	
}