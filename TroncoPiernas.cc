#include "TroncoPiernas.h"


TroncoPiernas::TroncoPiernas(){
    pierna_izq = new Pierna(80, 10, 15);
    pierna_der = new Pierna(80, 10, 15);

    troncoCabeza = new TroncoCabeza(50, 50);

    h_tronco = troncoCabeza->getAlturaTronco();
    r_tronco = troncoCabeza->getRadioTronco();
}

void TroncoPiernas::draw(){
    glPushMatrix();
        troncoCabeza->draw();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(r_tronco-30, h_tronco/2, 0);
        pierna_der->draw();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-(r_tronco-30), h_tronco/2, 0);
        pierna_izq->draw();
    glPopMatrix();
}


/* MODIFICADORES */
void TroncoPiernas::modificaGiroPiernaIzq(float valor){
    pierna_izq->modificaGiroPierna(valor);
}

void TroncoPiernas::modificaGiroPiernaDer(float valor){
    pierna_der->modificaGiroPierna(valor);
}

/* MÉTODOS SET Y GET */
float TroncoPiernas::getAlturaTronco(){
    return h_tronco;
}

float TroncoPiernas::getRadioTronco(){
    return r_tronco;
}

bool TroncoPiernas::getSentidoPositivoPiernaIzq(){
    return pierna_izq->getSentidoPositivo();
}

bool TroncoPiernas::getSentidoPositivoPiernaDer(){
    return pierna_der->getSentidoPositivo();
}

void TroncoPiernas::setSentidoPositivoPiernaIzq(bool sentido){
    pierna_izq->setSentidoPositivo(sentido);
}

void TroncoPiernas::setSentidoPositivoPiernaDer(bool sentido){
    pierna_der->setSentidoPositivo(sentido);
}



/* MATERIALES */
void TroncoPiernas::setMaterialCuerpo(Material m){
    troncoCabeza->setMaterialCuerpo(m);
    pierna_izq->setMaterialPierna(m);
    pierna_der->setMaterialPierna(m);
}

void TroncoPiernas::setMaterialPiernas(Material m){
    pierna_izq->setMaterialPierna(m);
    pierna_der->setMaterialPierna(m);
}


void TroncoPiernas::setMaterialTronco(Material m){
    troncoCabeza->setMaterialTronco(m);
}

void TroncoPiernas::setMaterialCabeza(Material m){
    troncoCabeza->setMaterialCabeza(m);
}