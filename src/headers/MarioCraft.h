/*-------------------------------------------------------------------*/
/* ---------------- PROYECTO FINAL: MARIOCRAFT ----------------------*/
/*-----------------              2021-2          --------------------*/
/*------------- Alumno: Ricardo Antonio Hern�ndez Torres ------------*/
/*------------- Alumno: Jorge C�rdenas C�rdenas          ------------*/
/*------------- Alumno: Samuel Arturo Garrido S�nchez    ------------*/

#pragma once

#include "libs.h"

//ENUMERATIONS
enum shader_enum { 
  SHADER_CORE_PROGRAM = 0, 
  SHADER_SKYBOX = 1 
};

class MarioCraft {
public:
  // Constructors / Destructors
  MarioCraft(const char* title, const char* icono, int WINDOW_WIDTH, int WINDOW_HEIGHT, bool resizable);
  virtual ~MarioCraft();

  // Accessors
  int getWindowShouldClose();

  //Modifiers
  void setWindowShouldClose();

  // Functions
  void updateDeltaTime();
  void updateInput();
  void update();
  void render();
  void updateMouseInput();
  void updateKeyboardInput();
  static GLFWwindow* window;

  // Camera
  static Camera* camera;
  // Shaders
  static std::vector<Shader*> shaders;

  // Static variables

  // Static functions
  static void framebuffer_resize_callback(GLFWwindow*, int, int);


  static void scroll_callback(GLFWwindow*, double, double);

private:
  // Static variables
  // Variables
    // Window
  
  int WINDOW_WIDTH = 500;
  int WINDOW_HEIGHT = 400;
  int frameBufferWidth = 0;
  int frameBufferHeight = 0;
  // Matrices
  glm::mat4 ViewMatrix;		// Matriz de vista
  glm::mat4 ProjectionMatrix; // Matriz de Proyeccion
  // Timing
  double deltaTime = 0.1;
  double lastFrame = 0.0;
  const int FPS = 60;
  const int LOOP_TIME = 1000 / FPS;
  // Lighting
  glm::vec3 lightPosition;
  glm::vec3 lightDirection;
  // Skybox
  Skybox* skybox;
  // Models
  ModelManager* models;

  //Mouse Input
  double lastMouseX;
  double lastMouseY;
  double mouseX;
  double mouseY;
  double mouseOffsetX;
  double mouseOffsetY;
  bool firstMouse;
  // Scroll Input
  double scrollOffsetY;

  // Private functions
  void getResolution();
  void initGLFW();
  void initWindow(const char* title, const char* icono, bool resizable);
  void initGLAD();
  void initOpenGLOptions();
  void initShaders();
  void initLights();
  void initSkybox();
  void initModels();

  void renderLights();
  void renderSkybox();
  void renderModels();

};