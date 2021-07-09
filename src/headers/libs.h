#pragma once
#include <Windows.h>

#include <glad.h>
#include <glfw3.h>

#include <glm.hpp>
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include "camera.h"
#include "shader_m.h"
#include "Model3D.h"
#include "DymanicModel.h"
#include "ModelManager.h"

#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>