#include "Game.h"

Game::Game(): window(sf::VideoMode(1000, 1000), "game", sf::Style::Close) {
	amountOfPlatform = 15;
	isRunning = 1;
	isLevelHard = 0;
	window.setFramerateLimit(80);
	window.setPosition({ window.getPosition().x, 0 });
	while (window.isOpen()) {
		int state_welcome = screen.drawMenu(window);
		switch (state_welcome) {
		case 0:
			//wybrano opcje gry i wchodzimy do petli gry
			gameLoop();
			break;
		case 1:
			//wybrano opcje settings ,a  wiec wchodzimy do ustawien gry
			settings.drawMenu(window, audio, !isRunning, isLevelHard);
			break;
		case 2:
			//wybrano opcje hihscore, na ekranie wyswietla sie lista 10 najlepszych graczy
			if (screen.highscoresMenu(window) == 1)
			break;
		case 3:
			//opcja exit zamyka okno
			window.close();
			break;
		}
	}
}

void Game::gameLoop() {
	//tworzymy startowe platformy i puszczamy muzyke
	createStartPlatforms();
	audio.playMusic();
	//dopoki okno jest otwarte, gracz ma zycia oraz gra trwa
	while (window.isOpen() && player.notLose(window.getSize().y) && isRunning) {
		window.clear();
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) { //zamknieto okno
				window.close();
			} //wybrano opcje pauzy
			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) {
				pauseManage();
			}
		}
		if (isRunning) { //gra trwa
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { //sprawdzamy czy nie wciskamy prawej strzalki
				if (player.getX() + 80 < window.getSize().x) { //sprawdzamy czy gracz nie wyszedl poza prawy bok okna
					player.moveRight(); // przesuwamy gracza w prawo
				}
			}if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {//sprawdzamy czy nie wciskamy lewej strzalki
				if (player.getX() > 0) { //sprawdzamy czy gracz nie wyszedl poza lewy bok okna
					player.moveLeft();// przesuwamy gracza w lewo
				}
			}
			player.move(); // poruszamy gracza
			board.drawBoard(window); //rysujemy tlo
			getDownPlayerAndPlatform(); // poruszamy platfromy i gracza w dol aby uzyskac efekt przesuwania sie ekranu
			for (int i = 0; i < amountOfPlatform; i++) { //rysujemy platfromy
				if (platformTable[i]->ifDraw()) {
					platformTable[i]->drawPlatform(window);
				}
			}
			player.drawPlayer(window); //rysujemy gracza
			bouncePlatform(); //odbijamy go od platformy
			window.display(); //wszystko wyswietlamy na ekranie
		}
	}
	audio.stopMusic(); //po przegranej zamykamy muzyke
	if (isRunning) {  //jesli gra sie skonczyla w sposob normalny(utrata zyc) to wyswietlamy na ekranie
		//informacje o punktach oraz jesli ma odpowiednie punkty pytamy go o imie
		screen.loseScreen(window, player.getScore());
	}
	player.getHeartList()->deleteElements(); //usuwamy liste serc
	player.setPlayerToNewGame();//czyscimy gracza do nowej gry
	deletePlatforms(); //usuwamy wszystkie platformy
	isRunning = 1;
}

void Game::deletePlatforms() {
	for (int i = 0; i < amountOfPlatform; i++) {
		delete platformTable[i];
	}
}

Game::~Game() {
	window.close();	
}

void Game::createStartPlatforms() {
	
	for (int i = 0 ; i < amountOfPlatform; i++) {
		setRandomPlatform(i); // losujemy typ platfromy i losujemy wspolrzedne
		int randomX = getRandomNumber(0, window.getSize().x - platformTable[i]->getWidth());
		int randomY = getRandomNumber(0, window.getSize().y - platformTable[i]->getHight());
		
		bool lookForX = true;
		int attempt = 0;
		//szukamy od elementu 2 w tablicy oraz do 10 lub dopóki znajdziemy
		while (i > 0 && attempt++ < 100 && lookForX) {
			for (int j = 0; j < i; j++) {
				float distance = getEuclideanDistance(randomX, platformTable[j]->getX(), randomY, platformTable[j]->getY());
				if ( distance < 200) { //jesli znaleziony dystans jest mniejszy od 200 to szukamy wspolrzednych dalej
					randomX = getRandomNumber(0, window.getSize().x - platformTable[i]->getWidth());
					randomY = getRandomNumber(0, window.getSize().y - platformTable[i]->getHight());
					break;
				}
				else if (j == i - 1) { 
					lookForX = false; //doszlismy do konca tablicy i nie bylo zandej zmiany, a wiec znalezlismy pozycje
				}
			}
		}

		if (!lookForX || i==0) {
			platformTable[i]->setXY(randomX, randomY); //ustawiamy pozycje platformy o ile zostala znaleziona
		}
	}
}


int Game::getRandomNumber(int number1, int number2) {
	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_int_distribution<int> uniform_dist(number1, number2);
	return uniform_dist(e1);
}

void Game::getDownPlayerAndPlatform() {
	if (player.highEnough() && player.getSpeedY() <= 0) { //jesli gracz jest wystarczajaco wysoko i leci do gory
		player.updateScore(-player.getSpeedY()); //to powiekszamy jego punkty
		for (int i = 0; i < amountOfPlatform; i++) { //oraz przzesuwamy w dol gracza oraz plefera
			platformTable[i]->setY(platformTable[i]->getY() - player.getSpeedY());
		}
		player.setPosition(player.getX(), player.getY() - player.getSpeedY());
	}
	else if(isLevelHard) { //gdy mamy wlaczony poziom hard to po prostu kiedy gracz nie leci do gory ekran sam sie przemieszka ku gorze
		for (int i = 0; i < amountOfPlatform; i++) {
			platformTable[i]->setY(platformTable[i]->getY() + 1);
		}
		player.setPosition(player.getX(), player.getY() + 1);
	}
	changePositionOfDisapearedPlatform(); //zmieniamy pozycje platform, ktore zniknely z ekranu
}



void Game::changePositionOfDisapearedPlatform() {
	float nearestDistance;
	for (int i = 0; i < amountOfPlatform; i++) {
		if (platformTable[i]->getY() >= window.getSize().y) {
			changePlatformType(i); //zmiana typu platformy
			int randomX = getRandomNumber(0, window.getSize().x - platformTable[i]->getWidth());
			int attempt = 0;
			bool lookForX = true;
			while (attempt < 10 && lookForX) {
				nearestDistance = distanceToNearestPlatform(i, randomX, amountOfPlatform);
				for (int j = 0; j < amountOfPlatform; j++) {
					float distance = getEuclideanDistance(randomX, platformTable[j]->getX(), 0, platformTable[j]->getY());
					if (i!=j && (distance < 200 || nearestDistance > 350)) { // podobnie jak w create platform, ale tutaj jeszcze sprawdzamy
						//najblizsza odleglosc do najblizszej platformy
						randomX = getRandomNumber(0, window.getSize().x - platformTable[i]->getWidth());
						break;
					}
					if (j == amountOfPlatform-1) {
						lookForX = false;
					}
				}
				attempt++;
			}
			if (!lookForX) {
				platformTable[i]->setXY(randomX, 0);
			}
		}
	}
}


float Game::getEuclideanDistance(float x1, float x2, float y1, float y2) {
	return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

bool Game::hitThePlatform(int index) {
	return (player.getX() + 20 <= (platformTable[index])->getX() + (platformTable[index])->getWidth()) &&
		(player.getX() + player.getWidth() - 20 >= (platformTable[index])->getX()) &&
		(player.getY() + player.getHight()  <= (platformTable[index])->getY() + (platformTable[index])->getHight())
		&& (player.getY() + player.getHight() > (platformTable[index])->getY());
}

void Game::bouncePlatform(){
	
	if (player.getSpeedY() >= 0 ) { //czy gracz spada
		for (int i = 0; i < amountOfPlatform; i++) {
			if (hitThePlatform(i) && platformTable[i]->ifDraw()) { //czy udezyl w platforme i ona jest rysowana	
				audio.makeJumpSound(); //dzwiek odbicia od platformy
				player.setSpeed(platformTable[i]->getBounceSpeed()); //odbijamy gracza
				platformTable[i]->specialAbility(player); //platforma spelnia swoje zadanie czyli np daje ekstra pkt lub odbija nas mocniej
				try { //rzutujemy na BrokenPlatform aby wywolac metode z tej klasy
					//gdy nullptr to rzucamy wyjatek
					BrokenPlatform &platform = dynamic_cast<BrokenPlatform&>(*platformTable[i]);
					platform.disapear(); //jak nie jest nullptr to wywoluje siê metoda
				}
				catch (std::bad_cast b) {
					std::cout << "Caught: " << b.what();
				}
			}
		}
	}
}

void Game::changePlatformType(int position) {
	float y = platformTable[position]->getY();
	delete platformTable[position];
	int whichPlatform = getRandomNumber(0, 100);

	if (whichPlatform < 60) {
		platformTable[position] = new DefaultPlatform(0, y);
	}
	else if (whichPlatform >=60 && whichPlatform < 70) {
		platformTable[position] = new SpeedPlatform(0,y);
	}
	else if (whichPlatform >= 70 && whichPlatform < 80) {
		platformTable[position] = new FirePlatform(0, y);
	}
	else if (whichPlatform >= 80 && whichPlatform <90 ) {
		platformTable[position] = new BrokenPlatform(0, y);
	}
	else {
		platformTable[position] = new BonusPlatform(0, y);
	}
}

void Game::setRandomPlatform(int position) {
	
	int whichPlatform = getRandomNumber(0, 100);
	if (whichPlatform < 60) {
		platformTable[position] = new DefaultPlatform();
	}
	else if (whichPlatform >= 60 && whichPlatform < 70) {
		platformTable[position] = new SpeedPlatform();
	}
	else if (whichPlatform >= 70 && whichPlatform < 80) {
		platformTable[position] = new FirePlatform();
	}
	else if (whichPlatform >= 80 && whichPlatform < 90) {
		platformTable[position] = new BrokenPlatform();
	}
	else {
		platformTable[position] = new BonusPlatform();
	}
}

float Game::distanceToNearestPlatform(int position,int newX, int amount) {
	float minimumDistance = window.getSize().y;
	
	for (int i = 0; i < amount; i++) {
		if (position != i && (typeid(*platformTable[i]) != typeid(BrokenPlatform) && typeid(*platformTable[i])!= typeid(FirePlatform))) {
			float distance = getEuclideanDistance(platformTable[i]->getX(), newX, platformTable[i]->getY(), platformTable[position]->getY());
			if (minimumDistance > distance) {
				minimumDistance = distance;
			}
	    }
	}
	return minimumDistance;
}

void Game::pauseManage() {
	while (window.isOpen()) {
		int state_welcome = pauseScreen.drawMenu(window);
		switch (state_welcome) {
		case 0:
			return;
		case 1:
			settings.drawMenu(window, audio, isRunning,isLevelHard );
			break;
		case 2:
			isRunning = 0;
			return;
		case 3:
			window.close();
			break;
		}
	}
}