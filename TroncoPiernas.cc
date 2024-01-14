#include "TroncoPiernas.h"

/// @brief Constructor del tronco (troncoCabeza) con las piernas 
TroncoPiernas::TroncoPiernas(){
    pierna_izq = new Pierna(80, 10, 15);
    pierna_der = new Pierna(80, 10, 15);

    troncoCabeza = new TroncoCabeza(50, 50);

    h_tronco = troncoCabeza->getAlturaTronco();
    r_tronco = troncoCabeza->getRadioTronco();
}

/// @brief Método draw del tronco (troncoCabeza) con las piernas
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

/// @brief Modifica el ángulo de giro de la pierna izquierda
/// @param valor 
void TroncoPiernas::modificaGiroPiernaIzq(float valor){
    pierna_izq->modificaGiroPierna(valor);
}

/// @brief Modifica el ángulo de giro de la pierna derecha
/// @param valor 
void TroncoPiernas::modificaGiroPiernaDer(float valor){
    pierna_der->modificaGiroPierna(valor);
}

void TroncoPiernas::modificaDesplazamientoCabeza(float valor){
    troncoCabeza->modificaDesplazamientoCabeza(valor);
}

/* MÉTODOS SET Y GET */

/// @brief Obtener la altura del tronco
/// @return Altura del tronco (h_tronco)
float TroncoPiernas::getAlturaTronco(){
    return h_tronco;
}

/// @brief Obtener el radio del tronco
/// @return Radio del tronco (r_tronco)
float TroncoPiernas::getRadioTronco(){
    return r_tronco;
}

/// @brief Obtener el sentido de giro de la pierna izquierda
/// @return true si el sentido positivo y false si negativo
bool TroncoPiernas::getSentidoPositivoPiernaIzq(){
    return pierna_izq->getSentidoPositivo();
}

/// @brief Obtener el sentido de giro de la pierna derecha
/// @return true si el sentido positivo y false si negativo
bool TroncoPiernas::getSentidoPositivoPiernaDer(){
    return pierna_der->getSentidoPositivo();
}

/// @brief Establecer el sentido de giro de la pierna izquierda 
/// @param sentido true=positivo, false=negativo
void TroncoPiernas::setSentidoPositivoPiernaIzq(bool sentido){
    pierna_izq->setSentidoPositivo(sentido);
}

/// @brief Establecer el sentido de giro de la pierna derecha
/// @param sentido true=positivo, false=negativo
void TroncoPiernas::setSentidoPositivoPiernaDer(bool sentido){
    pierna_der->setSentidoPositivo(sentido);
}



/* MATERIALES */

/// @brief Establecer el material del cuerpo
/// @param m 
void TroncoPiernas::setMaterialCuerpo(Material m){
    troncoCabeza->setMaterialCuerpo(m);
    pierna_izq->setMaterialPierna(m);
    pierna_der->setMaterialPierna(m);
}

/// @brief Establecer el material de las piernas
/// @param m 
void TroncoPiernas::setMaterialPiernas(Material m){
    pierna_izq->setMaterialPierna(m);
    pierna_der->setMaterialPierna(m);
}

/// @brief Establecer el material del tronco
/// @param m 
void TroncoPiernas::setMaterialTronco(Material m){
    troncoCabeza->setMaterialTronco(m);
}

/// @brief Establecer el material de la cabeza
/// @param m 
void TroncoPiernas::setMaterialCabeza(Material m){
    troncoCabeza->setMaterialCabeza(m);
}