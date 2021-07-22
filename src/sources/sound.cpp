#include "sound.h"

using namespace sf;

void sound::musica(string ogg) {
	cancion.openFromFile(ogg);
}

void sound::sonido(string wav) {
	//"./resources/sounds/coint.wav"
	buffer.loadFromFile(wav);
	sonidos.setBuffer(buffer);
}

void sound::playSound(int vol) {
	sonidos.setVolume(vol);
	sonidos.play();
}

void sound::playMusic(int vol) {
	cancion.setVolume(vol);
	cancion.setLoop(true);
	cancion.play();
}

