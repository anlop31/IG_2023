#ifndef ROBOT_H_INCLUDED
#define ROBOT_H_INCLUDED

#include "auxiliar.h"
#include "objrevolucion.h"

class Robot : public ObjRevolucion
{

    float giroIngleDcha , giroIngleIzda ;
    float giroHombroDcho , giroHombroIzdo ;
    float alturaCuello ;

   public:
    Robot();
    void draw();

    // o mejor modifica giro brazos? en vez de brazo izq y der

    void modificaGiroCabeza(float valor);
    void modificaGiroBrazoIzq(float valor);
    void modificaGiroBrazoDer(float valor); 

    // ejemplo de uso: robot.modificaGiroCabeza(0.05);
    // para incrementar en un 5% el valor del angulo de giro
};

#endif