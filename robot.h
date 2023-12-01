#ifndef ROBOT_H_INCLUDED
#define ROBOT_H_INCLUDED

#include "auxiliar.h"
#include "objrevolucion.h"
#include "cuerpo1.h"
#include "brazo.h"

class Robot : public ObjRevolucion
{
    // Brazos y resto del cuerpo
    Brazo * brazo_izq = nullptr;
    Brazo * brazo_der = nullptr;
    Cuerpo1 * cuerpo1 = nullptr;

    // variables de los brazos
    float r_brazo_izq, r_brazo_der;
    float h_brazo_izq, h_brazo_der;

    // variables del tronco
    float h_tronco, r_tronco;

   public:
    Robot();
    void draw();

    // o mejor modifica giro brazos? en vez de brazo izq y der

    // void modificaGiroCabeza(float valor);
    void modificaGiroBrazoIzq(float valor);
    void modificaGiroBrazoDer(float valor); 

    void modificaGiroPiernaIzq(float valor);
    void modificaGiroPiernaDer(float valor);

    void modificaGiroPiernas(float valor);
    void modificaGiroBrazos(float valor);
    void modificaDesplazamientoCabeza(float valor);

    bool getSentidoPositivoBrazoDer();
    bool getSentidoPositivoBrazoIzq();

    float getAnguloBrazoDer();
    float getAnguloBrazoIzq();

    // ejemplo de uso: robot.modificaGiroCabeza(0.05);
    // para incrementar en un 5% el valor del angulo de giro
};

#endif