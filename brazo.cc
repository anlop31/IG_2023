#include "brazo.h"

/// @brief Constructor de brazo
/// @param h Altura del brazo
/// @param r Radio del brazo
Brazo::Brazo(float h=1, float r=0.5){
    h_brazo = h;
    r_brazo = r;

    cilindro = new Cilindro(4, 20, h_brazo, r_brazo);
}

/// @brief Método draw de Brazo
void Brazo::draw(){
    glPushMatrix();
        glRotatef(giro_brazo, 1, 0, 0);
        glTranslatef(0, -h_brazo, 0);
        cilindro->draw();
    glPopMatrix();
}


/* MODIFICADORES */

/// @brief Modifica el ángulo de giro del brazo
/// @param valor 
void Brazo::modificaGiroBrazo(float valor){

    if(sentido_positivo){
        if ( (giro_brazo + valor) > limite_giro ){ // ha llegado al tope positivo
            giro_brazo = limite_giro;
            sentido_positivo = false;
        } else {
            giro_brazo += valor;
        }
    } else {
        if ( (giro_brazo + valor) < -limite_giro ){ // ha llegado al tope negativo
            giro_brazo = -limite_giro;
            sentido_positivo = true;
        } else {
            giro_brazo -= valor;
        }
    }

}


/* MÉTODOS GET Y SET */

/// @brief Obtener la altura del brazo
/// @return Altura del brazo (h_brazo)
float Brazo::getAlturaBrazo(){
    return h_brazo;
}

/// @brief Obtener el radio del brazo
/// @return Rradio del brazo(r_brazo)
float Brazo::getRadioBrazo(){
    return r_brazo;
}

/// @brief Obtener el giro del brazo
/// @return El ángulo del brazo (giro_brazo)
float Brazo::getGiroBrazo(){
    return giro_brazo;
}

/// @brief Obtener el sentido de giro del brazo
/// @return true si el sentido positivo y false si negativo
bool Brazo::getSentidoPositivo(){
    return sentido_positivo;
}

/// @brief Establecer el sentido de giro del brazo
/// @param sentido true=positivo, false=negativo
void Brazo::setSentidoPositivo(bool sentido){
    sentido_positivo = sentido;
}


/* MATERIALES */

/// @brief Establecer el material del brazo
/// @param m 
void Brazo::setMaterialBrazo(Material m){
    cilindro->setMaterial(m);
}