#pragma once
#include "Dragon.h"
#include "MarioCraft.h"

Dragon::Dragon(string rutaObj, float xInit, float yInit, float zInit, float yRotInit)
	: DynamicModel(rutaObj + "/cuerpo.obj") {
	cuerpo = this;
	cabeza = new Model3D(rutaObj + "/cabeza.obj");
	colaParte1 = new Model3D(rutaObj + "/cola.obj");
	colaParte2 = new Model3D(rutaObj + "/cola.obj");
	colaParte3 = new Model3D(rutaObj + "/cola.obj");
	colaParte4 = new Model3D(rutaObj + "/cola.obj");
	magmaCube = new Model3D(rutaObj + "/magmaCube.obj");
	musloAlaDerecha = new Model3D(rutaObj + "/musloAlaDerecha.obj");
	alaDerecha = new Model3D(rutaObj + "/alaDerecha.obj");
	musloAlaIzquierda = new Model3D(rutaObj + "/musloAlaIzquierda.obj");
	alaIzquierda = new Model3D(rutaObj + "/alaIzquierda.obj");
	bocaSuperior = new Model3D(rutaObj + "/bocaSuperior.obj");
	bocaInferior = new Model3D(rutaObj + "/bocaInferior.obj");
	musloDerecho = new Model3D(rutaObj + "/muslo.obj");
	piernaDerecha = new Model3D(rutaObj + "/pierna.obj");
	pataDerecha = new Model3D(rutaObj + "/pata.obj");
	musloIzquierdo = new Model3D(rutaObj + "/muslo.obj");
	piernaIzquierda = new Model3D(rutaObj + "/pierna.obj");
	pataIzquierda = new Model3D(rutaObj + "/pata.obj");
	manoDerecha = new Model3D(rutaObj + "/manos.obj");
	manoIzquierda = new Model3D(rutaObj + "/manos.obj");
	this->xInit = xInit;
	this->yInit = yInit;
	this->zInit = zInit;
	this->yRotInit = yRotInit;
}

//Listener
void Dragon::animate() {
	update();

	cuerpo->Init(glm::mat4(1.0f))
		->Translate(xInit + desplazamientoX, yInit + desplazamientoY, zInit + desplazamientoZ)
		->Rotate(yRotInit + anguloGiro, 0.f, 1.f, 0.f);

	cabeza->Init(cuerpo->model)
		->Translate(0.f, 0.38f, 9.85f)
		->Rotate(anguloVerticalCabeza, 1.f, 0.f, 0.f)
		->Rotate(anguloHorizontalCabeza, 0.f, 1.f, 0.f);

	bocaSuperior->Init(cabeza->model)
		->Translate(0.f, -0.86f, 5.65f)
		->Rotate(-anguloBoca, 1.f, 0.f, 0.f);

	bocaInferior->Init(cabeza->model)
		->Translate(0.f, -1.46f, 5.65f)
		->Rotate(anguloBoca, 1.f, 0.f, 0.f);

	musloAlaDerecha->Init(cuerpo->model)
		->Translate(1.3f, .8f, 2.9f)
		->Rotate(anguloMuslo, 0.f, 0.f, 1.f);

	alaDerecha->Init(musloAlaDerecha->model)
		->Translate(8.232f, 2.459f, -1.5f)
		->Rotate(10, 0.f, 1.f, 0.f)
		->Rotate(anguloAla, 0.f, 0.f, 1.f);

	musloAlaIzquierda->Init(cuerpo->model)
		->Translate(-1.2f, .8f, 2.9f)
		->Rotate(-anguloMuslo, 0.f, 0.f, 1.f);

	alaIzquierda->Init(musloAlaIzquierda->model)
		->Translate(-8.232f, 2.459f, -1.5f)
		->Rotate(-10, 0.f, 1.f, 0.f)
		->Rotate(-anguloAla, 0.f, 0.f, 1.f);

	colaParte1->Init(cuerpo->model)
		->Translate(.0f, -.31f, -5.155f)
		->Rotate(anguloColaX, 1.f, 0.f, 0.f);

	colaParte2->Init(colaParte1->model)
		->Translate(.0f, 0.f, -4.7f)
		->Rotate(-anguloColaX, 1.f, 0.f, 0.f)
		->Rotate(-anguloColaY, 0.f, 1.f, 0.f);

	colaParte3->Init(colaParte2->model)
		->Translate(.0f, 0.f, -4.7f)
		->Rotate(anguloColaX, 1.f, 0.f, 0.f);
	
	colaParte4->Init(colaParte3->model)
		->Translate(.0f, 0.f, -4.7f)
		->Rotate(anguloColaX, 1.f, 0.f, 0.f)
		->Rotate(-anguloColaY, 0.f, 1.f, 0.f);

	musloDerecho->Init(cuerpo->model)
		->Translate(1.8f, 0.f, -2.5f)
		->Rotate(-5 + anguloMusloPiernas, 1.f, 0.f, 0.f);

	piernaDerecha->Init(musloDerecho->model)
		->Translate(0.f, -2.1f, -4.3f)
		->Rotate(anguloPiernas, 1.f, 0.f, 0.f);

	pataDerecha->Init(piernaDerecha->model)
		->Translate(0.f, 0.f, -4.85f)
		->Rotate(anguloPatas, 1.f, 0.f, 0.f);

	musloIzquierdo->Init(cuerpo->model)
		->Translate(-1.8f, 0.f, -2.5f)
		->Rotate(-10 + anguloMusloPiernas, 1.f, 0.f, 0.f);

	piernaIzquierda->Init(musloIzquierdo->model)
		->Translate(0.f, -2.1f, -4.3f)
		->Rotate(anguloPiernas, 1.f, 0.f, 0.f);

	pataIzquierda->Init(piernaIzquierda->model)
		->Translate(0.f, 0.f, -4.85f)
		->Rotate(anguloPatas, 1.f, 0.f, 0.f);

	manoDerecha->Init(cuerpo->model)
		->Translate(1.8f, -1.4f, 1.f)
		->Rotate(-10 + anguloManos, 1.f, 0.f, 0.f);

	manoIzquierda->Init(cuerpo->model)
		->Translate(-1.8f, -1.4f, 1.f)
		->Rotate(anguloManos, 1.f, 0.f, 0.f);
}

void Dragon::update() {

	// Animación de las alas
	switch (estadoAlas) {
	case (Alas::INICIO):
		anguloMuslo = anguloAla = anguloColaX = 0.f;
		anguloMusloPiernas = 0.f;
		anguloPiernas = -20.f;
		anguloPatas = -20.f;
		anguloManos = 0.f;
		desplazamientoY = 0.f;
		estadoAlas = Alas::ALETEAR_ARRIBA;
		break;
	case (Alas::ALETEAR_ARRIBA):
		desplazamientoY += 0.2f;
		anguloMuslo += 1.f;
		anguloAla += 1.3f;
		anguloColaX -= .5f;
		anguloMusloPiernas += 0.2f;
		anguloPiernas += 0.3f;
		anguloPatas += .7f;
		anguloManos -= 0.6f;
		if (anguloMuslo > 45) {
			estadoAlas = Alas::ALETEAR_ABAJO;
		}
		break;
	case (Alas::ALETEAR_ABAJO):
		desplazamientoY -= 0.2f;
		anguloMuslo -= 1.f;
		anguloAla -= 1.3f;
		anguloColaX += .5f;
		anguloMusloPiernas -= 0.2f;
		anguloPiernas -= 0.3f;
		anguloPatas -= .7f;
		anguloManos += 0.6f;
		if (anguloMuslo < -20)
			estadoAlas = Alas::ALETEAR_ARRIBA;
		break;
	}

	// Mover Dragón por el escenario
	switch (estadoAnimacion.estado) {
	case MoviemientosDragon::INICIO:
		desplazamientoX = desplazamientoZ = 0.f;
		deltaX = deltaZ = 0.f;
		anguloGiro = anguloColaY = 0.f;
		deltaGiro = 0.f;
		siguienteMovimiento();
		break;
	case MoviemientosDragon::NORTE:
		deltaZ -= estadoAnimacion.delta;
		desplazamientoZ -= estadoAnimacion.delta;
		if (deltaZ <= -estadoAnimacion.limite) {
			deltaZ = 0.f;
			siguienteMovimiento();
		}
		break;
	case MoviemientosDragon::SUR:
		deltaZ += estadoAnimacion.delta;
		desplazamientoZ += estadoAnimacion.delta;
		if (deltaZ >= estadoAnimacion.limite) {
			deltaZ = 0.f;
			siguienteMovimiento();
		}
		break;
	case MoviemientosDragon::ESTE:
		deltaX += estadoAnimacion.delta;
		desplazamientoX += estadoAnimacion.delta;
		if (deltaX >= estadoAnimacion.limite) {
			deltaX = 0.f;
			siguienteMovimiento();
		}
		break;
	case MoviemientosDragon::OESTE:
		deltaX -= estadoAnimacion.delta;
		desplazamientoX -= estadoAnimacion.delta;
		if (deltaX <= -estadoAnimacion.limite) {
			deltaX = 0.f;
			siguienteMovimiento();
		}
		break;
	case MoviemientosDragon::GIRO_DERECHA:
		deltaGiro -= estadoAnimacion.delta;
		anguloGiro -= estadoAnimacion.delta;
		if (deltaGiro < -estadoAnimacion.limite / 2)
			anguloColaY += .5f;
		else
			anguloColaY -= .5f;
		if (deltaGiro <= -estadoAnimacion.limite) {
			deltaGiro = 0.f;
			anguloColaY = 0.f;
			siguienteMovimiento();
		}
		break;
	case MoviemientosDragon::GIRO_IZQUIERDA:
		deltaGiro += estadoAnimacion.delta;
		anguloGiro += estadoAnimacion.delta;
		if (deltaGiro > estadoAnimacion.limite / 2)
			anguloColaY -= .5f;
		else
			anguloColaY += .5f;
		if (deltaGiro >= estadoAnimacion.limite) {
			deltaGiro = 0.f;
			anguloColaY = 0.f;
			siguienteMovimiento();
		}
		break;
	}

	// Animación de la Boca del Dragón
	switch (estadoBoca) {
	case Boca::INICIO:
		if(estadoMagma == Magma::INICIO and rand() % 300 == 1)
			estadoBoca = Boca::BAJAR;
		break;
	case Boca::BAJAR:
		anguloVerticalCabeza += 1.f;
		if (anguloVerticalCabeza > 30) {
			if (rand() % 2 == 0)
				estadoBoca = Boca::DERECHA;
			else
				estadoBoca = Boca::IZQUIERDA;
		}
		break;
	case Boca::DERECHA:
		anguloHorizontalCabeza += 1.f;
		if (anguloHorizontalCabeza > 30) {
			estadoMagma = Magma::LANZAR;
			estadoBoca = Boca::ABRIR;
		}
		break;
	case Boca::IZQUIERDA:
		anguloHorizontalCabeza -= 1.f;
		if (anguloHorizontalCabeza < -30) {
			estadoMagma = Magma::LANZAR;
			estadoBoca = Boca::ABRIR;
		}
		break;
	case Boca::ABRIR:
		anguloBoca += 1.f;
		if (anguloBoca > 30)
			estadoBoca = Boca::CERRAR;
		break;
	case Boca::CERRAR:
		anguloBoca -= 1.f;
		if (anguloBoca < 0)
			estadoBoca = Boca::CENTRO;
		break;
	case Boca::CENTRO:
		if (anguloHorizontalCabeza == 0)
			estadoBoca = Boca::SUBIR;
		else if (anguloHorizontalCabeza > 0)
			anguloHorizontalCabeza -= 1.f;
		else
			anguloHorizontalCabeza += 1.f;
		break;
	case Boca::SUBIR:
		anguloVerticalCabeza -= 1.f;
		if (anguloVerticalCabeza < 0)
			estadoBoca = Boca::INICIO;
		break;
	}

	switch (estadoMagma){
	case Magma::INICIO:
		magmaY = 0.f;
		magmaCube->Init(glm::mat4(0.0f));
		break;
	case Magma::LANZAR:
		magmaAux = cabeza->model;
		magmaCube->Init(magmaAux)
			->Translate(0.f, -1.f, 5.65f)
			->Scale(0.15f, 0.15f, 0.15f);
		estadoMagma = Magma::ACTUALIZAR;
		break;
	case Magma::ACTUALIZAR:
		magmaY -= 1.f;
		magmaCube->Translate(0.f, -.5f, 7.f);
		if (magmaY < -magmaAux[3][1])
			estadoMagma = Magma::INICIO;
		break;
	}
}

// siguienteMovimiento actualiza la variable estadoMovimiento
// simula una lista circular donde si se llega al final del vector, 
// se regresa a la posicion 0 (reiniciar animación)
void Dragon::siguienteMovimiento() {
	estadoAnimacion = animaciones[i++];
	if (i == animaciones.size()) i = 0;
}

Dragon* Dragon::addEstadoAnimacion(MoviemientosDragon estado, float delta, float limite) {
	Animacion animacion;
	animacion.estado = estado;
	animacion.delta = delta;
	animacion.limite = limite;
	animaciones.push_back(animacion);
	return this;
}

void Dragon::setEstadosAnimacion(vector<Animacion> animaciones) {
	this->animaciones = animaciones;
}


void Dragon::keyboardInput() {

}

void Dragon::renderModels() {
	cabeza->Draw();
	colaParte1->Draw();
	colaParte2->Draw();
	colaParte3->Draw();
	colaParte4->Draw();
	magmaCube->Draw();
	musloAlaDerecha->Draw();
	alaDerecha->Draw();
	musloAlaIzquierda->Draw();
	alaIzquierda->Draw();
	bocaSuperior->Draw();
	bocaInferior->Draw();
	musloDerecho->Draw();
	piernaDerecha->Draw();
	pataDerecha->Draw();
	musloIzquierdo->Draw();
	piernaIzquierda->Draw();
	pataIzquierda->Draw();
	manoDerecha->Draw();
	manoIzquierda->Draw();
}