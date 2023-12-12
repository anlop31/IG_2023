#ifndef TRONCOCABEZA_H_INCLUDED
#define TRONCOCABEZA_H_INCLUDED

#include "auxiliar.h"
#include "objrevolucion.h"
#include "esfera.h"
#include "cilindro.h"

// tronco y cabeza
class TroncoCabeza : public ObjRevolucion
{

    float h_tronco, r_tronco;
    float r_cabeza;

    // contendra 2 brazos
    Cilindro * tronco = nullptr;
    Esfera * cabeza = nullptr;


   public:
    TroncoCabeza(float h, float r);
    void draw();

    /* Métodos SET y GET */
    float getAlturaTronco();
    float getRadioTronco();
    float getRadioCabeza();

    /* Materiales */
    void setMaterialCuerpo(Material m);
    void setMaterialTronco(Material m);
    void setMaterialCabeza(Material m);
};

#endif