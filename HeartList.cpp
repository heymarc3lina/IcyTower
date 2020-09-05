#include "HeartList.h"
HeartList::HeartList(int amountofElements) {
	this->ammountOfElements = amountofElements;
}

void HeartList::createList() {
	int x = 0;
	for (int i = 0; i < ammountOfElements; i++) {
		Heart * heart = new Heart(x, 0);
		heartList.push_front(*heart);
		x += heart->getWidth();
	}
}

void HeartList::deleteElement() {
	if (!heartList.empty()) {
		heartList.erase(heartList.begin());
	}
}
void HeartList::deleteElements() {
	if (!heartList.empty()) {
		heartList.clear();
	}
}

void HeartList::drawElements(sf::RenderWindow &window) {
	for (std::list<Heart>::iterator iter = heartList.begin(); iter != heartList.end(); iter++) {
		(*iter).drawHeart(window);
	}
}

HeartList::~HeartList() {
	deleteElements();
}