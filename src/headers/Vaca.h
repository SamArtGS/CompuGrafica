#pragma once
#include "MobMinecraft.h";
#include "MarioCraft.h";


class Vaca : public MobMinecraft {
private:
    float ruta[20][2] = {
            {1,220},
            {-1,30},
            {1,15},
            {2,15},
            {3,42},
            {4,15}
    };
    enum class Estado {
        caminando, mugiendo = -1, comiendo = -2
    };
    Estado estado = Estado::caminando;
    float tiempoMugir = 10.0f;

public:
    void animate();
    void keyboardInput();
    Vaca(string rutaObj, TipoMovimiento);
    void mugir();
};