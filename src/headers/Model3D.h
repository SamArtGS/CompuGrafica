#pragma once
#include <stdlib.h>
#include <string>		

#include <shader_m.h>
#include "Model.h"
#include <vector>

using  namespace std;

class Model3D : public Model {
private:
  string rutaObj;
public:
  glm::mat4 model;
  Model3D(string);
  Model3D* Init(glm::mat4);
  Model3D* Rotate(float, float, float, float);
  Model3D* Translate(float, float, float);
  Model3D* Scale(float, float, float);
  void Draw();
};