#ifndef CABEZA_H_INCLUDED
#define CABEZA_H_INCLUDED

#include "auxiliar.h"
#include "objrevolucion.h"
#include "esfera.h"
#include "cilindro.h"

// tronco y cabeza
class Cabeza : public ObjRevolucion
{

    float h_tronco, r_tronco;
    float r_cabeza;

    // contendra 2 brazos
    Cilindro * oreja1 = nullptr;
    Cilindro * oreja2 = nullptr;
    Esfera * cabeza = nullptr;

    float desplazamientoCabeza = 0;
    float limiteCabeza = 0;


   public:
    Cabeza(float r_cabeza);
    void draw();

    /* Métodos SET y GET */
    float getRadioCabeza();

    /* Materiales */
    void setMaterialCabeza(Material m);
    void setMaterialOrejas(Material m);

    /* Modificadores */
    void modificaDesplazamientoCabeza(float valor); //??

};

#endif