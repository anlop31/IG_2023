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

    this->posicion = {posicion(0), posicion(1), posicion(2), 0};

    // posicion = {p(0), p(1), p(2), 1};
}


LuzPosicional::LuzPosicional(const Tupla3f & posicion){
        // a rellenar
}