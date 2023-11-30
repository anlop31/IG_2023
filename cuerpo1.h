#ifndef CUERPO1_H_INCLUDED
#define CUERPO1_H_INCLUDED

#include "auxiliar.h"
#include "objrevolucion.h"
#include "pierna.h"
#include "cuerpo2.h"

class Cuerpo1 : public ObjRevolucion
{

    // contendra 2 brazos
    Pierna * pierna_izq = nullptr;
    Pierna * pierna_der = nullptr;

    float r_tronco, h_tronco;

    // tronco y cabeza (al que uniremos las piernas y formaran cuerpo1)
    Cuerpo2 * cuerpo2 = nullptr;

   public:
    Cuerpo1();
    void draw();
    float getAlturaTronco();
    float getRadioTronco();

    void modificaGiroPiernaIzq(float valor);
    void modificaGiroPiernaDer(float valor);

};

#endif