
#pragma once
#include "Toad.h"
#include "MarioCraft.h"
//#include <GLM/gtx/string_cast.hpp>

Toad::Toad(string rutaObj) : DynamicModel(rutaObj + "/cuerpo.obj"){
	cuerpo = this;
	cabeza = new Model3D(rutaObj + "/cabeza.obj");
	brazoDer = new Model3D(rutaObj + "/brazoDer.obj");
	brazoIzq = new Model3D(rutaObj + "/brazoIzq.obj");
	pieDer = new Model3D(rutaObj + "/pieIzq.obj");
	pieIzq = new Model3D(rutaObj + "/pieDer.obj");
}


//Listener
void Toad::animate() {
	update();

	cuerpo->Init(glm::mat4(1.0f))
		->Translate(-28.0f + desplazamientoX, 14.2f + desplazamientoY, .0f + desplazamientoZ)
		->Rotate(anguloGiro, 0.f, 1.f, 0.f);

	cabeza->Init(cuerpo->model)
		->Translate(.127f, .254f, 0.f);

	brazoDer->Init(cuerpo->model)
		->Translate(0.11f, 0.f, 0.f)
		->Rotate(-45, 0.f, 0.f, 1.f)
		->Translate(-.6f, .75f, 0.f)
		->Rotate(-anguloBrazosPiernas, 0.f, 1.f, 0.f);

	brazoIzq->Init(cuerpo->model)
		->Translate(-0.11f, 0.f, 0.f)
		->Rotate(45, 0.f, 0.f, 1.f)
		->Translate(.6f, .5f, 0.f)
		->Rotate(-anguloBrazosPiernas, 0.f, 1.f, 0.f);

	pieDer->Init(cuerpo->model)
		->Translate(1.356f, -0.2f, 0.f)
		->Rotate(anguloBrazosPiernas, 1.f, 0.f, 0.f);

	pieIzq->Init(cuerpo->model)
		->Translate(-1.356f, -0.2f, -0.1f)
		->Rotate(-anguloBrazosPiernas, 1.f, 0.f, 0.f);

}

void Toad::update() {

	switch (estadoBrincar) {
	case Brincar::INICIO:
		anguloBrazosPiernas = 0.f;
		desplazamientoY = 0.f;
		estadoBrincar = Brincar::ESTADO_1;
		break;
	case Brincar::ESTADO_1:
		anguloBrazosPiernas += 1.f;
		desplazamientoY += .05f;
		if (anguloBrazosPiernas > 60)
			estadoBrincar = Brincar::ESTADO_2;
		break;
	case Brincar::ESTADO_2:
		anguloBrazosPiernas -= 1.f;
		desplazamientoY -= .05f;
		if (anguloBrazosPiernas < 0)
			estadoBrincar = Brincar::ESTADO_3;
		break;
	case Brincar::ESTADO_3:
		anguloBrazosPiernas -= 1.f;
		desplazamientoY += .05f;
		if (anguloBrazosPiernas < -60)
			estadoBrincar = Brincar::ESTADO_4;
		break;
	case Brincar::ESTADO_4:
		anguloBrazosPiernas += 1.f;
		desplazamientoY -= .05f;
		if (anguloBrazosPiernas > 0)
			estadoBrincar = Brincar::INICIO;
		break;
	}

	switch (estadoDesplazar) {
	case Desplazar::INICIO:
		desplazamientoZ = 0.f;
		desplazamientoX = 0.f;
		anguloGiro = 0.f;
		estadoDesplazar = Desplazar::AVANZAR_1;
		break;
	case Desplazar::AVANZAR_1:
		desplazamientoZ += .1f;
		if (desplazamientoZ > 28) {
			anguloGiro = 0.f;
			estadoDesplazar = Desplazar::VUELTA_1;
		}
		break;
	case Desplazar::VUELTA_1:
		anguloGiro -= 1;
		if (anguloGiro < -90) {
			estadoDesplazar = Desplazar::AVANZAR_2;
		}
		break;
	case Desplazar::AVANZAR_2:
		desplazamientoX -= .1f;
		if (desplazamientoX < -33)
			estadoDesplazar = Desplazar::VUELTA_2;
		break;
	case Desplazar::VUELTA_2:
		anguloGiro -= 1;
		if (anguloGiro < -180)
			estadoDesplazar = Desplazar::AVANZAR_3;
		break;
	case Desplazar::AVANZAR_3:
		desplazamientoZ -= .1f;
		if (desplazamientoZ < 0)
			estadoDesplazar = Desplazar::VUELTA_3;
		break;
	case Desplazar::VUELTA_3:
		anguloGiro -= 1;
		if (anguloGiro < -270)
			estadoDesplazar = Desplazar::AVANZAR_4;
		break;
	case Desplazar::AVANZAR_4:
		desplazamientoX += .1f;
		if (desplazamientoX > 0)
			estadoDesplazar = Desplazar::VUELTA_4;
		break;
	case Desplazar::VUELTA_4:
		anguloGiro -= 1;
		if (anguloGiro < -360)
			estadoDesplazar = Desplazar::INICIO;
		break;
	}
}

void Toad::keyboardInput() {

}

void Toad::renderModels() {
	cabeza->Draw();
	brazoDer->Draw();
	brazoIzq->Draw();
	pieDer->Draw();
	pieIzq->Draw();
}