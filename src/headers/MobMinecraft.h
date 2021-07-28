#pragma once
#include <vector>
#include "Model3D.h"
#include "StaticModel.h"
#include "DymanicModel.h"


class MobMinecraft : public DynamicModel {
protected:
    Model3D* torso;
    Model3D* brazoIzq;
    Model3D* brazoDer;
    Model3D* pieIzq;
    Model3D* pieDer;

    float ruta[8][2] = { 0 };
    int posicion = 0;
    float incremento = 0.0f;
    float posicionInicial[3] = { 0.0f, 0.0f, 0.0f };
    float escalaInicial[3] = { 0.0f, 0.0f, 0.0f };
    float posicionDesplazamiento[3] = { 0.0f,0.0f,0.0f };
    bool idaVueta = true;
    float angulo = 0.0f;
    bool animando = false;
    float auxiliarContador = 0.0f;
    float retardo = 0.0f;


    enum class Direccion {
        Norte=1, Sur=2, Este=3, Oeste=4
    };



public:
    enum class Tipo {
        Antropomorfico, Ave, Cuadrupedo
    };
    enum class TipoMovimiento {
        sixSag, cuadrado, rectangulo, L, C
    };
    MobMinecraft(string, Tipo,TipoMovimiento);
    void renderModels();
    void update();
    virtual Model3D* Translate(float tX, float tY, float tZ);
    virtual Model3D* Rotate(float angulo,float tX, float tY, float tZ);
    virtual Model3D* Scale(float tX, float tY, float tZ);
    void caminar();
}; 
