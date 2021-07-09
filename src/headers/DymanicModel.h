#pragma once

#include "Model3D.h"

class DynamicModel : public Model3D {
public:
  DynamicModel(string rutaObj) : Model3D(rutaObj) {};
  virtual void keyboardInput() = 0;
  virtual void animate() = 0;
};

