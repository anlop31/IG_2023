#include "auxiliar.h"
#include "malla.h"
#include "carretera.h"

/// @brief Constructor de carretera
/// @param ancho 
/// @param largo 
Carretera::Carretera(const float ancho, const float largo){
    this->ancho = ancho;
    this->largo = largo;

    v.resize(4); // 4 vértices
    f.resize(2); // 2 caras

    // inicializar la tabla de vértices
    v[0] = {0.0f, 0.0f, 0.0f};
    v[1] = {ancho, 0.0f, 0.0f};
    v[2] = {ancho, largo, 0.0f};
    v[3] = {0.0f, largo, 0.0f};

    // inicializar las caras
    f[0] = {0, 1, 2};
    f[1] = {0, 2, 3}; 

    // texturas
    modo_textura = PLANA;

    ct.resize(v.size());
    es_carretera = true;


    // colores
    Tupla4f colorVertices = Tupla4f(1.0f, 0.0f, 0.0f, 1.0f);
    Tupla4f colorLineas = Tupla4f(0.0f, 0.0f, 1.0f, 1.0f);
    Tupla4f colorSolido = Tupla4f(1.0f, 1.0f, 1.0f, 1.0f);

    setColor(colorVertices, colorLineas, colorSolido);

    calcularNormales();
}

/* SET Y GET */

/// @brief Devuelve el ancho de la carretera
/// @return ancho
float Carretera::getAncho(){
    return ancho;
}

/// @brief Devuelve el largo de la carretera
/// @return largo
float Carretera::getLargo(){
    return largo;
}