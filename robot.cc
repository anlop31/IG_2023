#include "robot.h"

Robot::Robot(){
    /* Brazos */
    brazo_izq = new Brazo(80, 10);
    brazo_der = new Brazo(80, 10);

    r_brazo_izq = brazo_izq->getRadioBrazo();
    r_brazo_der = brazo_der->getRadioBrazo();

    h_brazo_izq = brazo_izq->getAlturaBrazo();
    h_brazo_der = brazo_der->getAlturaBrazo();

    /* Cuerpo1 */
    cuerpo1 = new Cuerpo1();

    h_tronco = cuerpo1->getAlturaTronco();
    r_tronco = cuerpo1->getRadioTronco();

}

void Robot::draw(){

    glPushMatrix();
        cuerpo1->draw();
    glPopMatrix();

    // brazos
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

void Robot::modificaGiroPiernas(float valor){
    // PRUEBA. Hay que identificar cuál tiene que sumar y cuál restar
    // Identificar cuál de las dos va hacia delante.

    cuerpo1->modificaGiroPiernaIzq(valor);
    cuerpo1->modificaGiroPiernaDer(-valor);
}