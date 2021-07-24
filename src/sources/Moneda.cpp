
#pragma once
#include "Moneda.h"
#include "MarioCraft.h"
//#include <GLM/gtx/string_cast.hpp>

Moneda::Moneda(string rutaObj) : DynamicModel(rutaObj) {
  moneda = this;
}

//Listener
void Moneda::animate() {
  moneda->Rotate(2.f, 0.f, 1.f, 0.f);
}

void Moneda::keyboardInput() {

}

void Moneda::renderModels() {

}