#ifndef MUSIC_H
#define MUSIC_H
#include <SFML/Audio.hpp>

class Audio {
	sf::Music music;
	sf::Sound jumpSound;
	sf::SoundBuffer jumpBuffer;
	bool isMusicPlaying;
	

public:
	Audio();
	//metoda wlaczajaca muzyke
	void playMusic();
	//metoda wylaczajaca muzyke
	void stopMusic();
	//metoda sluzaca do zglosnienia muzyki
	void turnUpTheVolume();
	//metoda sluzaca do sciczenia muzyki
	void turnDownTheVolume();
	//metoda powodujaca dzwiek skoku
	void makeJumpSound();
	//metoda pauzujaca muzyke
	void pauseMusic();
	~Audio();
	inline float getVolume() {
		return music.getVolume();
	}
	inline void setIsMusicPlaying(bool value) {
		isMusicPlaying = value;
	}
};
#endif