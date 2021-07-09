#pragma once

#include "Model3D.h"

class StaticModel : public Model3D{
public:
  StaticModel(string rutaObj) : Model3D(rutaObj) {};
};

