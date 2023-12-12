#ifndef PIERNA_H_INCLUDED
#define PIERNA_H_INCLUDED

#include "auxiliar.h"
#include "objrevolucion.h"
#include "cilindro.h"
#include "esfera.h"

class Pierna : public ObjRevolucion
{
    /* OBJETOS */
    Cilindro * cilindro = nullptr;
    Esfera * pie = nullptr;

    /* Parámetros pierna */
    float h_pierna, r_pierna, r_pie;
    float giro_pierna = 0;

    /* Parámetros para el giro */
    bool sentido_positivo = false;
    float limite_giro = 70;

   public:
    Pierna(float h, float r, float r_pie);
    void draw();

    /* Modificadores */
    void modificaGiroPierna(float valor);

    /* Métodos SET y GET */
    float getAlturaPierna();
    float getRadioPierna();
    float getRadioPie();
    float getGiroPierna();

    bool getSentidoPositivo();
    void setSentidoPositivo(bool sentido);

    /* Materiales */
    void setMaterialPierna(Material m);
};

#endif