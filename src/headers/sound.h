#pragma once

#include <libs.h>

using namespace sf;

class sound {
public:
	void musica(string ogg);
	void sonido(string wav);
	void playSound(int vol);
	void playMusic(int vol);
private:
	SoundBuffer buffer;
	Sound sonidos;
	Music cancion;

};