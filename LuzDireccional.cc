#include <LuzDireccional.h>
#include <auxiliar.h>
#include <unistd.h>


using namespace std;

/// @brief Constructor de LuzDireccional con parámetros
/// @param direccion 
/// @param idLuzOpenGL 
/// @param colorAmbiente 
/// @param colorEspecular 
/// @param colorDifuso 
LuzDireccional::LuzDireccional(Tupla2f direccion, GLenum idLuzOpenGL, 
    Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso){

    id = idLuzOpenGL;
    this->colorAmbiente = colorAmbiente;
    this->colorDifuso = colorDifuso;
    this->colorEspecular = colorEspecular;

    alpha = direccion(0);
    beta = direccion(1);

    // this->posicion = {
    //     sin(alpha) * cos(beta),
    //     sin(beta),
    //     cos(alpha) * cos(beta),
    //     0
    // };

     // actualizar posicion según alpha y beta
    actualizarPosicion();
}


/// @brief Constructor de LuzDireccional solo con la orientación
/// @param orientacion 
LuzDireccional::LuzDireccional(const Tupla2f & orientacion){
    alpha = orientacion(0);
    beta = orientacion(1);

    // actualizar posicion según alpha y beta
    actualizarPosicion();

    // por defecto
    id = 0;
    colorAmbiente = {0.0, 0.0, 0.0, 1.0};
    colorDifuso = {1.0, 0.0, 0.0, 1.0}; // rojo
    colorEspecular = {1.0, 1.0, 1.0, 1.0};
}

/// @brief Función para variar el angulo alpha de la luz
/// @param incremento 
void LuzDireccional::variarAnguloAlpha(float incremento){
    alpha += incremento;

    // comprobar si se pasa de 2pi
    if(alpha > M_PI*2.0)
        alpha -= M_PI*2.0;
    else if(alpha < 0)
        alpha += M_PI*2.0;

    // actualizar posicion según alpha y beta
    actualizarPosicion();
}

/// @brief Función para variar el angulo beta de la luz
/// @param incremento 
void LuzDireccional::variarAnguloBeta(float incremento){
    beta += incremento;
    
    // comprobar si se pasa de 2pi
    if(beta > M_PI*2.0)
        beta -= M_PI*2.0;
    else if(beta < 0)
        beta += M_PI*2.0;
    
    // actualizar posicion según alpha y beta
    actualizarPosicion();
}

/// @brief Función para cambiar el primer componente (R) del color de la luz
void LuzDireccional::cambiarColor(){

    if(colorDifuso(0) == 1){ // si ya está en 1, empezar bajando
        aumentarColor = false;
    }

    if(colorDifuso(0) == 0){ // si ya está en 0, empezar subiendo
        aumentarColor = true;
    }

    // Aumentar color
    if(colorDifuso(0) < 1 && aumentarColor){
        if(colorDifuso(0) + 0.1 > 1){ // si sobrepasa 1, establecer a 1
            colorDifuso = {
                1, // establece a 1
                colorDifuso(1),
                colorDifuso(2),
                1
            };
        }
        else{
            colorDifuso = {
                colorDifuso(0)+0.01, // sumarle a la primera componente
                colorDifuso(1),
                colorDifuso(2),
                1
            };
        }
    }

    // Disminuir color
    if(colorDifuso(0) > 0 && !aumentarColor){
        if(colorDifuso(0) - 0.1 < 0){ // si sobrepasa 0, establecer a 0
            colorDifuso = {
                0, // establece a 0
                colorDifuso(1),
                colorDifuso(2),
                1
            };
        }
        else{
            colorDifuso = {
                colorDifuso(0)-0.01, // restarle a la primera componente
                colorDifuso(1),
                colorDifuso(2),
                1
            };
        }
    }
}

/// @brief Animar color de la luz direccional
void LuzDireccional::animarLuzDireccional(){
    cambiarColor();
}

/// @brief Actualizar la posició de la luz direccional según alpha y beta
void LuzDireccional::actualizarPosicion(){
    posicion(0) = sin(alpha) * cos(beta);
    posicion(1) = sin(beta);
    posicion(2) = cos(alpha) * cos(beta);
    posicion(3) = 0;
}
