#include "brazo.h"


Brazo::Brazo(float h=1, float r=0.5){
    h_brazo = h;
    r_brazo = r;

    cilindro = new Cilindro(4, 20, h_brazo, r_brazo);
}


void Brazo::draw(){
    glPushMatrix();
        glRotatef(giro_brazo, 1, 0, 0);
        glTranslatef(0, -h_brazo, 0);
        cilindro->draw();
    glPopMatrix();
}

/* MODIFICADORES */
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
float Brazo::getAlturaBrazo(){
    return h_brazo;
}

float Brazo::getRadioBrazo(){
    return r_brazo;
}

void Brazo::setSentidoPositivo(bool sentido){
    sentido_positivo = sentido;
}

bool Brazo::getSentidoPositivo(){
    return sentido_positivo;
}

float Brazo::getGiroBrazo(){
    return giro_brazo;
}


void Brazo::setMaterialBrazo(Material m){
    cilindro->setMaterial(m);
}