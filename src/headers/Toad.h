#pragma once
#include "Model3D.h"
#include "DymanicModel.h"

class Toad : public DynamicModel {
private:
  Model3D* cabeza;
  Model3D* brazoIzq;
  Model3D* brazoDer;
  Model3D* cuerpo;
  Model3D* pieIzq;
  Model3D* pieDer;
  enum class Desplazar { 
    INICIO, 
    AVANZAR_1, VUELTA_1, 
    AVANZAR_2, VUELTA_2, 
    AVANZAR_3, VUELTA_3, 
    AVANZAR_4, VUELTA_4 
  };
  enum class Brincar {
    INICIO, ESTADO_1, ESTADO_2, ESTADO_3, ESTADO_4
  };
  Desplazar estadoDesplazar = Desplazar::INICIO;
  Brincar estadoBrincar = Brincar::INICIO;
  float rX, rY, rZ;
  float desplazamientoX, desplazamientoY, desplazamientoZ;
  float anguloGiro;
  float anguloBrazosPiernas;
public:
    Toad(string rutaObj);
    void animate();
    void keyboardInput();
    void renderModels();
    void update();
};

