#pragma once
#include <vector>
#include "Model3D.h"
#include "StaticModel.h"
#include "DymanicModel.h"



class Kart: public DynamicModel{
    private:
        bool salida = false;
        //Ruta con base a las manecillas del reloj y horas 8 DOBLECES
        float distancias[20][2] = {
            {12,220},
            {1,15},
            {2,15},
            {3,42},
            {4,15},
            {5,15},
            {6,50},
            {7,50},
            {6,50},
            {7,15},
            {9,130},
            {8,15},
            {7,15},
            {6,80},
            {5,15},
            {4,15},
            {3,38},
            {2,15},
            {1,15},
            {12,10}
        };


        
        int posicion = 0;
        float incremento = 0.0f;
        float posicionInicial[3] = { 0.0f, 0.0f, 0.0f };
        float escalaInicial[3] = { 0.0f, 0.0f, 0.0f };
        float posicionDesplazamiento[3] = {0.0f,0.0f,0.0f};
        
    public:
        float velocidad = 0.3f;
        Kart(string rutaObj) : DynamicModel(rutaObj) { };
        void animate();
        void keyboardInput();
        void renderModels();
        virtual Model3D* Translate(float tX, float tY, float tZ);

};

