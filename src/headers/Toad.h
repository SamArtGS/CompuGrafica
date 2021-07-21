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
    Toad(string rutaObj) : DynamicModel(rutaObj) {};
    void animate();
    void keyboardInput();
};

