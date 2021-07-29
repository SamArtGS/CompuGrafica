#pragma once
#include "Model3D.h"
#include "DymanicModel.h"
#include "GLM/vec4.hpp"

class Moneda : public DynamicModel {
private:
  Model3D* moneda;
public:
  Moneda(string rutaObj);
  void animate();
  void keyboardInput();
  void renderModels();
  void Render();
};

