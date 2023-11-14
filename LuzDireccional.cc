#include <LuzDireccional.h>
#include <auxiliar.h>

LuzDireccional::LuzDireccional(Tupla2f direccion, GLenum idLuzOpenGL, 
    Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso){

    id = idLuzOpenGL;
    this->colorAmbiente = colorAmbiente;
    this->colorDifuso = colorDifuso;
    this->colorEspecular = colorEspecular;

    alpha = direccion(0);
    beta = direccion(1);

    this->posicion = {
        sin(alpha) * cos(beta),
        sin(beta),
        cos(alpha) * cos(beta),
        0
    };
}


LuzDireccional::LuzDireccional(const Tupla2f & orientacion){
    alpha = orientacion(0);
    beta = orientacion(1);


    // por defecto
    id = 0;
    colorAmbiente = {0.0, 0.0, 0.0, 1.0};
    colorDifuso = {1.0, 0.0, 0.0, 1.0}; // rojo
    colorEspecular = {1.0, 1.0, 1.0, 1.0};
}


void LuzDireccional::variarAnguloAlpha(float incremento){
    alpha += incremento;

    // comprobar si se pasa de 2pi
    if(alpha > M_PI*2.0)
        alpha -= M_PI*2.0;
    else if(alpha < 0)
        alpha += M_PI*2.0;

    // actualizar posicion
    posicion(0) = sin(alpha) * cos(beta);
    posicion(1) = sin(beta);
    posicion(2) = cos(alpha) * cos(beta);
}

void LuzDireccional::variarAnguloBeta(float incremento){
    beta += incremento;
    
    // comprobar si se pasa de 2pi
    if(beta > M_PI*2.0)
        beta -= M_PI*2.0;
    else if(beta < 0)
        beta += M_PI*2.0;
    
    // actualizar posicion
    posicion(0) = sin(alpha) * cos(beta);
    posicion(1) = sin(beta);
    posicion(2) = cos(alpha) * cos(beta);
}