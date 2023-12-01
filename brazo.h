#ifndef BRAZO_H_INCLUDED
#define BRAZO_H_INCLUDED

#include "auxiliar.h"
#include "objrevolucion.h"
#include "cilindro.h"

class Brazo : public ObjRevolucion
{
    float h_brazo, r_brazo;
    float giro_brazo = 0;

    Cilindro * cilindro = nullptr;

    bool sentido_positivo = false;
    float limite_giro = 80;

   public:
    Brazo(float h, float r);
    void draw();
    float getAlturaBrazo();
    float getRadioBrazo();
    void setSentidoPositivo(bool sentido);
    bool getSentidoPositivo();
    float getGiroBrazo();


    void modificaGiroBrazo(float valor);
};

#endif