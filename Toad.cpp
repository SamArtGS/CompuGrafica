
#pragma once
#include "Toad.h"
#include "MarioCraft.h"
#include <GLM/gtx/string_cast.hpp>
//Listener
void Toad::animate() {
	int indice = shader_enum::SHADER_CORE_PROGRAM;

	//model = glm::translate(glm::mat4(1.0f), glm::vec3(posicionInicial[0], posicionInicial[1], posicionInicial[2]));
	//model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));

	Model::Draw(*MarioCraft::shaders[indice]);

}

void Toad::keyboardInput() {

}