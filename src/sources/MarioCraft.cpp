#pragma once

#include "MarioCraft.h"

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "StaticModel.h"
#include "DymanicModel.h"
#include "Kart.h"


// Static declarations
vector<Shader*> MarioCraft::shaders;
Camera* MarioCraft::camera;

// Constructors / Destructors
MarioCraft::MarioCraft(const char* title, int WINDOW_WIDTH, int WINDOW_HEIGHT, bool resizable)
  : WINDOW_WIDTH(WINDOW_WIDTH), WINDOW_HEIGHT(WINDOW_HEIGHT) {

  // Init Variables
  this->window = nullptr;
  this->frameBufferWidth = this->WINDOW_WIDTH;
  this->frameBufferHeight = this->WINDOW_HEIGHT;

  // Init Camara
  this->camera = new Camera(glm::vec3(0.0f, 50.0f, 90.0f));

  this->lastMouseX = 0.0;
  this->lastMouseY = 0.0;
  this->mouseX = 0.0;
  this->mouseY = 0.0;
  this->mouseOffsetX = 0.0;
  this->mouseOffsetY = 0.0;
  this->firstMouse = true;

  this->initGLFW();
  // Validate the screen resolution
  if (this->WINDOW_WIDTH <= 0 || this->WINDOW_WIDTH < 0) this->getResolution();

  this->initWindow(title, resizable);
  this->initGLAD();
  this->initOpenGLOptions();

  this->initShaders();
  this->initSkybox();

  this->initModels();
}

MarioCraft::~MarioCraft() {
  // Terminamos los recursos para el Skybox
  skybox->Terminate();

  glfwDestroyWindow(this->window);
  glfwTerminate();
  

  // Destruir los Shaders
  for (size_t i = 0; i < this->shaders.size(); i++)
    delete this->shaders[i];
}

// Static functions
// framebuffer_resize_callback establece el tamaño de la ventana
void MarioCraft::framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH) {
  glViewport(0, 0, fbW, fbH);
}

//Accessor
//
int MarioCraft::getWindowShouldClose(){
  return glfwWindowShouldClose(this->window);
}

//Modifier
// setWindowShouldClose detecta el cierre de ventana
void MarioCraft::setWindowShouldClose(){
  glfwSetWindowShouldClose(this->window, GLFW_TRUE);
}

// scroll_callback se ejecuta cada que la rueda de desplazamiento del mouse de desplaza
void  MarioCraft::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
  MarioCraft::camera->ProcessMouseScroll(yoffset);
}


// Functions
// updateMouseInput reacciona a los eventos del mouse
void MarioCraft::updateMouseInput() {
  glfwGetCursorPos(this->window, &this->mouseX, &this->mouseY);

  if (this->firstMouse){
    this->lastMouseX = this->mouseX;
    this->lastMouseY = this->mouseY;
    this->firstMouse = false;
  }

  // Calcular offset
  this->mouseOffsetX = this->mouseX - this->lastMouseX;
  this->mouseOffsetY = this->lastMouseY - this->mouseY;

  // Establece last X and Y
  this->lastMouseX = this->mouseX;
  this->lastMouseY = this->mouseY;

  // Reposiciona la camara
  camera->ProcessMouseMovement(mouseOffsetX, mouseOffsetY);
  
}

// updateKeyboardInput reacciona a los eventos del teclado
void MarioCraft::updateKeyboardInput() {
  // Program
  if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
    glfwSetWindowShouldClose(this->window, GLFW_TRUE);
  }

  // Camera
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera->ProcessKeyboard(FORWARD, (float)deltaTime);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera->ProcessKeyboard(BACKWARD, (float)deltaTime);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera->ProcessKeyboard(LEFT, (float)deltaTime);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera->ProcessKeyboard(RIGHT, (float)deltaTime);
    
  // Models
  models->keyboardInputModels();
}
// updateDeltaTime limita el framerate a los FPS establecidos
void MarioCraft::updateDeltaTime() {
  deltaTime = SDL_GetTicks() - lastFrame; // time for full 1 loop
  //std::cout <<"frame time = " << frameTime << " milli sec"<< std::endl;
  if (deltaTime < LOOP_TIME)
    SDL_Delay((int)(LOOP_TIME - deltaTime));

}

// updateInput reacciona a los eventos de entrada
void MarioCraft::updateInput(){
  glfwPollEvents();

  this->updateKeyboardInput();
  this->updateMouseInput();
}

// update realiza los cambios necesarios antes de renderizar
void MarioCraft::update() {
  this->lastFrame = SDL_GetTicks();

  this->updateInput();
  models->updateModels();
}

//
void MarioCraft::render() {
  

  // DRAW ---
  // Clear
  glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Update the uniforms
  update();

  // Render models
  renderSkybox();
  renderLights();
  renderModels();

  // Update Timing
  updateDeltaTime();
  // End Draw
  glfwSwapBuffers(window);
  glFlush();

  /* Reset
  glBindVertexArray(0);
  glUseProgram(0);
  glActiveTexture(0);
  glBindTexture(GL_TEXTURE_2D, 0);
  */
}

// Private functions
//
void MarioCraft::initGLFW() {
  if (glfwInit() == GLFW_FALSE) {
    std::cout << "EROR:GLFW_INIT_FAILED" << "\n";
    glfwTerminate();
  }
}

// getResolution obtiene las dimesiones máximas de la pantalla
void MarioCraft::getResolution() {
  const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  this->WINDOW_WIDTH = mode->width;
  this->WINDOW_HEIGHT = (mode->height) - 80;
}

// 
void MarioCraft::initWindow(const char* title, bool resizable) {
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_RESIZABLE, resizable);

  this->window = glfwCreateWindow(this->WINDOW_WIDTH, this->WINDOW_HEIGHT, title, NULL, NULL);

  if (this->window == nullptr){
    std::cout << "ERROR::GLFW_WINDOW_INIT_FAILED" << "\n";
    glfwTerminate();
  }
  glfwSetWindowPos(window, 0, 30);
  glfwGetFramebufferSize(window, &this->frameBufferWidth, &this->frameBufferHeight);
  glfwSetFramebufferSizeCallback(window, MarioCraft::framebuffer_resize_callback);
  glfwSetScrollCallback(window, MarioCraft::scroll_callback);
  glfwMakeContextCurrent(this->window);
}


// initGLAD cargar todos los punteros de función OpenGL
void MarioCraft::initGLAD() {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "ERROR::MAIN.CPP::GLAD_INIT_FAILED" << std::endl;
    glfwTerminate();
  }
}

// initOpenGLOptions configura el estado global de OpenGL
void MarioCraft::initOpenGLOptions() {
  glEnable(GL_DEPTH_TEST);

  //Input
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

//
void MarioCraft::initShaders() {
    // staticShader

  this->shaders.push_back(
      new Shader("Shaders/shader_Lights.vs", "Shaders/shader_Lights.fs")
  );
  
  // skyboxShader
  this->shaders.push_back(new Shader("Shaders/skybox.vs", "Shaders/skybox.fs"));
}


// initLights inicializa los vectores para las luces
void MarioCraft::initLights(){
  lightPosition = glm::vec3(0.0f, 4.0f, -10.0f);
  lightDirection = glm::vec3(0.0f, -1.0f, -1.0f);

}

// initSkybox inicializa el cubo que generará el cielo del escenario
void MarioCraft::initSkybox() {
  vector<std::string> faces {
    "resources/skybox/right.jpg",
    "resources/skybox/left.jpg",
    "resources/skybox/top.jpg",
    "resources/skybox/bottom.jpg",
    "resources/skybox/front.jpg",
    "resources/skybox/back.jpg"
  };

  skybox = new Skybox(faces);
}


/*
* Añadir Fuentes de luz Aquí
*/
// setLights establece las propiedades de las fuentes de luz
void MarioCraft::renderLights() {
  int indice = shader_enum::SHADER_CORE_PROGRAM;
  shaders[indice]->use();
  // Simula la luz del sol.
  //Setup Advanced Lights
  shaders[indice]->setVec3("viewPos", camera->Position);
  shaders[indice]->setVec3("dirLight.direction", lightDirection);
  shaders[indice]->setVec3("dirLight.ambient", glm::vec3(1.0f, 1.0f, 1.0f)); // Tonalidad del ambiente, modifica las caras menos iluminadas
  shaders[indice]->setVec3("dirLight.diffuse", glm::vec3(0.0f, 0.0f, 0.0f)); // Color principal de la fuente de luz
  shaders[indice]->setVec3("dirLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));  // Brillo

  // Fuentes de luz posicionales
  shaders[indice]->setVec3("pointLight[0].position", lightPosition);
  shaders[indice]->setVec3("pointLight[0].ambient", glm::vec3(1.0f, 1.0f, 1.0f));
  shaders[indice]->setVec3("pointLight[0].diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
  shaders[indice]->setVec3("pointLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
  shaders[indice]->setFloat("pointLight[0].constant", 0.08f);
  shaders[indice]->setFloat("pointLight[0].linear", 0.009f); // Que tanto viaja la luz en el ambiente
  shaders[indice]->setFloat("pointLight[0].quadratic", 0.032f); // Intencidad de la fuente de luz
  
  shaders[indice]->setVec3("pointLight[1].position", glm::vec3(-80.0, 0.0f, 0.0f));
  shaders[indice]->setVec3("pointLight[1].ambient", glm::vec3(1.0f, 0.0f, 0.0f));
  shaders[indice]->setVec3("pointLight[1].diffuse", glm::vec3(1.0f, 0.0f, 0.0f));
  shaders[indice]->setVec3("pointLight[1].specular", glm::vec3(0.0f, 0.0f, 0.0f));
  shaders[indice]->setFloat("pointLight[1].constant", 1.0f);
  shaders[indice]->setFloat("pointLight[1].linear", 0.009f);
  shaders[indice]->setFloat("pointLight[1].quadratic", 0.032f);
  shaders[indice]->setFloat("material_shininess", 32.0f);

  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 tmp = glm::mat4(1.0f);
  // view/projection transformations
  ProjectionMatrix = glm::perspective(
    glm::radians(camera->Zoom), 
    (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 
    0.1f, 
    10000.0f
  );
  ViewMatrix = camera->GetViewMatrix();
  shaders[indice]->setMat4("projection", ProjectionMatrix);
  shaders[indice]->setMat4("view", ViewMatrix);
}

// renderSkybox renderiza el cielo
void MarioCraft::renderSkybox() {
  shaders[shader_enum::SHADER_SKYBOX]->use();
  shaders[shader_enum::SHADER_SKYBOX]->setInt("skybox", 0);
  skybox->Draw(
    *shaders[shader_enum::SHADER_SKYBOX], 
    ViewMatrix, 
    ProjectionMatrix, 
    *camera
  );
}

// renderModels renderiza todos los modelos creados
void MarioCraft::renderModels() {
  models->renderModels();
}

void MarioCraft::initModels() {

    models = new ModelManager();
    float altura = 3.5f;
    float coordenadasCasasToad[12][2] = {
        //Tres a lado de la carretera, alineados, a lado de las gallinas
        {-100.0f, -40.0f}, 
        {-100.0f, -10.0f},
        {-100.0f,  20.0f},

        //2 en medio de la carretera
        {-20.0f, -85.0f},
        {-50.0f, -35.0f},

        //Mini Villa de Champiñones 6 juntos en cuadrícula 3x2
        { 40.0f, -70.0f},
        { 40.0f, -30.0f},
        { 40.0f,  10.0f},
        { 80.0f, -70.0f},
        { 80.0f, -30.0f},
        { 80.0f,  10.0f},

        { 0.0f,  0.0f}
    };

    float coordenadasCasasMaicra1[2][2] = {
        {170.0f, 170.0f},
        { 80.0f, 50.0f}
    };

    float coordenadasCasasMaicra2[2][2] = {
        {-170.0f, 270.0f},
        {-60.0f,  100.0f}
    };

    //Escenario -------------------------------------------
    //
    StaticModel* escenario = new StaticModel("resources/objects/Escenario/Mariocraft.obj");
    escenario
        ->Init(glm::mat4(1.0f))
        ->Scale(15.0f, 15.0f, 15.0f);
    models->addModel(escenario);

    //Castillo -------------------------------------------
    //
    StaticModel* castillo = new StaticModel("resources/objects/Castillo/castillo.obj");
    castillo
        ->Init(glm::mat4(1.0f))
        ->Translate(10.0f, 44.0f, -238.0f)
        ->Scale(50.0f, 50.0f, 50.0f);
    models->addModel(castillo);

    // CasasTOAD -----------------------------------------
    //

    for (int i = 0; i < 12; i++) {
        StaticModel* casaToad = new StaticModel("resources/objects/CasaToad/casatoad.obj");
        casaToad
            ->Init(glm::mat4(1.0f))
            ->Translate(coordenadasCasasToad[i][0], altura, coordenadasCasasToad[i][1])
            ->Scale(10.0f, 10.0f, 10.0f);
        models->addModel(casaToad);
    }

    // Casas Minecraft // Buscar modelos más ligeros o quitar un poconón de vértices, mucha RAM
    /* for (int i = 0; i < 1; i++) {
        StaticModel* casa = new StaticModel("resources/objects/CasaMinecraft1/casa.obj");
        casa
            ->Init(glm::mat4(1.0f))
            ->Translate(coordenadasCasasMaicra1[i][0], 30.0f, coordenadasCasasMaicra1[i][1])
            ->Scale(2.0f, 2.0f, 2.0f);
        models->addModel(casa);
    }*/

    // Arboles

    //Antorchas



    //Kart1

    DynamicModel* kart1 = new Kart("resources/objects/Karts/Kart1/kart1.obj");
    kart1
        ->Init(glm::mat4(1.0f))
        ->Translate(30.0f, 30.0f, -180.0f)
        ->Scale(10.0f, 10.0f, 10.0f);
    models->addModel(kart1,DYNAMIC);

    D


}