#pragma once
#include <vector>
#include "Model3D.h"
#include "StaticModel.h"
#include "DymanicModel.h"

class Toad : public DynamicModel {
private:
    //float distancias[4] = { 1,1,1,1 };
    //float posicionInicial[3] = { 30.0f, 30.0f, -180.0f };
public:
    DynamicModel* cabeza = new Model3D("resources/objects/Karts/Kart1/kart1.obj");
    DynamicModel* brazoIzq = new DynamicModel("resources/objects/Karts/Kart1/kart1.obj");
    DynamicModel* brazoDer = new DynamicModel("resources/objects/Karts/Kart1/kart1.obj");
    DynamicModel* cuerpo = new DynamicModel("resources/objects/Karts/Kart1/kart1.obj");
    DynamicModel* pieIzq = new DynamicModel("resources/objects/Karts/Kart1/kart1.obj");
    DynamicModel* pieDer = new DynamicModel("resources/objects/Karts/Kart1/kart1.obj");
    Toad(string rutaObj) : DynamicModel(rutaObj) {};
    void animate();
    void keyboardInput();
};

