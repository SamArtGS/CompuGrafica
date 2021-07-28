#pragma once
#include "creeper.h"
#include "MarioCraft.h"
//#include <GLM/gtx/string_cast.hpp>
Creeper::Creeper(string rutaObj) : DynamicModel(rutaObj + "/creeperbody.obj") {
	cuerpo = this;
	cabeza = new Model3D(rutaObj + "/creeperhead.obj");
	pieDerTras = new Model3D(rutaObj + "/creepeleg.obj");
	pieIzqTras = new Model3D(rutaObj + "/creepeleg.obj");
	pieDerDel = new Model3D(rutaObj + "/creepeleg.obj");
	pieIzqDel = new Model3D(rutaObj + "/creepeleg.obj");
}


//Listener
void Creeper::animate() {
	update();

	cuerpo->Init(glm::mat4(1.0f))
		->Translate(-25.0f + desplazamientoX, 12.2f + desplazamientoY, -75.0f + desplazamientoZ)
		->Rotate(anguloGiro, 0.f, 1.f, 0.f)
		->Scale(escala, escala, escala);

	cabeza->Init(cuerpo->model)
		->Translate(.0f, 0.0f, 0.f);

	pieDerDel->Init(cuerpo->model)
		->Translate(-0.7f, 1.1f, 0.7f)
		->Rotate(anguloPiernas, 1.f, 0.f, 0.f);

	pieIzqDel->Init(cuerpo->model)
		->Translate(0.0f, 1.1f, 0.7f)
		->Rotate(-anguloPiernas, 1.f, 0.f, 0.f);

	pieDerTras->Init(cuerpo->model)
		->Translate(-0.7f, 1.1f, -0.7f)
		->Rotate(-anguloPiernas, 1.f, 0.f, 0.f);

	pieIzqTras->Init(cuerpo->model)
		->Translate(0.0f, 1.1f, -0.7f)
	    ->Rotate(anguloPiernas, 1.f, 0.f, 0.f);

}

void Creeper::update() {
	if (explota == true) {
		if (estadoExplota == explotar::INICIO) {
			escala += 0.005f;
			if (escala > 1.1f) {
				estadoExplota = explotar::ESTADO_2;
			}
		}
		else {
			escala -= 0.005f;
			if (escala < 0.9f) {
				estadoExplota = explotar::INICIO;
			}
		}
	}

	if (estadoCaminar == Caminar::INICIO) {
		anguloPiernas += 1.0f;
		if (anguloPiernas > 30.0f) {
			estadoCaminar = Caminar::ESTADO_2;
		}
	}
	else {
		anguloPiernas -= 1.0f;
		if (anguloPiernas < -30.0f) {
			estadoCaminar = Caminar::INICIO;
		}
	}
	
	switch (estadoDesplazar) {
	case Desplazar::INICIO:
		desplazamientoZ = 0.f;
		desplazamientoX = 0.f;
		anguloGiro = 180.f;
		estadoDesplazar = Desplazar::AVANZAR_1;
		break;
	case Desplazar::AVANZAR_1:
		desplazamientoZ -= .1f;
		if (desplazamientoZ < -48) {
			anguloGiro = 90.f;
			estadoDesplazar = Desplazar::AVANZAR_2;
		}
		break;
	case Desplazar::AVANZAR_2:
		desplazamientoX += .1f;
		if (desplazamientoX > 15) {
			explota = true;
		}
		if (desplazamientoX > 27) {
			anguloGiro = 0.f;
			explota = false;
			escala = 1;
			estadoDesplazar = Desplazar::AVANZAR_3;
		}
		
		break;
	case Desplazar::AVANZAR_3:
		desplazamientoZ += .16f;
		if (desplazamientoZ > 103) {
			anguloGiro = -90.f;
			estadoDesplazar = Desplazar::AVANZAR_4;
		}
		break;
	case Desplazar::AVANZAR_4:
		desplazamientoX -= .16f;
		if (desplazamientoX < -125) {
			anguloGiro = 0.f;
			estadoDesplazar = Desplazar::AVANZAR_5;
		}
		break;
	case Desplazar::AVANZAR_5:
		desplazamientoZ += .16f;
		if (desplazamientoZ > 127) {
			anguloGiro = -90.f;
			estadoDesplazar = Desplazar::AVANZAR_6;
		}
		break;
	case Desplazar::AVANZAR_6:
		desplazamientoX -= .16f;
		if (desplazamientoX < -125) {
			anguloGiro = -90.f;
			estadoDesplazar = Desplazar::AVANZAR_7;
		}
		break;
	case Desplazar::AVANZAR_7:
		desplazamientoX -= .16f;
		if (desplazamientoX < -157) {
			anguloGiro = 180.f;
			estadoDesplazar = Desplazar::AVANZAR_8;
		}
		break;
	case Desplazar::AVANZAR_8:
		desplazamientoZ -= .16f;
		if (desplazamientoZ < 100) {
			anguloGiro = 90.f;
			estadoDesplazar = Desplazar::AVANZAR_9;
		}
		break;
	case Desplazar::AVANZAR_9:
		desplazamientoX += .16f;
		if (desplazamientoX > -125) {
			anguloGiro = 0.f;
			estadoDesplazar = Desplazar::AVANZAR_5;
		}
		break;
	}
	
}

void Creeper::keyboardInput() {

}

void Creeper::renderModels() {
	cabeza->Draw();
	pieDerTras->Draw();
	pieIzqTras->Draw();
	pieDerDel->Draw();
	pieIzqDel->Draw();

}