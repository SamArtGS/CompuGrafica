#include "Vaca.h"

Vaca::Vaca(string rutaObj, TipoMovimiento mov) : MobMinecraft(rutaObj, Tipo::Cuadrupedo, mov) {

}

void Vaca::animate() {
	switch (estado){
		case Vaca::Estado::caminando:
			switch ((int)ruta[posicion][0]){
			case 1:
				posicionDesplazamiento[2] -= 0.01;
				break;
			case 2:
				posicionDesplazamiento[2] += 0.01;
				break;
			case 3:
				posicionDesplazamiento[0] += 0.01;
				break;
			case 4:
				posicionDesplazamiento[0] -= 0.01;
				break;
			default:
				break;
			}
			this->Translate(posicionDesplazamiento[0],
							posicionDesplazamiento[1],
							posicionDesplazamiento[2]);
			caminar();
			break;
		case Vaca::Estado::mugiendo:
			mugir();
			break;
		case Vaca::Estado::comiendo:

			break;
		default:
			break;
	}
}
void Vaca::keyboardInput() {

}

void Vaca::mugir() {

}
