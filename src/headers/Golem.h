#pragma once
#include "MobMinecraft.h";
#include "MarioCraft.h";


class Golem : public MobMinecraft{
private:

    enum class Estado {
        caminando, matando = -1, saltando = -2
    };
    Estado estado = Estado::caminando;
    Model3D* creeper = new StaticModel("resources/objects/Creeper/creeper.obj");
    bool creeperMorido = false;
    float tiempoCreeper = 50;

    float posicionCreeper[3] = {0,0,0};
public:
	void animate();
	void keyboardInput();
	Golem(string rutaObj, Tipo, TipoMovimiento);
    void matarZombie();
}; 