#pragma once
#include "Model3D.h"
#include "DymanicModel.h"

enum class MoviemientosDragon {
  INICIO, FIN,
  NORTE, SUR, ESTE, OESTE,
  GIRO_DERECHA, GIRO_IZQUIERDA
};

class Dragon : public DynamicModel {
private:
  Model3D* cuerpo;
  Model3D* cabeza;
  Model3D* colaParte1;
  Model3D* colaParte2;
  Model3D* colaParte3;
  Model3D* colaParte4;
  Model3D* magmaCube;
  Model3D* musloAlaDerecha;
  Model3D* musloAlaIzquierda;
  Model3D* alaDerecha;
  Model3D* alaIzquierda;
  Model3D* bocaSuperior;
  Model3D* bocaInferior;
  Model3D* musloDerecho;
  Model3D* piernaDerecha;
  Model3D* pataDerecha;
  Model3D* musloIzquierdo;
  Model3D* piernaIzquierda;
  Model3D* pataIzquierda;
  Model3D* manoDerecha;
  Model3D* manoIzquierda;
  enum class Alas {
    INICIO, ALETEAR_ARRIBA, ALETEAR_ABAJO
  };
  enum class Boca {
    INICIO, BAJAR, ABRIR, CERRAR, SUBIR, IZQUIERDA, DERECHA, CENTRO
  };
  enum class Magma {
    INICIO, LANZAR, ELIMINAR, ACTUALIZAR
  };
  Alas estadoAlas = Alas::INICIO;
  MoviemientosDragon estadoMoverse = MoviemientosDragon::INICIO;
  Boca estadoBoca = Boca::INICIO;
  Magma estadoMagma = Magma::INICIO;
  vector<MoviemientosDragon> movimientos;
  int i = 0;
  float anguloMuslo;
  float anguloAla;
  float anguloGiro;
  float anguloGiroAux;
  float anguloVerticalCabeza = 0.f;
  float anguloHorizontalCabeza = 0.f;
  float anguloBoca = 0.f;
  float anguloColaX, anguloColaY;
  float xInit, yInit, zInit;
  float incX, incY, incZ;
  float girX, girY, girZ;
  float magmaY;
  glm::mat4 magmaAux;
  float anguloMusloPiernas;
  float anguloPiernas;
  float anguloPatas;
  float anguloManos;
public:
  Dragon(string rutaObj, float, float, float, vector<MoviemientosDragon>);
  void animate();
  void keyboardInput();
  void renderModels();
  void update();
  void definirMovimientos();
  void siguienteMovimiento();
};

