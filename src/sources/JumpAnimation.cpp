
#pragma once
#include "JumpAnimation.h"
#include "MarioCraft.h"

JumpAnimation::JumpAnimation(string rutaObj, float xInit, float yInit, float zInit, float yRotInit)
	: DynamicModel(rutaObj + "/cuerpo.obj"){
	cuerpo = this;
	cabeza = new Model3D(rutaObj + "/cabeza.obj");
	brazoDer = new Model3D(rutaObj + "/brazoDer.obj");
	brazoIzq = new Model3D(rutaObj + "/brazoIzq.obj");
	pieDer = new Model3D(rutaObj + "/pieIzq.obj");
	pieIzq = new Model3D(rutaObj + "/pieDer.obj");
	this->xInit = xInit;
	this->yInit = yInit;
	this->zInit = zInit;
	this->yRotInit = yRotInit;
}


//Listener
void JumpAnimation::animate() {
	update();

	cuerpo->Init(glm::mat4(1.0f))
		->Translate(xInit + desplazamientoX, yInit + desplazamientoY, zInit + desplazamientoZ)
		->Rotate(yRotInit + anguloGiro, 0.f, 1.f, 0.f);

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

void JumpAnimation::update() {

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

	switch (estadoAnimacion.estado) {
	case Desplazamiento::INICIO:
		desplazamientoX = desplazamientoZ = 0.f;
		deltaX = deltaZ = 0.f;
		anguloGiro = 0.f;
		deltaGiro = 0.f;
		siguienteMovimiento();
		break;
	case Desplazamiento::NORTE:
		deltaZ -= estadoAnimacion.delta;
		desplazamientoZ -= estadoAnimacion.delta;
		if (deltaZ < -estadoAnimacion.limite) {
			deltaZ = 0.f;
			siguienteMovimiento();
		}
		break;
	case Desplazamiento::SUR:
		deltaZ += estadoAnimacion.delta;
		desplazamientoZ += estadoAnimacion.delta;
		if (deltaZ > estadoAnimacion.limite) {
			deltaZ = 0.f;
			siguienteMovimiento();
		}
		break;
	case Desplazamiento::ESTE:
		deltaX += estadoAnimacion.delta;
		desplazamientoX += estadoAnimacion.delta;
		if (deltaX > estadoAnimacion.limite) {
			deltaX = 0.f;
			siguienteMovimiento();
		}
		break;
	case Desplazamiento::OESTE:
		deltaX -= estadoAnimacion.delta;
		desplazamientoX -= estadoAnimacion.delta;
		if (deltaX < -estadoAnimacion.limite) {
			deltaX = 0.f;
			siguienteMovimiento();
		}
		break;
	case Desplazamiento::GIRO_DERECHA:
		deltaGiro -= estadoAnimacion.delta;
		anguloGiro -= estadoAnimacion.delta;
		if (deltaGiro < -estadoAnimacion.limite) {
			deltaGiro = 0.f;
			siguienteMovimiento();
		}
		break;
	case Desplazamiento::GIRO_IZQUIERDA:
		deltaGiro += estadoAnimacion.delta;
		anguloGiro += estadoAnimacion.delta;
		if (deltaGiro > estadoAnimacion.limite) {
			deltaGiro = 0.f;
			siguienteMovimiento();
		}
		break;
	}
}

void JumpAnimation::siguienteMovimiento() {
	estadoAnimacion = animaciones[i++];
	if (i == animaciones.size()) i = 0;
}

JumpAnimation* JumpAnimation:: addEstadoAnimacion(Desplazamiento estado, float delta, float limite) {
	AnimacionBrincar animacion;
	animacion.estado = estado;
	animacion.delta = delta;
	animacion.limite = limite;
	animaciones.push_back(animacion);
	return this;
}

void JumpAnimation::setEstadosAnimacion(vector<AnimacionBrincar> animaciones) {
	this->animaciones = animaciones;
}


void JumpAnimation::renderModels() {
	cabeza->Draw();
	brazoDer->Draw();
	brazoIzq->Draw();
	pieDer->Draw();
	pieIzq->Draw();
}