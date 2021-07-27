#pragma once
#include "Model3D.h"
#include "DymanicModel.h"

/*
* JumpAnimation:
* Esta clase genera la animacion de brincar hacia cualquier posición
* para cualquier objeto con formas humanoides (cabeza, cuerpo o tronco,
* brazos izquierdo y derecho, así como piernas izquierda y derechas).
* 
* Dentro de la carpeta que contiene los archivos obj se deben encontrar
* los siguientes objetos (con el mismo nombre):
*   - cuerpo.obj
*   - cabeza.obj
*   - brazoDer.obj
*   - brazoIzq.obj
*   - pieDer.obj
*   - pieIzq.obj
* 
* Existen 2 métodos para agregar los estados de la animación
*   - addEstadoAnimacion(Desplazamiento, float = 0, float = 0)
*       Recice cada estado a ejecutar, el tamaño del incremento o diferencial
*       y el limite o número unidades a moverse en total.
*   - setEstadosAnimacion(vector<AnimacionBrincar>)
*       Recibe un vector de tipo AnimacionBrincar que puede corresponder al de
*       otro modelo JumpAnimation, en este caso, la animacion será exactamente
*       igual a la del modelo base.
*/


// Desplazamiento es una enumeracion que corresponde con los posibles estados 
// de la animación.
// Los puntos cardinales coinciden con la proyeccion del plano xz:
//  - NORTE -> -z
//  - SUR   ->  z
//  - ESTE  ->  x
//  - OESTE -> -x
enum class Desplazamiento {
  INICIO,
  NORTE, SUR, ESTE, OESTE,
  GIRO_DERECHA, GIRO_IZQUIERDA
};

typedef struct {
  Desplazamiento estado;
  float delta;
  float limite;
} AnimacionBrincar;

class JumpAnimation : public DynamicModel {
private:
  Model3D* cabeza;
  Model3D* brazoIzq;
  Model3D* brazoDer;
  Model3D* cuerpo;
  Model3D* pieIzq;
  Model3D* pieDer;

  enum class Brincar {
    INICIO, ESTADO_1, ESTADO_2, ESTADO_3, ESTADO_4
  };
  Brincar estadoBrincar = Brincar::INICIO;
  int i = 0; // Posicion actual del vector de animaciones
  AnimacionBrincar estadoAnimacion;
  float xInit, yInit, zInit;
  float yRotInit;
  float desplazamientoX, desplazamientoY, desplazamientoZ;
  float deltaX, deltaZ;
  float anguloGiro;
  float deltaGiro;
  float anguloBrazosPiernas;
public:
  vector<AnimacionBrincar> animaciones;
  // JumpAnimation recibe la ruta de la carpeta que contiene todos los objetos,
  // las posiciones iniciales de los objetos, estas posiciones se consideran
  // para realizar la traslacion del objeto, y el angulo de rotacion en el 
  // eje Y en caso de desear rotar el objeto.
  JumpAnimation(string rutaObj, float, float, float, float = 0.f);
  void animate();
  void keyboardInput() {};
  void renderModels();
  void update();
  void siguienteMovimiento();
  JumpAnimation * addEstadoAnimacion(Desplazamiento, float = 0, float = 0);
  void setEstadosAnimacion(vector<AnimacionBrincar>);
};

