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
  MarioCraft(const char* title, int WINDOW_WIDTH, int WINDOW_HEIGHT, bool resizable);
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


  // Shaders
  static std::vector<Shader*> shaders;

  // Static variables

  // Static functions
  static void framebuffer_resize_callback(GLFWwindow*, int, int);


  static void scroll_callback(GLFWwindow*, double, double);

private:
  // Static variables
    // Camera
  static Camera* camera;
  // Variables
    // Window
  GLFWwindow* window;
  int WINDOW_WIDTH = 800;
  int WINDOW_HEIGHT = 600;
  int frameBufferWidth = 0;
  int frameBufferHeight = 0;
  // Matrices
  glm::mat4 ViewMatrix;		// Matriz de vista
  glm::mat4 ProjectionMatrix; // Matriz de Proyeccion
  // Timing
  double deltaTime = 0.0;
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
  void initWindow(const char* title, bool resizable);
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