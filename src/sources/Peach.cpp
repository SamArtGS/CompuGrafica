#pragma once
#include "Peach.h"
#include "MarioCraft.h"
#include <time.h>
#include <ctime>
#include <GLM/gtx/string_cast.hpp>
using namespace std;
Peach::Peach(string rutaObj) : DynamicModel(rutaObj + "/PeachBody.obj") {
	cuerpo = this;
	cabeza = new Model3D(rutaObj + "/PeachHead.obj");
	brazoDer = new Model3D(rutaObj + "/PeachRarm.obj");
	brazoIzq = new Model3D(rutaObj + "/PeachLarm.obj");
	pieDer = new Model3D(rutaObj + "/PeachRleg.obj");
	pieIzq = new Model3D(rutaObj + "/PeachLleg.obj");
}

//Listener
void Peach::animate() {
	update();

	cuerpo->Init(glm::mat4(1.0f))
		->Translate(+17.0f + desplazamientoX, 13.0f + desplazamientoY, -170.0f + desplazamientoZ)
		->Rotate(anguloGiro, 0.f, 1.f, 0.f)
		-> Scale(escala+0.04f, escala+0.04f, escala+0.04f)
		->Rotate(anguloCuerpoX, 1.f, 0.f, 0.f)
		->Rotate(anguloCuerpoZ, 0.f, 0.f, 1.f);

	cabeza->Init(cuerpo->model)
		->Translate(0.f, +135.0f, -5.f)
		->Rotate(anguloCabeza, 1.f, 0.f, 0.f);
		

	brazoDer->Init(cuerpo->model)
		->Translate(70.0f, +35.f, 0.0f)
		->Rotate(+90, 0.f, 1.f, 0.f)
		->Rotate(-45, 1.f, 0.f, 0.f)
		->Rotate(anguloBrazos, 0.f, 1.f, 0.f)
		->Rotate(anguloBrazosCaminar, 0.f, 1.f, 0.f);

	brazoIzq->Init(cuerpo->model)
		->Translate(-70.0f, 35.f, 0.0f)
		->Rotate(-90, 0.f, 1.f, 0.f)
		->Rotate(-45, 1.f, 0.f, 0.f)
		->Rotate(anguloBrazos, 0.f, 1.f, 0.f)
		->Rotate(-anguloBrazosCaminar, 0.f, 0.1f, 0.f);

	pieDer->Init(cuerpo->model)
		->Translate(-2.0f, +30.0f, 0.f)
		->Rotate(anguloPiernas, 1.f, 0.f, 0.f)
		->Rotate(-anguloPiernasdescanso, 1.f, 0.f, 0.f);

	pieIzq->Init(cuerpo->model)
		->Translate(2.0f, +30.0f, 0.0f)
		->Rotate(-anguloPiernas, 1.f, 0.f, 0.f)
		->Rotate(-anguloPiernasdescanso, 1.f, 0.f, 0.f);

}

void Peach::update() {
	if (correr == true) {
		anguloCuerpoX = 20;
		if (estadoCorrer == Correr::INICIO) {
			anguloPiernas += 2.0f;
			if (anguloPiernas > 50.0f) {
				estadoCorrer = Correr::ESTADO_2;
			}
		}
		if (estadoCorrer == Correr::ESTADO_2) {
			anguloPiernas -= 2.0f;
			if (anguloPiernas < -50.0f) {
				estadoCorrer = Correr::INICIO;
			}
		}
		if (estadoCorrerArms == Correr::INICIOARMS) {
			anguloBrazos += 1.6f;
			if (anguloBrazos > 40.0f) {
				estadoCorrerArms = Correr::ESTADO_3;
			}
		}
		if (estadoCorrerArms == Correr::ESTADO_3) {
			anguloBrazos -= 1.6f;
			if (anguloBrazos < -40.0f) {
				estadoCorrerArms = Correr::INICIOARMS;
			}
		}
		if (estadoCorrerBody == Correr::INICIOBODY) {
			anguloCuerpoZ += 0.2f;
			if (anguloCuerpoZ > 5.0f) {
				estadoCorrerBody = Correr::ESTADO_1;
			}
		}
		if (estadoCorrerBody == Correr::ESTADO_1) {
			anguloCuerpoZ -= 0.2f;
			if (anguloCuerpoZ < -5.0f) {
				estadoCorrerBody = Correr::INICIOBODY;
			}
		}
	}

	if (caminar == true) {
		anguloBrazosCaminar = -50;
		if (estadoCaminar == Caminar::INICIO) {
			anguloPiernas += 0.5f;
			if (anguloPiernas > 20.0f) {
				estadoCaminar = Caminar::ESTADO_1;
			}
		}
		if (estadoCaminar == Caminar::ESTADO_1) {
			anguloPiernas -= 0.5f;
			if (anguloPiernas < -20.0f) {
				estadoCaminar = Caminar::INICIO;
			}
		}
		if (estadoCaminarArms == Caminar::INICIOARMS) {
			anguloBrazos += .5f;
			if (anguloBrazos > 20.0f) {
				estadoCaminarArms = Caminar::ESTADO_3;
			}
		}
		if (estadoCaminarArms == Caminar::ESTADO_3) {
			anguloBrazos -= .5f;
			if (anguloBrazos < -20.0f) {
				estadoCaminarArms = Caminar::INICIOARMS;
			}
		}
	}
	if (subir == true){
		anguloCuerpoX = -0;
		anguloBrazosCaminar = 0;
		if (estadoCaminarArms == Caminar::INICIOARMS) {
			anguloBrazos += .5f;
			if (anguloBrazos > 20.0f) {
				estadoCaminarArms = Caminar::ESTADO_3;
			}
		}
		if (estadoCaminarArms == Caminar::ESTADO_3) {
			anguloBrazos -= .5f;
			if (anguloBrazos < -20.0f) {
				estadoCaminarArms = Caminar::INICIOARMS;
			}
		}
	}

	if (asustar == true) {
		anguloBrazosCaminar = 30;
		if (estadoCaminar == Caminar::INICIO) {
			anguloPiernas += 0.5f;
			if (anguloPiernas > 20.0f) {
				estadoCaminar = Caminar::ESTADO_1;
			}
		}
		if (estadoCaminar == Caminar::ESTADO_1) {
			anguloPiernas -= 0.5f;
			if (anguloPiernas < -20.0f) {
				estadoCaminar = Caminar::INICIO;
			}
		}
		if (estadoCaminarArms == Caminar::INICIOARMS) {
			anguloBrazos += .5f;
			if (anguloBrazos > 20.0f) {
				estadoCaminarArms = Caminar::ESTADO_3;
			}
		}
		if (estadoCaminarArms == Caminar::ESTADO_3) {
			anguloBrazos -= .5f;
			if (anguloBrazos < -20.0f) {
				estadoCaminarArms = Caminar::INICIOARMS;
			}
		}
	}
	if (subir == true) {
		anguloCuerpoX = -0;
		anguloBrazosCaminar = 0;
		if (estadoCaminarArms == Caminar::INICIOARMS) {
			anguloBrazos += .5f;
			if (anguloBrazos > 20.0f) {
				estadoCaminarArms = Caminar::ESTADO_3;
			}
		}
		if (estadoCaminarArms == Caminar::ESTADO_3) {
			anguloBrazos -= .5f;
			if (anguloBrazos < -20.0f) {
				estadoCaminarArms = Caminar::INICIOARMS;
			}
		}
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
		if (desplazamientoZ > 10) {
			estadoDesplazar = Desplazar::AVANZAR_2;
		}
		break;
	case Desplazar::AVANZAR_2:
		desplazamientoZ += .1f;
		desplazamientoY += .03f;
		if (desplazamientoZ > 20) {
			estadoDesplazar = Desplazar::AVANZAR_3;
		}
		break;
	case Desplazar::AVANZAR_3:
		desplazamientoZ += .08f;
		desplazamientoY -= .012f;
		if (desplazamientoZ > 40) {
			anguloGiro = -40.f;
			estadoDesplazar = Desplazar::AVANZAR_4;
		}
		break;
	case Desplazar::AVANZAR_4:
		desplazamientoZ += .08f;
		desplazamientoX -= .13f;
		if (desplazamientoZ > 49) {
			anguloGiro = 0.f;
			caminar = false;
			correr = true;
			estadoDesplazar = Desplazar::AVANZAR_5;
		}
		break;
	case Desplazar::AVANZAR_5:
		desplazamientoZ += .16f;
		if (desplazamientoZ > 198) {
			anguloGiro = -90.f;
			estadoDesplazar = Desplazar::AVANZAR_6;
		}
		break;
	case Desplazar::AVANZAR_6:
		desplazamientoX -= .16f;
		if (desplazamientoX < -100) {
			anguloGiro = -80.f;
			estadoDesplazar = Desplazar::AVANZAR_7;
		}
		break;
	case Desplazar::AVANZAR_7:
		desplazamientoX -= .16f;
		desplazamientoZ += 0.023f;
		if (desplazamientoX < -168) {
			estadoDesplazar = Desplazar::AVANZAR_8;
		}
		break;
	case Desplazar::AVANZAR_8:
		desplazamientoX -= .16f;
		desplazamientoZ += 0.023f;
		desplazamientoY += 0.09f;
		if (desplazamientoX < -174) {
			anguloGiro = -90.f;
			estadoDesplazar = Desplazar::AVANZAR_9;
		}
	case Desplazar::AVANZAR_9:
		desplazamientoX -= .16f;
		desplazamientoZ += 0.006f;
		if (desplazamientoX < -189) {
			anguloGiro = -90.f;
			estadoDesplazar = Desplazar::AVANZAR_10;
			correr = false;
			subir = true;
		}
		break;
	case Desplazar::AVANZAR_10:
		desplazamientoY += 0.1f;
		if (desplazamientoY > 35) {
			anguloGiro = 90.f;
			estadoDesplazar = Desplazar::AVANZAR_11;
		}
		break;
	case Desplazar::AVANZAR_11:
		desplazamientoY -= 0.06f;
		desplazamientoX += .16f;
		if (desplazamientoX > -185) {
			anguloGiro = 90.f;
			estadoDesplazar = Desplazar::AVANZAR_12;
			subir = false;
			caminar = true;
		}
		break;
	case Desplazar::AVANZAR_12:
		desplazamientoX += .16f;
		if (desplazamientoX > -168) {
			anguloGiro = 0.f;
			estadoDesplazar = Desplazar::AVANZAR_13;
			anguloBrazosCaminar = -50;
			caminar = false;
			asustar = true;
		}
		break;
	case Desplazar::AVANZAR_13:
		desplazamientoZ += .16f;
		if (desplazamientoZ > 215) {
			anguloGiro = 180.f;
			estadoDesplazar = Desplazar::AVANZAR_14;
		}
		break;
	case Desplazar::AVANZAR_14:
		desplazamientoZ -= .16f;
		if (desplazamientoZ < 204) {
			anguloGiro = 0.f;
			estadoDesplazar = Desplazar::AVANZAR_13;
		}
		break;
	}

}

void Peach::delay(int secs) {
	for (int i = (time(NULL) + secs); time(NULL) != i; time(NULL));
}

void Peach::keyboardInput() {

}

void Peach::renderModels() {
	cabeza->Draw();
	brazoDer->Draw();
	brazoIzq->Draw();
	pieDer->Draw();
	pieIzq->Draw();
}