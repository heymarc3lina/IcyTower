#ifndef HEARTLIST_H
#define HEARTLIST_H
#include "Heart.h"
#include <list>

class HeartList {
	std::list<Heart> heartList;
	int ammountOfElements;
public:
	void deleteElements();
	HeartList(int ammountOfElements = 3);
	void createList();
	void deleteElement();
	void drawElements(sf::RenderWindow &window);
	~HeartList();

};

#endif