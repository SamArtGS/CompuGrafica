<p>
  <img src="img/icono.png" align="right"  width="50" height="50" />
</p>

## Manual de desarrollo 

### Clases

### Model3D
La clase base para poder dibujar los modelos en el ambiente es definida de la siguiente forma. Los elementos más importantes son:

- ``rutaObj ``:Ruta relativa del modelo OBJ que se cargará en el ambiente
- ``Init(glm::mat4)``:
- ``Translate(float, float, float)``:
- ``Rotate(float, float, float, float)``:
- ``Scale(float, float, float, float)``:

```cpp
class Model3D : public Model {
private:
  string rutaObj;
public:
  glm::mat4 model;
  Model3D(string);
  Model3D* Init(glm::mat4);
  Model3D* Rotate(float, float, float, float);
  virtual Model3D* Translate(float, float, float);
  Model3D* Scale(float, float, float);
  void Draw();
};

```

### Static y Dynamic Model

Model3D hereda a las siguientes clases, una destinada para los objetos estáticos dentro del ambiente y otra destinada a los elementos dinámicos que necesiten transladarse, rotarse o escalarse en un tiempo determinado.

```cpp
class StaticModel : public Model3D{
public:
  StaticModel(string rutaObj) : Model3D(rutaObj) {};
};
```

**Dynamic Model** incorpora además los métodos:

- ``render()`` que se llamará en un ciclo for desde la clase **ManageModel**.
- ``keyboardInput()``: Verifica constantemente la entrada en el teclado para que el modelo pueda realizar alguna acción.
- ``renderModels()``: Renderiza los elementos de un modelo en el diagrama jerárquico.

```cpp
class DynamicModel : public Model3D {
public:
  DynamicModel(string rutaObj) : Model3D(rutaObj) {};
  virtual void keyboardInput() = 0;
  virtual void animate() = 0;
  virtual void renderModels() = 0;
};
```

### Model Manager
Es el encargado de mostrar los elementos en pantalla gracias a que almacena todos los elementos estáticos y dinámicos y se encargar de llamar a los métodos de lo dibujan o actualizan.

```cpp
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

```

### JumpAnimation

Esta clase genera la animacion de brincar hacia cualquier posición para cualquier objeto con formas humanoides (cabeza, cuerpo o tronco, brazos izquierdo y derecho, así como piernas izquierda y derechas).

Dentro de la carpeta que contiene los archivos obj se deben encontrar los siguientes objetos (con el mismo nombre):

- cuerpo.obj
- cabeza.obj
- brazoDer.obj
- brazoIzq.obj
- pieDer.obj
- pieIzq.obj

Existen 2 métodos para agregar los estados de la animación

- ``addEstadoAnimacion(Desplazamiento, float = 0, float = 0)``: Recibe cada estado a ejecutar, el tamaño del incremento o diferencial y el limite o número unidades a moverse en total.
- ``setEstadosAnimacion(vector<AnimacionBrincar>)``: Recibe un vector de tipo AnimacionBrincar que puede corresponder al de otro modelo JumpAnimation, en este caso, la animacion será exactamente igual a la del modelo base.

El desplazamiento es una enumeracion que corresponde con los posibles estados de la animación.

Los puntos cardinales coinciden con la proyeccion del plano xz:

- NORTE -> -z
- SUR   ->  z
- ESTE  ->  x
- OESTE -> -x


**Esta clase es utilizada para los modelos: TOAD**


```cpp
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
  JumpAnimation(string rutaObj, float, float, float, float = 0.f);
  void animate();
  void keyboardInput() {};
  void renderModels();
  void update();
  void siguienteMovimiento();
  JumpAnimation * addEstadoAnimacion(Desplazamiento, float = 0, float = 0);
  void setEstadosAnimacion(vector<AnimacionBrincar>);
};
```

### Sound
Encargado de la reproducción del audio dentro del ambiente.

- ``musica(string ogg)``: Reproduce música de fondo contínuo.
- ``sonido(string ogg)``: Reproduce sonidos cortos para efectos.

```cpp
class sound {
public:
	void musica(string ogg);
	void sonido(string wav);
	void playSound(int vol);
	void playMusic(int vol);
private:
	SoundBuffer buffer;
	Sound sonidos;
	Music cancion;

};
```



### Lighting (Ciclo día - noche)

Para implementar la iluminación ambiental, se obtó por realizar un modelo de un sol y una luna que hagan que en el día haya luz ambiental y en la noche una luz puntual. Se realiza por medio de un ciclo de 12 horas diurno, y al llegar la noche se cambia por una luz posicional.


```cpp
class Lighting : public DynamicModel {
private:
  enum class EstadoTamano {
    EXTRASMALL,
    SMALL,
    MEDIUM,
    LARGE,
    EXTRALARGE
  };
  EstadoTamano tamanoSol = EstadoTamano::EXTRASMALL;
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
```

### Peach + Creeper

En cuanto inicia el programa, ambos realizan un recorrido desde el castillo, peach corre huyendo del creeper. El recorrido es sincronizado por medio de banderas. Al llegar a la torre, peach sube por las escaleras y se queda pidiendo ayuda en el piso superior, mientras tanto el creeper se queda en un ciclo dando vueltas alrededor de la torre. Todo esto está especificado en el método ``render()``.
De igual manera en la clase se especifican por medio de atributos Model3D* las partes en que se conforma el personaje y en enumeraciones los estados que tendrá la animación.



```cpp
class Peach : public DynamicModel {
private:
    Model3D* cabeza;
    Model3D* brazoIzq;
    Model3D* brazoDer;
    Model3D* cuerpo;
    Model3D* pieIzq;
    Model3D* pieDer;

    enum class Desplazar {
        INICIO,
        AVANZAR_1, AVANZAR_2, 
        AVANZAR_3, AVANZAR_4, 
        AVANZAR_5, AVANZAR_6,
        AVANZAR_7, AVANZAR_8,
        AVANZAR_9, AVANZAR_10,
        AVANZAR_11, AVANZAR_12,
        AVANZAR_13, AVANZAR_14,
    };
    enum class Correr {
        INICIO, INICIOARMS, ESTADO_2, ESTADO_3,INICIOBODY,ESTADO_1
    };
    enum class Caminar {
        INICIO, INICIOARMS, ESTADO_1, ESTADO_3
    };

    Desplazar estadoDesplazar = Desplazar::INICIO;
    Correr estadoCorrer = Correr::INICIO;
    Correr estadoCorrerArms = Correr::INICIOARMS;
    Correr estadoCorrerBody = Correr::INICIOBODY;
    Caminar estadoCaminar = Caminar::INICIO;
    Caminar estadoCaminarArms = Caminar::INICIOARMS;
    bool correr = false;
    bool caminar = true;
    bool subir = false;
    bool asustar = false;
    float rX, rY, rZ;
    float desplazamientoX, desplazamientoY, desplazamientoZ;
    float anguloGiro;
    float anguloBrazos, anguloBrazosCaminar;
    float anguloPiernas, anguloPiernasdescanso;
    float anguloCuerpoX, anguloCuerpoZ;
    float anguloCabeza;
    float escala = 0;
public:
    Peach(string rutaObj);
    void animate();
    void keyboardInput();
    void renderModels();
    void update();
    void delay(int secs);
};



class Creeper : public DynamicModel {
private:
    Model3D* cabeza;
    Model3D* cuerpo;
    Model3D* pieIzqDel;
    Model3D* pieDerDel;
    Model3D* pieIzqTras;
    Model3D* pieDerTras;
    enum class Desplazar {
        INICIO,
        AVANZAR_1, AVANZAR_2, 
        AVANZAR_3, AVANZAR_4, 
        AVANZAR_5, AVANZAR_6,
        AVANZAR_7, AVANZAR_8,
        AVANZAR_9, AVANZAR_10
    };
    enum class Caminar {
        INICIO, ESTADO_2
    };
    enum class explotar {
        INICIO, ESTADO_2
    };
    Desplazar estadoDesplazar = Desplazar::INICIO;
    Caminar estadoCaminar = Caminar::INICIO;
    explotar estadoExplota = explotar::INICIO;
    bool explota = false;
    float rX, rY, rZ;
    float desplazamientoX, desplazamientoY, desplazamientoZ;
    float anguloGiro;
    float anguloPiernas;
    float escala=1;
public:
    Creeper(string rutaObj);
    void animate();
    void keyboardInput();
    void renderModels();
    void update();
};

```

### Dragón

Esta clase genera la animacion de Ender dragon (Minecraft). La animacion consiste en el ender aleteando (subiendo y bajando), escupiendo cubos de lava cada cierto tiempo (generaciÛn aleatoria). y Moviendose por el escenario
según los estados indicados.

Existen 2 métodos para agregar los estados de la animación
 
 - ``addEstadoAnimacion(Desplazamiento, float = 0, float = 0)``: Recibe cada estado a ejecutar, el tamaño del incremento o diferencial y el límite o número unidades a moverse en total.

- ``setEstadosAnimacion(vector<AnimacionBrincar>)``: Recibe un vector de tipo AnimacionBrincar que puede corresponder al de otro modelo JumpAnimation, en este caso, la animación ser exactamente igual a la del modelo base.

```cpp
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


```
