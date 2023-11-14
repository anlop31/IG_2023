#include <LuzPosicional.h>
#include <auxiliar.h>


LuzPosicional::LuzPosicional(
    Tupla3f posicion, GLenum idLuzOpenGL,
    Tupla4f colorAmbiente, Tupla4f colorEspecular,
    Tupla4f colorDifuso     ) 
{
    id = idLuzOpenGL;
    this->colorAmbiente = colorAmbiente;
    this->colorDifuso = colorDifuso;
    this->colorEspecular = colorEspecular;

    this->posicion = {
        posicion(0), // x
        posicion(1), // y
        posicion(2), // z
        1
    };
}


LuzPosicional::LuzPosicional(const Tupla3f & posicion){
    // por defecto
    id = 0;
    colorAmbiente = {0.0, 0.0, 0.0, 1.0};
    colorDifuso = {1.0, 0.0, 0.0, 1.0}; // rojo
    colorEspecular = {1.0, 1.0, 1.0, 1.0};

    this->posicion = {
        posicion(0), // x
        posicion(1), // y
        posicion(2), // z
        1
    };
}