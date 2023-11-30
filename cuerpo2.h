#ifndef CUERPO2_H_INCLUDED
#define CUERPO2_H_INCLUDED

#include "auxiliar.h"
#include "objrevolucion.h"
#include "esfera.h"
#include "cilindro.h"

// tronco y cabeza
class Cuerpo2 : public ObjRevolucion
{

    float h_tronco, r_tronco;
    float r_cabeza;

    // contendra 2 brazos
    Cilindro * tronco = nullptr;
    Esfera * cabeza = nullptr;



   public:
    Cuerpo2(float h, float r);
    void draw();

    float getAlturaTronco();
    float getRadioTronco();
};

#endif