#ifndef ROBOT_H_INCLUDED
#define ROBOT_H_INCLUDED

#include "auxiliar.h"
#include "objrevolucion.h"
#include "TroncoPiernas.h"
#include "brazo.h"

class Robot : public ObjRevolucion
{
    /* OBJETOS */
    Brazo * brazo_izq = nullptr;
    Brazo * brazo_der = nullptr;
    TroncoPiernas * troncoPiernas = nullptr;

    /* Parámetros brazos */
    float r_brazo_izq, r_brazo_der;
    float h_brazo_izq, h_brazo_der;

    /* Parámetros tronco */
    float h_tronco, r_tronco;

    /* Parámetros para grados de libertad */
    float desplazamiento = 0;

    /* Velocidad para animación automática */
    float velDesplazamiento = 2;
    float velBrazos = 2;
    float velPiernas = 2;

   public:
    Robot();
    void draw();

    /* Modificadores individuales */
    void modificaGiroBrazoIzq(float valor);
    void modificaGiroBrazoDer(float valor); 

    void modificaGiroPiernaIzq(float valor);
    void modificaGiroPiernaDer(float valor);

    /* Modificadores generales */
    void modificaGiroPiernas(float valor);
    void modificaGiroBrazos(float valor);
    void modificaDesplazamientoCabeza(float valor);
    void modificaDesplazamiento(float valor);
    void modificaDesplazamientoAislado(float valor);

    /* Animación automática */
    void animarModeloJerarquico();
    void cambiarVelocidad(float valor);
    void cambiarVelocidadDesplazamiento(float valor);
    void cambiarVelocidadGiroBrazos(float valor);
    void cambiarVelocidadGiroPiernas(float valor);

    /* Métodos GET y SET */
    bool getSentidoPositivoBrazoDer();
    bool getSentidoPositivoBrazoIzq();

    float getAnguloBrazoDer();
    float getAnguloBrazoIzq();

    /* Material robot */
    void setMaterialRobot(Material mat);
    void setMaterialPiernas(Material mat);
    void setMaterialBrazos(Material mat);
    void setMaterialTronco(Material mat);
    void setMaterialCabeza(Material mat);


    // ejemplo de uso: robot.modificaGiroCabeza(0.05);
    // para incrementar en un 5% el valor del angulo de giro
};

#endif