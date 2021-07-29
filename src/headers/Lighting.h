#pragma once

#include "DymanicModel.h"

class Lighting : public DynamicModel {
private:
  enum class EstadoTamaño {
    EXTRASMALL,
    SMALL,
    MEDIUM,
    LARGE,
    EXTRALARGE
  };
  EstadoTamaño tamañoSol = EstadoTamaño::EXTRASMALL;
  enum class EstadoDia {
    DIA_1, DIA_2, DIA_3, DIA_4, DIA_5, DIA_6,
    DIA_7, DIA_8, DIA_9, DIA_10, DIA_11, DIA_12,
    NOCHE_1, NOCHE_2,
  };
  EstadoDia estado;
  float velocidad;
  float minutos = 0.f;
  float scaleSize = 1.f;
  Model3D* sol; 
  Model3D* luna;
  glm::mat4 initSol = glm::mat4(1.f);
  glm::mat4 initLuna = glm::mat4(0.f);
  // Iluminacion
  Shader* shader;
  float ambientDay = 0.2f;
  float ambientNight = 0.2f;
  float deltaIluminacion;
public:
  Lighting(string rutaObj, Shader* shader, float velocidad = .03f);
  void update();
  void animate();
  void keyboardInput() {};
  void renderModels();
};

