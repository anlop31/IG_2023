#ifndef PIERNA_H_INCLUDED
#define PIERNA_H_INCLUDED

#include "auxiliar.h"
#include "objrevolucion.h"
#include "cilindro.h"
#include "esfera.h"

class Pierna : public ObjRevolucion
{
    float h_pierna, r_pierna, r_pie;
    float giro_pierna = 0;

    Cilindro * cilindro = nullptr;
    Esfera * pie = nullptr;

    bool sentido_positivo = false;
    float limite_giro = 80;

   public:
    Pierna(float h, float r, float r_pie);
    void draw();

    void modificaGiroPierna(float valor);
    void setSentidoPositivo(bool sentido);
};

#endif