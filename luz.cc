#include <luz.h>
#include <auxiliar.h>
#include<LuzDireccional.h>
#include<LuzPosicional.h>

/// @brief Constructor de luz
Luz::Luz(){
    activada = false;
}

/// @brief Activar las luces
void Luz::activar(){

    // glEnable(id);
    if(activada){
        glLightfv(id, GL_DIFFUSE, colorDifuso);
        glLightfv(id, GL_AMBIENT, colorAmbiente);
        glLightfv(id, GL_SPECULAR, colorEspecular);
        glLightfv(id, GL_POSITION, posicion);
    }

}

/// @brief Obtener si una luz está activada
/// @return Valor de "activada"
bool Luz::estadoActivada(){
    return activada;
}

/// @brief Establecer el valor de activada
/// @param nuevo_valor 
void Luz::setActivada(const bool nuevo_valor){
    activada = nuevo_valor;

    if(activada)
        glEnable(id);
    else
        glDisable(id);
}



int Luz::getId(){
    return id;
}