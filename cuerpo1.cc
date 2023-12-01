#include "cuerpo1.h"


Cuerpo1::Cuerpo1(){
    pierna_izq = new Pierna(80, 10, 15);
    pierna_der = new Pierna(80, 10, 15);

    cuerpo2 = new Cuerpo2(50, 50);

    h_tronco = cuerpo2->getAlturaTronco();
    r_tronco = cuerpo2->getRadioTronco();
}

void Cuerpo1::draw(){
    glPushMatrix();
        cuerpo2->draw();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(r_tronco-30, 0, 0);
        glTranslatef(0, h_tronco/2, 0);
        pierna_der->draw();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-(r_tronco-30), 0, 0);
        glTranslatef(0, h_tronco/2, 0);
        pierna_izq->draw();
    glPopMatrix();
}


/* MODIFICADORES */
void Cuerpo1::modificaGiroPiernaIzq(float valor){
    pierna_izq->modificaGiroPierna(valor);
}

void Cuerpo1::modificaGiroPiernaDer(float valor){
    pierna_der->modificaGiroPierna(valor);
}

void Cuerpo1::modificaDesplazamientoCabeza(float valor){
    cuerpo2->modificaDesplazamientoCabeza(valor);
}


/* MÉTODOS SET Y GET */
float Cuerpo1::getAlturaTronco(){
    return h_tronco;
}

float Cuerpo1::getRadioTronco(){
    return r_tronco;
}

void Cuerpo1::setSentidoPositivoPiernaIzq(bool sentido){
    pierna_izq->setSentidoPositivo(sentido);
}

void Cuerpo1::setSentidoPositivoPiernaDer(bool sentido){
    pierna_der->setSentidoPositivo(sentido);
}