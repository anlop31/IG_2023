#include <luz.h>
#include <auxiliar.h>
#include<LuzDireccional.h>
#include<LuzPosicional.h>


Luz::Luz(){
    activada = false;
}

void Luz::activar(){

    // glEnable(id);
    if(activada){
        glLightfv(id, GL_DIFFUSE, colorDifuso);
        glLightfv(id, GL_AMBIENT, colorAmbiente);
        glLightfv(id, GL_SPECULAR, colorEspecular);
        glLightfv(id, GL_POSITION, posicion);
    }

}

bool Luz::estadoActivada(){
    return activada;
}


void Luz::setActivada(const bool nuevo_valor){
    activada = nuevo_valor;

    if(activada)
        glEnable(id);
    else
        glDisable(id);
}

