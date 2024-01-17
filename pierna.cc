#include "pierna.h"

using namespace std;

/// @brief Constructor de pierna
/// @param h Altura de la pierna
/// @param r Radio de la pierna
/// @param r_pie Radio del pie
Pierna::Pierna(float h = 1, float r = 1, float r_pie = 0.5){

    h_pierna = h;
    r_pierna = r; 
    this->r_pie = r_pie;

    cilindro = new Cilindro(4, 20, h_pierna, r_pierna);

    pie = new Esfera(15, 30, r_pie); 

}

/// @brief Método draw de Pierna
void Pierna::draw(){
    glPushMatrix();
        glRotatef(giro_pierna, 1, 0, 0); // empiezo en 0
        glTranslatef(0, -h_pierna, 0);

        pie->draw();
        cilindro->draw();
    glPopMatrix();
}


/* MODIFICADORES */

/// @brief Modificar el ángulo de la pierna
/// @param valor 
void Pierna::modificaGiroPierna(float valor){
    
    if(sentido_positivo){
        if ( (giro_pierna + valor) > limite_giro ){ // ha llegado al tope positivo
            giro_pierna = limite_giro;
            sentido_positivo = false;
        } else {
            giro_pierna += valor;
        }
    } else {
        if ( (giro_pierna + valor) < -limite_giro ){ // ha llegado al tope negativo
            giro_pierna = -limite_giro;
            sentido_positivo = true;
        } else {
            giro_pierna -= valor;
        }
    }

    // debug
    // std::cout << "angulo:" << giro_pierna << std::endl;
}


/* MÉTODOS SET Y GET */

/// @brief Obtener la altura de la pierna
/// @return Altura de la pierna (h_pierna)
float Pierna::getAlturaPierna(){
    return h_pierna;
}

/// @brief Obtener el radio de la pierna
/// @return Radio de la pierna (r_pierna)
float Pierna::getRadioPierna(){
    return r_pierna;
}

/// @brief Obtener el radio del pie
/// @return Radio del pie (r_pie)
float Pierna::getRadioPie(){
    return r_pie;
}

/// @brief Obtener el ángulo de giro de la pierna
/// @return Ángulo de la pierna (giro_pierna)
float Pierna::getGiroPierna(){
    return giro_pierna;
}

/// @brief Obtener el sentido de giro de la pierna
/// @return true si el sentido positivo y false si negativo
bool Pierna::getSentidoPositivo(){
    return sentido_positivo;
}

/// @brief Establecer el sentido de giro de la pierna
/// @param sentido true=positivo, false=negativo
void Pierna::setSentidoPositivo(bool sentido){
    sentido_positivo = sentido;
}


/* MATERIALES */

/// @brief Establecer el material de la pierna
/// @param m 
void Pierna::setMaterialPierna(Material m){
    cilindro->setMaterial(m);
    pie->setMaterial(m);
}