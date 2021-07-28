#pragma once
#pragma once
#include "Model3D.h"
#include "DymanicModel.h"

class Creeper : public DynamicModel {
private:
    Model3D* cabeza;
    Model3D* cuerpo;
    Model3D* pieIzqDel;
    Model3D* pieDerDel;
    Model3D* pieIzqTras;
    Model3D* pieDerTras;
    enum class Desplazar {
        INICIO,
        AVANZAR_1, AVANZAR_2, 
        AVANZAR_3, AVANZAR_4, 
        AVANZAR_5, AVANZAR_6,
        AVANZAR_7, AVANZAR_8,
        AVANZAR_9, AVANZAR_10
    };
    enum class Caminar {
        INICIO, ESTADO_2
    };
    enum class explotar {
        INICIO, ESTADO_2
    };
    Desplazar estadoDesplazar = Desplazar::INICIO;
    Caminar estadoCaminar = Caminar::INICIO;
    explotar estadoExplota = explotar::INICIO;
    bool explota = false;
    float rX, rY, rZ;
    float desplazamientoX, desplazamientoY, desplazamientoZ;
    float anguloGiro;
    float anguloPiernas;
    float escala=1;
public:
    Creeper(string rutaObj);
    void animate();
    void keyboardInput();
    void renderModels();
    void update();
};