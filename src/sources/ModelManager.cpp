#include "ModelManager.h"

// addModel registra un nuevo modelo en la lista de modelos
void ModelManager::addModel(Model3D* model, tipoModel tipo) {
	if (tipo == tipoModel::STATIC)
		staticModels.push_back(static_cast<StaticModel*>(model));
	else
		dymanicModels.push_back(static_cast<DynamicModel*>(model));
}

// renderModels recorre la lista de modelos e invoca para cada uno su método
// su método draw
void ModelManager::renderModels() {
	for (Model3D * model : staticModels)
		model->Draw();
	for (Model3D* model : dymanicModels)
		model->Draw();
}

void ModelManager::keyboardInputModels() {
	for (DynamicModel* model : dymanicModels)
		model->keyboardInput();
}

// 
void ModelManager::updateModels() {
	for (DynamicModel* model : dymanicModels)
		model->animate();
}