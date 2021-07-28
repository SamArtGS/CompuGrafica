#pragma once
#pragma once
#include "Model3D.h"
#include "DymanicModel.h"

class Peach : public DynamicModel {
private:
    Model3D* cabeza;
    Model3D* brazoIzq;
    Model3D* brazoDer;
    Model3D* cuerpo;
    Model3D* pieIzq;
    Model3D* pieDer;

    enum class Desplazar {
        INICIO,
        AVANZAR_1, AVANZAR_2, 
        AVANZAR_3, AVANZAR_4, 
        AVANZAR_5, AVANZAR_6,
        AVANZAR_7, AVANZAR_8,
        AVANZAR_9, AVANZAR_10,
        AVANZAR_11, AVANZAR_12,
        AVANZAR_13, AVANZAR_14,
    };
    enum class Correr {
        INICIO, INICIOARMS, ESTADO_2, ESTADO_3,INICIOBODY,ESTADO_1
    };
    enum class Caminar {
        INICIO, INICIOARMS, ESTADO_1, ESTADO_3
    };

    Desplazar estadoDesplazar = Desplazar::INICIO;
    Correr estadoCorrer = Correr::INICIO;
    Correr estadoCorrerArms = Correr::INICIOARMS;
    Correr estadoCorrerBody = Correr::INICIOBODY;
    Caminar estadoCaminar = Caminar::INICIO;
    Caminar estadoCaminarArms = Caminar::INICIOARMS;
    bool correr = false;
    bool caminar = true;
    bool subir = false;
    bool asustar = false;
    float rX, rY, rZ;
    float desplazamientoX, desplazamientoY, desplazamientoZ;
    float anguloGiro;
    float anguloBrazos, anguloBrazosCaminar;
    float anguloPiernas, anguloPiernasdescanso;
    float anguloCuerpoX, anguloCuerpoZ;
    float anguloCabeza;
    float escala = 0;
public:
    Peach(string rutaObj);
    void animate();
    void keyboardInput();
    void renderModels();
    void update();
    void delay(int secs);
};