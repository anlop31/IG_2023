#include <LuzPosicional.h>
#include <auxiliar.h>

using namespace std;

/// @brief Constructor de luz posicional con parámetros
/// @param posicion 
/// @param idLuzOpenGL 
/// @param colorAmbiente 
/// @param colorEspecular 
/// @param colorDifuso 
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

/// @brief Constructor de luz posicional con la posición
/// @param posicion 
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

/// @brief Variar la posición de la luz posicional
/// @param x 
/// @param y 
/// @param z 
void LuzPosicional::variarPosicion(int x, int y, int z){
    posicion(0) += x;
    posicion(1) += y;
    posicion(2) += z;
}

/// @brief Animar posición de la luz posicional
void LuzPosicional::animarLuzPosicional(){
    variarPosicion(0, 2, 0);

    std::cout << "variado posicion: " << std::endl;
    cout << "posicion(0)= " << posicion(0) << endl;
    cout << "posicion(1) =" << posicion(1) << endl;
    cout << "posicion(2)= " << posicion(2) << endl;

}