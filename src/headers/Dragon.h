#pragma once
#include "Model3D.h"
#include "DymanicModel.h"

/*
* Dragon:
* Esta clase genera la animacion de Ender dragon (Minecraft). La animacion
* consiste en el ender aleteando (subiendo y bajando), escupiendo cubos de 
* lava cada cierto tiempo (generación aleatoria). y Moviendose por el escenario
* según los estados indicados.
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

  typedef struct {
    MoviemientosDragon estado;
    float delta;
    float limite;
  } Animacion;

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
  int i = 0; // Posicion actual del vector de animaciones
  Animacion estadoAnimacion;
  Boca estadoBoca = Boca::INICIO;
  Magma estadoMagma = Magma::INICIO;
  float anguloMuslo;
  float anguloAla;
  float anguloGiro;
  float deltaGiro;
  float anguloVerticalCabeza = 0.f;
  float anguloHorizontalCabeza = 0.f;
  float anguloBoca = 0.f;
  float anguloColaX, anguloColaY;
  float deltaX, deltaZ;
  float xInit, yInit, zInit;
  float yRotInit;
  float desplazamientoX, desplazamientoY, desplazamientoZ;
  float magmaY;
  glm::mat4 magmaAux;
  float anguloMusloPiernas;
  float anguloPiernas;
  float anguloPatas;
  float anguloManos;
public:
  vector<Animacion> animaciones;
  Dragon(string rutaObj, float, float, float, float = 0.f);
  void animate();
  void keyboardInput();
  void renderModels();
  void update();
  void siguienteMovimiento();
  Dragon* addEstadoAnimacion(MoviemientosDragon, float = 0, float = 0);
  void setEstadosAnimacion(vector<Animacion>);
};

