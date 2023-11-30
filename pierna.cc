#include "pierna.h"

Pierna::Pierna(float h = 1, float r = 1, float r_pie = 0.5){

    h_pierna = h;
    r_pierna = r; // diamtro = r*2
    this->r_pie = r_pie;

    cilindro = new Cilindro(4, 20, h_pierna, r_pierna);

    pie = new Esfera(15, 30, r_pie); // pie

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

void Pierna::modificaGiroPierna(float valor){
    giro_pierna += valor;
}