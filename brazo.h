#ifndef BRAZO_H_INCLUDED
#define BRAZO_H_INCLUDED

#include "auxiliar.h"
#include "objrevolucion.h"
#include "cilindro.h"

class Brazo : public ObjRevolucion
{
    /* OBJETOS */
    Cilindro * cilindro = nullptr;

    /* Parámetros brazo */
    float h_brazo, r_brazo;
    float giro_brazo = 0;

    /* Parámetros para el giro */
    bool sentido_positivo = false;
    float limite_giro = 70;

   public:
    Brazo(float h, float r);
    void draw();

    /* Modificadores */
    void modificaGiroBrazo(float valor);

    /* Métodos SET y GET */
    float getAlturaBrazo();
    float getRadioBrazo();
    void setSentidoPositivo(bool sentido);
    bool getSentidoPositivo();
    float getGiroBrazo();

    /* Material */
    void setMaterialBrazo(Material m);
};

#endif