#include "pierna.h"

using namespace std;

Pierna::Pierna(float h = 1, float r = 1, float r_pie = 0.5){

    h_pierna = h;
    r_pierna = r; 
    this->r_pie = r_pie;

    cilindro = new Cilindro(4, 20, h_pierna, r_pierna);

    pie = new Esfera(15, 30, r_pie); 

}

void Pierna::draw(){
    glPushMatrix();
        glRotatef(giro_pierna, 1, 0, 0); // empiezo en 0
        glTranslatef(0, -h_pierna, 0);

        glPushMatrix();
            pie->draw();
        glPopMatrix();
        cilindro->draw();
    glPopMatrix();
}


/* MODIFICADORES */
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
float Pierna::getAlturaPierna(){
    return h_pierna;
}

float Pierna::getRadioPierna(){
    return r_pierna;
}

float Pierna::getRadioPie(){
    return r_pie;
}

float Pierna::getGiroPierna(){
    return giro_pierna;
}

bool Pierna::getSentidoPositivo(){
    return sentido_positivo;
}

void Pierna::setSentidoPositivo(bool sentido){
    sentido_positivo = sentido;
}


/* MATERIALES */
void Pierna::setMaterialPierna(Material m){
    cilindro->setMaterial(m);
    pie->setMaterial(m);
}