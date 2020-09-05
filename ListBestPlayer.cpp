#include "ListBestPlayer.h"



ListBestPlayer::ListBestPlayer()
{
	head = nullptr;
}


ListBestPlayer::~ListBestPlayer()
{
	Score *temp = head;
	while (temp) {
		temp = head->next;
		delete head;
		head = temp;
	}
}

void ListBestPlayer::add(std::string playerName, int scoreValue) {
	if (head == nullptr) {
		Score *score = new Score{ playerName, scoreValue, nullptr };
		head = score;
		return;
	}

	if (scoreValue > head->score) {
		Score *score = new Score{ playerName, scoreValue, head };
		head = score;
		return;
	}

	Score *temp = head;

	while (temp->next) {
		if (temp->next->score >= scoreValue)
			temp = temp->next;
		else
			break;
	}
	if (temp->next) {
		Score *score = new Score{ playerName, scoreValue, temp->next };
		temp->next = score;
		return;
	}
	//gdy na koncu do dodania
	else {
		Score *score = new Score{ playerName, scoreValue, nullptr };
		temp->next = score;
		return;
	}
}


void ListBestPlayer::dropLast() {
	Score *temp = head;
	while (temp->next->next) {
		temp = temp->next;
	}
	Score *temp2 = temp->next;
	temp->next = nullptr;
	delete temp2;
}

ListBestPlayer &ListBestPlayer::operator+=(player score) {
	add(score.name, score.score);
	return *this;
}


void ListBestPlayer::save(std::string filename) {
	std::ofstream plik(filename);
	if (plik) {
		
		Score *temp = head;
		for (int i = 0; i < 10; i++) {
			plik << temp->name << " " << temp->score << std::endl;
			temp = temp->next;
		}
		plik.close();
		//plik << this->head;
	}

	
}


bool ListBestPlayer::goodEnough(int score) {
	Score *temp = head;
	for (int i = 0; i < 10; i++) {
		if (score > temp->score)
			return true;
		temp = temp->next;
	}
	return false;
}

int ListBestPlayer::showHighscores(sf::RenderWindow &window, sf::Text score[10], sf::Font &font) {

	window.clear();

	Score *tem = head;
	for (int i = 0; i < 10; i++) {
		score[i].setFont(font);
		score[i].setFillColor(sf::Color::Green);
		std::string temp = tem->name + ": " + std::to_string(tem->score);
		score[i].setString(temp);
		score[i].setPosition(sf::Vector2f(window.getSize().x / 2 - score[i].getLocalBounds().width / 2, window.getSize().y / (10 + 1) * (i + 1)));
		window.draw(score[i]);
		tem = tem->next;
	}

	window.display();
	while (window.isOpen()) {
		window.clear();
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				return -1;
			case sf::Event::KeyReleased:
				switch (event.key.code) {
				case sf::Keyboard::Escape:
					return 1;
				}
			}
		}
	}
}


std::ostream &operator<<(std::ostream & stream, Score *head) {
	Score *temp = head;
	std::cout << head << std::endl;
	while (temp) {
		stream << temp->name << " " << temp->score << std::endl;
		temp = temp->next;
	}
	return stream;
}

std::istream &operator>>(std::istream & stream, ListBestPlayer &list) {
	player tmp;
	for (int i = 0; i < 10; i++) {
		stream >> tmp.name;
		stream >> tmp.score;
		list += tmp;
		tmp.name = "";
		tmp.score = 0;
	}

	return stream;
}