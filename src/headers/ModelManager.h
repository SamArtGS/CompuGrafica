#pragma once

#include <vector>
#include "Model3D.h"
#include "StaticModel.h"
#include "DymanicModel.h"

enum tipoModel { STATIC, DYNAMIC };

class ModelManager{
private:
  std::vector<StaticModel*> staticModels;
  std::vector<DynamicModel*> dymanicModels;
public:
  void addModel(Model3D*, tipoModel tipo = STATIC);
  void renderModels();
  void keyboardInputModels();
  void updateModels();
};

