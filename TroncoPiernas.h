#ifndef TRONCOPIERNAS_H_INCLUDED
#define TRONCOPIERNAS_H_INCLUDED

#include "auxiliar.h"
#include "objrevolucion.h"
#include "pierna.h"
#include "TroncoCabeza.h"

class TroncoPiernas : public ObjRevolucion
{ // cuerpo1
    /* OBJETOS*/
    Pierna * pierna_izq = nullptr;
    Pierna * pierna_der = nullptr;
    TroncoCabeza * troncoCabeza = nullptr; // tronco y cabeza

    /* Parámetros tronco */
    float r_tronco, h_tronco;


   public:
    TroncoPiernas();

    void draw();

    /* Modificadores */
    void modificaGiroPiernaIzq(float valor);
    void modificaGiroPiernaDer(float valor);
    void modificaDesplazamientoCabeza(float valor);

    /* Métodos SET y GET */
    float getAlturaTronco();
    float getRadioTronco();

    bool getSentidoPositivoPiernaIzq();
    bool getSentidoPositivoPiernaDer();
    void setSentidoPositivoPiernaIzq(bool sentido);
    void setSentidoPositivoPiernaDer(bool sentido);

    /* Materiales */
    void setMaterialCuerpo(Material m);
    void setMaterialPiernas(Material m);
    void setMaterialTronco(Material m);
    void setMaterialCabeza(Material m);
};

#endif