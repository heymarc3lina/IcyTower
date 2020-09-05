#ifndef LISTBESTPLAYER_H
#define LISTBESTPLAYER_H
#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>

struct player {
	std::string name;
	int score;
};

struct Score {
	std::string name;
	int score;
	Score *next;
};

class ListBestPlayer
{
public:
	Score *head;
	ListBestPlayer();
	~ListBestPlayer();
	//dodaje do listy gracza i jego punkty
	void add(std::string playerName, int scoreValue);
	//metoda usuwajaca ostatni element listy
	void dropLast();
	//metoda sluzaca do zapisu danych do pliku o podanej nazwie
	void save(std::string filename);
	//metoda sprawdzajaca czy dany gracz jest wystarczajaco dobry
	bool goodEnough(int score);
	//operator sluzacy do dodania do listy korzystajacy z metody add
	ListBestPlayer &operator+=(player sc);
	//zaprzyjaznione operatory strumieniowe sluzace do zapisu i odczytu z pliku
	friend std::ostream &operator<<(std::ostream &stream, Score *head);
	friend std::istream &operator>>(std::istream &stream, ListBestPlayer &list);
	//metoda sluzaca do wypisania listy na ekranie
	int showHighscores(sf::RenderWindow &window, sf::Text score[10], sf::Font &f);

};

#endif