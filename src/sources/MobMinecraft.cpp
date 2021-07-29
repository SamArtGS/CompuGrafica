#pragma once
#include "MarioCraft.h"
#include "MobMinecraft.h"

MobMinecraft::MobMinecraft(string rutaObj, Tipo tipo, TipoMovimiento mov) : DynamicModel(rutaObj + "/torso/torso.obj"){
	torso = this;
	retardo = rand() % 1000 + 1;
	switch (tipo){
	case MobMinecraft::Tipo::Antropomorfico:
		brazoDer = new Model3D(rutaObj + "/brazoDer/brazoDer.obj");
		brazoIzq = new Model3D(rutaObj + "/brazoIzq/brazoIzq.obj");
		pieIzq = new Model3D(rutaObj + "/pieIzq/pieIzq.obj");
		pieDer = new Model3D(rutaObj + "/pieDer/pieDer.obj");
		break;
	case MobMinecraft::Tipo::Ave:
		brazoDer = new Model3D(rutaObj + "/ala/ala.obj");
		brazoIzq = new Model3D(rutaObj + "/ala/ala.obj");
		pieIzq = new Model3D(rutaObj + "/pata/pata.obj");
		pieDer = new Model3D(rutaObj + "/pata/pata.obj");
		break;
	case MobMinecraft::Tipo::Cuadrupedo:
		brazoDer = new Model3D(rutaObj + "/pata/pata.obj");
		brazoIzq = new Model3D(rutaObj + "/pata/pata.obj");
		pieIzq = new Model3D(rutaObj + "/pata/pata.obj");
		pieDer = new Model3D(rutaObj + "/pata/pata.obj");
		break;
	default:
		break;
	}
	

	float sixsag[2][2] = { { 1,15 }, {1, 50} };

	float cuadrado[1][2] = { { 1,50 } };

	float rectangulo[8][2] = { { 1,50 },
							 { 4,50 },
							 { 2,50 },
							 { 3,50 },
							 { 1,50 },
							 { 3,50 },
							 { 2,50 },
							 { 4,50 } };
	float ELE[8][2] = { { 1,50 },
							 { 4,50 },
							 { 2,50 },
							 { 3,50 },
							 { 1,50 },
							 { 3,50 },
							 { 2,50 },
							 { 4,50 } };
	float CE[8][2] = { { 1,50 },
					   { 4,50 },
					   { 2,50 },
					   { 3,50 },
					   { 1,50 },
					   { 3,50 },
					   { 2,50 },
					   { 4,50 } };

	switch (mov) {
	case MobMinecraft::TipoMovimiento::sixSag:
		memcpy(ruta, sixsag, sizeof(sixsag));
		break;
	case MobMinecraft::TipoMovimiento::cuadrado:
		memcpy(ruta, cuadrado, sizeof(cuadrado));
		break;
	case MobMinecraft::TipoMovimiento::rectangulo:
		memcpy(ruta, rectangulo, sizeof(rectangulo));
		break;
	case MobMinecraft::TipoMovimiento::L:
		memcpy(ruta, ELE, sizeof(ELE));
		break;
	case MobMinecraft::TipoMovimiento::C:
		memcpy(ruta, CE, sizeof(CE));
		break;
	default:
		break;
	}

}


void MobMinecraft::renderModels() {
	pieDer->Draw();
	pieIzq->Draw();
	brazoDer->Draw();
	brazoIzq->Draw();
	
}
void MobMinecraft::update() {

}


void MobMinecraft::caminar() {
	this->Translate(0, 0, 0);
	brazoDer->Init(this->model)
		->Translate(posicionInicial[0],
			posicionInicial[1] + angulo / 12,
			posicionInicial[2] + angulo / 1.7)
		->Rotate(-angulo, 1, 0, 0);

	brazoIzq->Init(this->model)
		->Translate(posicionInicial[0],
			posicionInicial[1] - angulo / 12,
			posicionInicial[2] - angulo / 1.7)
		->Rotate(angulo, 1, 0, 0);

	pieIzq->Init(this->model)
		->Translate(posicionInicial[0],
			posicionInicial[1] + angulo / 10 + 2,
			posicionInicial[2] + angulo / 4 - 1)
		->Rotate(-angulo, 1, 0, 0);

	pieDer->Init(this->model)
		->Translate(posicionInicial[0],
			posicionInicial[1] - angulo / 10 + 2,
			posicionInicial[2] - angulo / 4 - 1)
		->Rotate(angulo, 1, 0, 0);

	if (idaVueta) {
		angulo += 0.5f;
		if (angulo >= 15) {
			idaVueta = false;
		}
	}
	else {
		angulo -= 0.5f;
		if (angulo <= -15) {
			idaVueta = true;
		}
	}

	switch ((int)ruta[posicion][0]) {
		case 1:
			posicionDesplazamiento[2] -= 0.2;
			break;
		case 2:
			posicionDesplazamiento[2] += 0.2;
			break;
		case 3:
			posicionDesplazamiento[0] += 0.2;
			break;
		case 4:
			posicionDesplazamiento[0] -= 0.2;
			break;
		default:
			break;
		}
		this->Translate(posicionDesplazamiento[0],
			posicionDesplazamiento[1],
			posicionDesplazamiento[2]);
		
		if (posicion % 2 == 0) {
			this->Rotate(0.3, 0, 1, 0);
		}
		else {

			this->Rotate(-0.3, 0, 1, 0);
		}
		
		auxiliarContador += 0.1f;
		if ((int)ruta[posicion][1] <= auxiliarContador) {
			auxiliarContador = 0.0f;
			
			if (posicion > sizeof(ruta) / sizeof(ruta[0])) {
				posicion = 0;
			}
			else {
				posicion++;
			}

		}
}

Model3D* MobMinecraft::Translate(float tX, float tY, float tZ) {
	Model3D* extraModel = __super::Translate(tX, tY, tZ);
	
	int posAux[3] = { tX,tY,tZ };
	std::copy(posAux, posAux + 3, posicionInicial);
	std::copy(posAux, posAux + 3, posicionDesplazamiento);

	
	pieDer->Translate(tX, tY, tZ);
	pieIzq->Translate(tX, tY, tZ);
	brazoDer->Translate(tX, tY, tZ);
	brazoIzq->Translate(tX, tY, tZ);

	return extraModel;
}

Model3D* MobMinecraft::Rotate(float angulo, float tX, float tY, float tZ) {
	Model3D* extraModel = __super::Rotate(angulo, tX, tY, tZ);

	
	pieDer->Rotate(angulo, tX, tY, tZ);
	pieIzq->Rotate(angulo, tX, tY, tZ);
	brazoDer->Rotate(angulo, tX, tY, tZ);
	brazoIzq->Rotate(angulo, tX, tY, tZ);

	return extraModel;
}

Model3D* MobMinecraft::Scale(float tX, float tY, float tZ) {
	Model3D* extraModel = __super::Scale(tX, tY, tZ);
	pieDer->Scale(tX, tY, tZ);
	pieIzq->Scale(tX, tY, tZ);
	brazoDer->Scale(tX, tY, tZ);
	brazoIzq->Scale(tX, tY, tZ);
	

	return extraModel;
}