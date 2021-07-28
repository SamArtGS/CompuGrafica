#include "Golem.h"

Golem::Golem(string rutaObj,Tipo a, TipoMovimiento tipoMov) : MobMinecraft(rutaObj, a, tipoMov) {
	creeper->Init(glm::mat4(1.0f))
		->Translate(posicionInicial[0], posicionInicial[1], posicionInicial[2])
		->Scale(0.7f,0.7f,0.7f);
	posicionCreeper[0] = 1;
	posicionCreeper[1] = 1;
	posicionCreeper[2] = 1;

	
}

void Golem::animate() {
	this->Translate(0, 0, 0);
	if (retardo >= 0) {
		brazoDer->Init(this->model);
		brazoIzq->Init(this->model);
		pieIzq->Init(this->model);
		pieDer->Init(this->model);
		retardo--;
		return;
	}
	switch (estado) {
	case Golem::Estado::caminando:
		caminar();
		break;
	case Golem::Estado::matando:

		break;
	case Golem::Estado::saltando:
		break;
	default:
		break;
	}
}
void Golem::keyboardInput() {
	
}

void Golem::matarZombie() {
	
}

