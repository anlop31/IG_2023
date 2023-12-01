#include "robot.h"

Robot::Robot(){
    /* Brazos */
    brazo_izq = new Brazo(80, 10);
    brazo_der = new Brazo(80, 10);
    brazo_der->setSentidoPositivo(true);

    r_brazo_izq = brazo_izq->getRadioBrazo();
    r_brazo_der = brazo_der->getRadioBrazo();

    h_brazo_izq = brazo_izq->getAlturaBrazo();
    h_brazo_der = brazo_der->getAlturaBrazo();

    /* Cuerpo1 */
    cuerpo1 = new Cuerpo1();

    h_tronco = cuerpo1->getAlturaTronco();
    r_tronco = cuerpo1->getRadioTronco();

    cuerpo1->setSentidoPositivoPiernaIzq(true);

}

void Robot::draw(){

    // RESTO DEL CUERPO
    glPushMatrix();
        cuerpo1->draw();
    glPopMatrix();

    // BRAZOS
    glPushMatrix();
        glPushMatrix();
            glTranslatef(r_tronco+r_brazo_der/2, 0, 0); // colocarlo a la izq
            glTranslatef(0, h_brazo_der/2, 0);
            brazo_der->draw();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-( r_tronco+r_brazo_izq/2 ), 0, 0); // colocarlo a la izq
            glTranslatef(0, h_brazo_izq/2, 0);
            brazo_izq->draw();
        glPopMatrix();
    glPopMatrix();
}


/* Métodos para los grados de libertad */

void Robot::modificaGiroBrazoDer(float valor){
    brazo_der->modificaGiroBrazo(valor);
}

void Robot::modificaGiroBrazoIzq(float valor){
    brazo_izq->modificaGiroBrazo(valor);
}

void Robot::modificaGiroPiernaIzq(float valor){
    cuerpo1->modificaGiroPiernaIzq(valor);
}

void Robot::modificaGiroPiernaDer(float valor){
    cuerpo1->modificaGiroPiernaDer(valor);
}


// Grados de libertad de ambas piernas y ambos brazos
void Robot::modificaGiroPiernas(float valor){
    // PRUEBA. Hay que identificar cuál tiene que sumar y cuál restar
    // Identificar cuál de las dos va hacia delante.

    cuerpo1->modificaGiroPiernaIzq(valor);
    cuerpo1->modificaGiroPiernaDer(valor);
}

void Robot::modificaGiroBrazos(float valor){
    brazo_izq->modificaGiroBrazo(valor);
    brazo_der->modificaGiroBrazo(valor);
}

void Robot::modificaDesplazamientoCabeza(float valor){
    cuerpo1->modificaDesplazamientoCabeza(valor);
}


/* MÉTODOS SET Y GET */
bool Robot::getSentidoPositivoBrazoIzq(){
    return brazo_izq->getSentidoPositivo();
}


bool Robot::getSentidoPositivoBrazoDer(){
    return brazo_der->getSentidoPositivo();
}


float Robot::getAnguloBrazoIzq(){
    return brazo_izq->getGiroBrazo();
}

float Robot::getAnguloBrazoDer(){
    return brazo_der->getGiroBrazo();
}
