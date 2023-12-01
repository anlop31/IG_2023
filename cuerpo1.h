#ifndef CUERPO1_H_INCLUDED
#define CUERPO1_H_INCLUDED

#include "auxiliar.h"
#include "objrevolucion.h"
#include "pierna.h"
#include "cuerpo2.h"

class Cuerpo1 : public ObjRevolucion
{
    /* OBJETOS*/
    Pierna * pierna_izq = nullptr;
    Pierna * pierna_der = nullptr;
    Cuerpo2 * cuerpo2 = nullptr; // tronco y cabeza

    /* Parámetros tronco */
    float r_tronco, h_tronco;


   public:
    Cuerpo1();
    void draw();

    /* Modificadores */
    void modificaGiroPiernaIzq(float valor);
    void modificaGiroPiernaDer(float valor);
    void modificaDesplazamientoCabeza(float valor);

    /* Métodos SET y GET */
    float getAlturaTronco();
    float getRadioTronco();

    void setSentidoPositivoPiernaIzq(bool sentido);
    void setSentidoPositivoPiernaDer(bool sentido);
};

#endif