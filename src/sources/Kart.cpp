#pragma once
#include "Kart.h"
#include "MarioCraft.h"
#include <GLM/gtx/string_cast.hpp>
//Listener
void Kart::animate() {
	int indice = shader_enum::SHADER_CORE_PROGRAM;

	model = glm::translate(glm::mat4(1.0f), glm::vec3(posicionInicial[0], posicionInicial[1], posicionInicial[2]));
	model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
	

	//model = glm::rotate(model, glm::radians(posicionInicial[0]), glm::vec3(0.0f, 1.0f, 0.0f));
	cout << glm::to_string(model) << " \n\n";
	this->posicionInicial[0] += 0.001f;
	this->posicionInicial[1] += 0.01f;
	this->posicionInicial[2] += 0.01f;

	Model::Draw(*MarioCraft::shaders[indice]);

}

void Kart::keyboardInput() {
	
}