#include "Audio.h"

Audio::Audio() {
	try {
		if (!music.openFromFile("music.ogg")) {
			throw 1;
		}
		if (!jumpBuffer.loadFromFile("jump.wav")) {
			throw 2;
		}
	}
	catch (int i) {
		exit(1);
	}
	jumpSound.setBuffer(jumpBuffer);
	music.setVolume(100);
	music.setLoop(true);
	isMusicPlaying=1;
}

void Audio::playMusic() {
	if (isMusicPlaying) {
		music.play();
	}
}

void Audio::stopMusic() {
	music.stop();
	jumpSound.stop();
}

void Audio::turnUpTheVolume() {
	if (music.getVolume() < 100) {
		music.setVolume(ceil(music.getVolume() + 5));
		jumpSound.setVolume(ceil(music.getVolume() + 5));
	}
}

void Audio::turnDownTheVolume() {
	if (music.getVolume() > 0) {
		music.setVolume(ceil(music.getVolume() -5.0));
		jumpSound.setVolume(ceil(music.getVolume() - 5.0));
	}
}

void Audio::makeJumpSound() {
	if (isMusicPlaying) {
		jumpSound.play();
	}
}

Audio::~Audio() {
	music.stop();
}

void Audio::pauseMusic() {
	music.pause();
}