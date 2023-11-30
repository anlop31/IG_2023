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


float Brazo::getAlturaBrazo(){
    return h_brazo;
}

float Brazo::getRadioBrazo(){
    return r_brazo;
}

void Brazo::modificaGiroBrazo(float valor){
    giro_brazo += valor; // hacer comprobaciones
}

// metodos para cambiar angulos y demás.....