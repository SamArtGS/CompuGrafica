#pragma once
#include "Dragon.h"
#include "MarioCraft.h"

Dragon::Dragon(string rutaObj) : DynamicModel(rutaObj + "/cuerpo.obj") {
	cuerpo = this;
	/*
	cabeza = new Model3D(rutaObj + "/cabeza.obj");
	brazoDer = new Model3D(rutaObj + "/brazoDer.obj");
	brazoIzq = new Model3D(rutaObj + "/brazoIzq.obj");
	pieDer = new Model3D(rutaObj + "/pieIzq.obj");
	pieIzq = new Model3D(rutaObj + "/pieDer.obj");
	*/
}

//Listener
void Dragon::animate() {
	update();

	cuerpo->Init(glm::mat4(1.0f))
		->Translate(-28.0f, 14.2f, .0f);
}

void Dragon::update() {

}

void Dragon::keyboardInput() {

}

void Dragon::renderModels() {

}