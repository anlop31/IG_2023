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

    /* troncoPiernas */
    troncoPiernas = new TroncoPiernas();

    h_tronco = troncoPiernas->getAlturaTronco();
    r_tronco = troncoPiernas->getRadioTronco();

    troncoPiernas->setSentidoPositivoPiernaIzq(true);
}

void Robot::draw(){
    glPushMatrix();
        glTranslatef(0, 0, desplazamiento);

        // RESTO DEL CUERPO
        glPushMatrix();
            troncoPiernas->draw();
        glPopMatrix();

        // BRAZOS
        glPushMatrix();
            glPushMatrix(); // brazo derecho
                glTranslatef(r_tronco+r_brazo_der/2, h_brazo_der/2, 0); // colocarlo a la der y arriba 
                brazo_der->draw();
            glPopMatrix();

            glPushMatrix(); // brazo izquierdo
                glTranslatef(-( r_tronco+r_brazo_izq/2 ), h_brazo_izq/2, 0); // colocarlo a la izq y arriba
                brazo_izq->draw();
            glPopMatrix();
        glPopMatrix();

    glPopMatrix();
}


/* GRADOS DE LIBERTAD INDIVIDUALES */
void Robot::modificaGiroBrazoDer(float valor){
    brazo_der->modificaGiroBrazo(valor);
}

void Robot::modificaGiroBrazoIzq(float valor){
    brazo_izq->modificaGiroBrazo(valor);
}

void Robot::modificaGiroPiernaIzq(float valor){
    troncoPiernas->modificaGiroPiernaIzq(valor);
}

void Robot::modificaGiroPiernaDer(float valor){
    troncoPiernas->modificaGiroPiernaDer(valor);
}


/* GRADOS DE LIBERTAD */ 
void Robot::modificaGiroPiernas(float valor){
    troncoPiernas->modificaGiroPiernaIzq(valor);
    troncoPiernas->modificaGiroPiernaDer(valor);
}

void Robot::modificaGiroBrazos(float valor){
    brazo_izq->modificaGiroBrazo(valor);
    brazo_der->modificaGiroBrazo(valor);
}

void Robot::modificaDesplazamiento(float valor){
    
    desplazamiento += valor;

    // que se muevan los brazos y piernas cuando se mueve
    // modificaGiroBrazos(5);
    // modificaGiroPiernas(5);
}

void Robot::modificaDesplazamientoAislado(float valor){
    desplazamiento += valor;
}


void Robot::cambiarSentidosBrazos(){
    brazo_izq->setSentidoPositivo(!brazo_izq->getSentidoPositivo());
    brazo_der->setSentidoPositivo(!brazo_der->getSentidoPositivo());
}

void Robot::cambiarSentidosPiernas(){
    troncoPiernas->setSentidoPositivoPiernaIzq(!troncoPiernas->getSentidoPositivoPiernaIzq());
    troncoPiernas->setSentidoPositivoPiernaDer(!troncoPiernas->getSentidoPositivoPiernaDer());
}

/* ANIMAR MODELO JERÁRQUICO */
void Robot::animarModeloJerarquico(){
    modificaDesplazamientoAislado(velDesplazamiento);

    modificaGiroBrazos(velBrazos);
    modificaGiroPiernas(velPiernas);
}

// Cambiar velocidades
void Robot::cambiarVelocidad(float valor){
    cambiarVelocidadDesplazamiento(valor);
    cambiarVelocidadGiroBrazos(valor);
    cambiarVelocidadGiroPiernas(valor);
}

void Robot::cambiarVelocidadDesplazamiento(float valor){
    if( (velDesplazamiento + valor) <= 0 )
        velDesplazamiento = 0;
    else
        velDesplazamiento += valor;
}


void Robot::cambiarVelocidadGiroBrazos(float valor){
    if( (velBrazos + valor) <= 0 )
        velBrazos = 0;
    else
        velBrazos += valor;
}

void Robot::cambiarVelocidadGiroPiernas(float valor){
    if( (velPiernas + valor) <= 0 )
        velPiernas = 0;
    else
        velPiernas += valor;
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


/* MATERIALES */
void Robot::setMaterialRobot(Material m){
    troncoPiernas->setMaterialCuerpo(m);
    brazo_izq->setMaterialBrazo(m);
    brazo_der->setMaterialBrazo(m);
}

void Robot::setMaterialPiernas(Material m){
    troncoPiernas->setMaterialPiernas(m);
}


void Robot::setMaterialBrazos(Material m){
    brazo_izq->setMaterialBrazo(m);
    brazo_der->setMaterialBrazo(m);
}

void Robot::setMaterialTronco(Material m){
    troncoPiernas->setMaterialTronco(m);
}

void Robot::setMaterialCabeza(Material m){
    troncoPiernas->setMaterialCabeza(m);
}