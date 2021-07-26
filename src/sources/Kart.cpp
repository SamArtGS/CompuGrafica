#pragma once
#include "Kart.h"
#include "MarioCraft.h"
#include "sound.h"
#include <GLM/gtx/string_cast.hpp>
//Listener


void Kart::animate() {
	if (salida){
		float incrementos[3] = { 0.0f,0.0f, 0.0f };
		switch ((int)distancias[posicion][0]) {
			case 12:
				incrementos[0] = posicionDesplazamiento[0];
				incrementos[1] = posicionDesplazamiento[1];
				incrementos[2] = posicionDesplazamiento[2] - incremento;
				break;
			case 1:
				incrementos[0] = posicionDesplazamiento[0] + incremento / 2;
				incrementos[1] = posicionDesplazamiento[1];
				incrementos[2] = posicionDesplazamiento[2] - incremento;
				break;
			case 2:
				incrementos[0] = posicionDesplazamiento[0] + incremento;
				incrementos[1] = posicionDesplazamiento[1];
				incrementos[2] = posicionDesplazamiento[2] - incremento / 2;
				break;
			case 3:
				incrementos[0] = posicionDesplazamiento[0] + incremento;
				incrementos[1] = posicionDesplazamiento[1];
				incrementos[2] = posicionDesplazamiento[2];
				break;
			case 4:
				incrementos[0] = posicionDesplazamiento[0] + incremento;
				incrementos[1] = posicionDesplazamiento[1];
				incrementos[2] = posicionDesplazamiento[2] + incremento / 2;
				break;
			case 5:
				incrementos[0] = posicionDesplazamiento[0] + incremento / 2;
				incrementos[1] = posicionDesplazamiento[1];
				incrementos[2] = posicionDesplazamiento[2] + incremento;
				break;
			case 6:
				incrementos[0] = posicionDesplazamiento[0];
				incrementos[1] = posicionDesplazamiento[1];
				incrementos[2] = posicionDesplazamiento[2] + incremento;
				break;
			case 7:
				incrementos[0] = posicionDesplazamiento[0] - incremento / 2;
				incrementos[1] = posicionDesplazamiento[1];
				incrementos[2] = posicionDesplazamiento[2] + incremento / 2;
				break;
			case 8:
				incrementos[0] = posicionDesplazamiento[0] - incremento / 2;
				incrementos[1] = posicionDesplazamiento[1];
				incrementos[2] = posicionDesplazamiento[2] + incremento;
				break;
			case 9:
				incrementos[0] = posicionDesplazamiento[0] - incremento;
				incrementos[1] = posicionDesplazamiento[1];
				incrementos[2] = posicionDesplazamiento[2];
				break;
			case 10:
				incrementos[0] = posicionDesplazamiento[0] + incremento;
				incrementos[1] = posicionDesplazamiento[1];
				incrementos[2] = posicionDesplazamiento[2];
				break;
			case 11:
				incrementos[0] = posicionDesplazamiento[0] + incremento;
				incrementos[1] = posicionDesplazamiento[1];
				incrementos[2] = posicionDesplazamiento[2];
				break;
			default:
				break;
			}
			if (incremento >= distancias[posicion][1]) {
				incremento = 0.0f;
				if (posicion >= sizeof(distancias) / sizeof(distancias[0])) {
					posicion = 0;

					posicionDesplazamiento[0] = posicionInicial[0];
					posicionDesplazamiento[1] = posicionInicial[1];
					posicionDesplazamiento[2] = posicionInicial[2];
					salida = false;
				}
				else {
					posicion++;
					posicionDesplazamiento[0] = incrementos[0];
					posicionDesplazamiento[1] = incrementos[1];
					posicionDesplazamiento[2] = incrementos[2];
				}
			}
			else {
				incremento += velocidad;
			}

			model = glm::translate(glm::mat4(1.0f),
				glm::vec3(incrementos[0],
						  incrementos[1],
						  incrementos[2]
				)
			);

			float direccion = distancias[posicion][0] == 12 ? 0 : distancias[posicion][0] * 30.0;
			model = glm::rotate(model, glm::radians(180 - direccion), glm::vec3(0.0f, 1.0f, 0.0f));

			model = glm::scale(model,
				glm::vec3(1.0f, 1.0f, 1.0f)
			);
	}else{
		model = glm::translate(glm::mat4(1.0f),glm::vec3(posicionInicial[0],posicionInicial[1],posicionInicial[2]));
		model = glm::rotate(model, glm::radians(172.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model,glm::vec3(1.0f, 1.0f, 1.0f));
	}
}

void Kart::keyboardInput() {
	if (glfwGetKey(MarioCraft::window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		if (salida == false) {
			sound* iniCarrera = new sound();
			iniCarrera->sonido("./resources/sounds/coint.wav");
			iniCarrera->playSound(100);
		}
		salida = true;
	}
}

void Kart::renderModels() {
	
}

Model3D* Kart::Translate(float tX, float tY, float tZ){
	Model3D* extraModel = __super::Translate(tX,tY,tZ);
	int posAux[3] = { tX,tY,tZ };
	std::copy(posAux, posAux + 3, posicionInicial);
	std::copy(posAux, posAux + 3, posicionDesplazamiento);
	return extraModel;
}
