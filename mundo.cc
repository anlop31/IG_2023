#include "auxiliar.h"
#include "malla.h"
#include "mundo.h"

/// @brief Constructor de cuadro
/// @param lado 
Mundo::Mundo(const float lado) {
    this->lado = lado;
    
    v.resize(7);

    f.resize(2);

    // inicializar la tabla de vértices
    v[0] = {0.0f, 0.0f, 0.0f}; // esquina inferior izquierda
    v[1] = {lado, 0.0f, 0.0f}; // esquina inferior derecha
    v[2] = {0.0f, lado, 0.0f}; // esquina superior izquierda
    v[3] = {lado, lado, 0.0f}; // esquina superior derecha

    v[4] = {0.0f, lado/10.0f, 0.0f}; // vertice intermedio para el lado izquierdo
    v[5] = {0.1f * lado, 0.0f, 0.0f}; // vertice intermedio para el lado inferior
    v[6] = {0.1f * lado, 0.1f * lado, 0.0f}; // vertice en mitad

    // inicializar las caras
    f[0] = {2, 0, 1};
    f[1] = {1, 3, 2}; 

    calcularNormales();


    // texturas
    modo_textura = PLANA;

    ct.resize(v.size());
    es_mundo = true;


    // colores
    Tupla4f colorVertices = Tupla4f(1.0f, 0.0f, 0.0f, 1.0f);
    Tupla4f colorLineas = Tupla4f(0.0f, 0.0f, 1.0f, 1.0f);
    Tupla4f colorSolido = Tupla4f(1.0f, 1.0f, 1.0f, 1.0f);

    setColor(colorVertices, colorLineas, colorSolido);

    calcularNormales();

}

/// @brief Devuelve la longitud del lado del mundo
/// @return lado
float Mundo::getLado(){
    return lado;
}
