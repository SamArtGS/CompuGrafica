#pragma once
#include <vector>
#include "Model3D.h"
#include "StaticModel.h"
#include "DymanicModel.h"

class Kart: public DynamicModel{
    private:
        float distancias[4] = {1,1,1,1};
    public:
    Kart(string rutaObj) : DynamicModel(rutaObj) {};
    void animate();
};

