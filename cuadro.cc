#include "auxiliar.h"
#include "malla.h"
#include "cuadro.h"

/// @brief Constructor de cuadro
/// @param lado 
Cuadro::Cuadro(const float lado) {
    this->lado = lado;
    
    v.resize(4);

    f.resize(2);

    // inicializar la tabla de vértices
    v[0] = {0.0f, 0.0f, 0.0f};
    v[1] = {lado, 0.0f, 0.0f};
    v[2] = {0.0f, lado, 0.0f};
    v[3] = {lado, lado, 0.0f};

    // inicializar las caras
    f[0] = {2, 0, 1};
    f[1] = {1, 3, 2}; 

    calcularNormales();


    // texturas
    modo_textura = PLANA;

    ct.resize(v.size());
    es_cuadro = true;


    // colores
    Tupla4f colorVertices = Tupla4f(1.0f, 0.0f, 0.0f, 1.0f);
    Tupla4f colorLineas = Tupla4f(0.0f, 0.0f, 1.0f, 1.0f);
    Tupla4f colorSolido = Tupla4f(1.0f, 1.0f, 1.0f, 1.0f);

    setColor(colorVertices, colorLineas, colorSolido);

    calcularNormales();

}

/// @brief Devuelve la longitud del lado del cuadro
/// @return lado
float Cuadro::getLado(){
    return lado;
}
