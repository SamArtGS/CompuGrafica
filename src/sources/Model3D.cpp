#pragma once
#include "Model3D.h"
#include "MarioCraft.h"

using  namespace std;

Model3D::Model3D(string rutaObj) : Model(rutaObj) {
  model = glm::mat4(1.0f);
}


Model3D Model3D::Init(glm::mat4 modelInit) {
  model = modelInit;
  return *this;
}

Model3D Model3D::Rotate(float ang, float rX, float rY, float rZ) {
  model = glm::rotate(model, glm::radians(45.0f), glm::vec3(rX, rY, rZ));
  return *this;
}

Model3D Model3D::Translate(float tX, float tY, float tZ) {
  model = glm::translate(model, glm::vec3(tX, tY, tZ));
  return *this;
}

Model3D Model3D::Scale(float sX, float xY, float sZ) {
  model = glm::scale(model, glm::vec3(sX, xY, sZ));
  return *this;
}

void Model3D::Draw() {
  int indice = shader_enum::SHADER_CORE_PROGRAM;
  MarioCraft::shaders[indice]->setMat4("model", model);
  Model::Draw(*MarioCraft::shaders[indice]);
}


