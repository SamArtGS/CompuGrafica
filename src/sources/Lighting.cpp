#include "Lighting.h"
#include <MarioCraft.h>

Lighting::Lighting(string rutaObj, Shader* shader, float velocidad)
  : DynamicModel(rutaObj + "/sun.obj"), velocidad(velocidad), shader(shader) {
  estado = EstadoDia::DIA_1;
  sol = this;
  luna = new Model3D(rutaObj + "/moon.obj");
  deltaIluminacion = 0.8 / (30 / velocidad);
}

//Listener
void Lighting::animate() {
  update();

  sol->Init(initSol)
    ->Rotate(minutos - 90, 0.f, 0.f, 1.f)
    ->Translate(0.f, 500.f, -500)
    ->Scale(scaleSize, scaleSize, scaleSize);
  luna->Init(initLuna)
    ->Rotate(minutos - 90, 0.f, 0.f, 1.f)
    ->Translate(0.f, 500.f, -250.f)
    ->Scale(10.f, 10.f, 10.f)
    ->Scale(scaleSize, scaleSize, scaleSize);

  // Actualizacion de la iluminacion del escenario
  shader->use();
  shader->setVec3("viewPos", MarioCraft::camera->Position);
  shader->setVec3("dirLight.direction", glm::vec3(0.f, -1.f, -1.f));
  shader->setVec3("dirLight.ambient", glm::vec3(ambientDay, ambientDay, ambientDay));
  shader->setVec3("dirLight.diffuse", glm::vec3(0.f, 0.f, 0.f));
  shader->setVec3("dirLight.specular", glm::vec3(1.f, 1.f, 1.f));

  if (estado == EstadoDia::NOCHE_2) {
    shader->setVec3("pointLight[0].position", luna->model[3]);
    shader->setVec3("pointLight[0].ambient", glm::vec3(1.0f, 1.0f, 1.0f));
    shader->setVec3("pointLight[0].diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
    shader->setVec3("pointLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
    shader->setFloat("pointLight[0].constant", .7f);
    shader->setFloat("pointLight[0].linear", 0.0014f);
    shader->setFloat("pointLight[0].quadratic", 0.000007f);
  }
  else {
    shader->setVec3("pointLight[0].position", sol->model[3]);
    shader->setVec3("pointLight[0].ambient", glm::vec3(1.0f, 1.0f, 0.0f));
    shader->setVec3("pointLight[0].diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
    shader->setVec3("pointLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
    shader->setFloat("pointLight[0].constant", 1.f);
    shader->setFloat("pointLight[0].linear", 0.7f); 
    shader->setFloat("pointLight[0].quadratic", 1.8f);
  }
}


void Lighting::update() {

  minutos += velocidad;
  switch (estado) {
  case EstadoDia::DIA_1:
    ambientDay += deltaIluminacion;
    scaleSize += 0.0002f;
    if (minutos >= 30) {
      estado = EstadoDia::DIA_2;
    }
    break;
  case EstadoDia::DIA_2:
    scaleSize += 0.0001f;
    if (minutos >= 90) {
      estado = EstadoDia::DIA_3;
    }
    break;
  case EstadoDia::DIA_3:
    scaleSize -= 0.0001f;
    if (minutos >= 160) {
      estado = EstadoDia::DIA_4;
    }
    break;
  case EstadoDia::DIA_4:
    if (scaleSize >= 1) scaleSize -= 0.003f;
    ambientDay -= deltaIluminacion;
    if (minutos >= 180) {
      minutos = 0.f;
      initSol = glm::mat4(0.f);
      estado = EstadoDia::NOCHE_1;
    }
    break;
  case EstadoDia::NOCHE_1:
    scaleSize = 1.f; 
    if (ambientDay > 0.0f)
      ambientDay -= deltaIluminacion;
    if (minutos >= 15) {
      minutos = 0;
      initLuna = glm::mat4(1.f);
      estado = EstadoDia::NOCHE_2;
    }
      break;
  case EstadoDia::NOCHE_2:    
    if (minutos >= 180) {
      minutos = 0;
      ambientDay = 0.2f;
      initLuna = glm::mat4(0.f);
      initSol = glm::mat4(1.f);
      estado = EstadoDia::DIA_1;
    }
    break;
  }
}

void Lighting::renderModels() {
  luna->Draw();
}