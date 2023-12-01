#include "cuerpo2.h"


Cuerpo2::Cuerpo2(float h=1, float r=0.5){
    h_tronco = h;
    r_tronco = r;


    tronco = new Cilindro(4, 10, h_tronco, r_tronco);
    cabeza = new Esfera(10, 20, r_tronco-r_tronco*0.40); // menos el 40%

    r_cabeza = cabeza->getRadio();

    limite_desplazamiento = h_tronco - h_tronco*0.7;

    cabeza->setColor(
      Tupla4f(1.0f, 0.0f, 0.0f, 1.0f), // color vértices
      Tupla4f(1.0f, 0.0f, 1.0f, 1.0f), // color líneas
      Tupla4f(1.0f, 0.0f, 0.0f, 1.0f)  // color sólido
   );
}

void Cuerpo2::draw(){
    glPushMatrix();
        glPushMatrix();
            glTranslatef(0, h_tronco+r_cabeza, 0);
            cabeza->draw();
        glPopMatrix();
        tronco->draw();
    glPopMatrix();
}

float Cuerpo2::getAlturaTronco(){
    return h_tronco;
}

float Cuerpo2::getRadioTronco(){
    return r_tronco;
}

void Cuerpo2::modificaDesplazamientoCabeza(float valor){
    if(sentido_positivo){
        if ( (desplazamiento_cabeza + valor) > limite_desplazamiento ){ // ha llegado al tope positivo
            desplazamiento_cabeza = limite_desplazamiento;
            sentido_positivo = false;
        }else{
            desplazamiento_cabeza += valor;
        }
    }else{
        if ( (desplazamiento_cabeza + valor) < -limite_desplazamiento ){ // ha llegado al tope negativo
            desplazamiento_cabeza = -limite_desplazamiento;
            sentido_positivo = true;
        }else{
            desplazamiento_cabeza -= valor;
        }
    }
}