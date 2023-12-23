#include "auxiliar.h"
#include "malla.h"
#include "cuadro.h"

Cuadro::Cuadro(const float lado) {

    v.resize(4);

    f.resize(2);

    // inicializar la tabla de vértices
    v[0] = {0.0f, 0.0f, 0.0f};
    v[1] = {lado, 0.0f, 0.0f};
    v[2] = {0.0f, lado, 0.0f};
    v[3] = {lado, lado, 0.0f};

    // inicializar las caras
    // f[0] = {0, 1, 3}; // par
    // f[1] = {3, 2, 0}; // impar
    f[0] = {2, 0, 1}; // par
    f[1] = {1, 3, 2}; // impar

    calcularNormales();


    // texturas
    modo_textura = PLANA;

    ct.resize(v.size());
    asignarPuntosTexturaCuadro(modo_textura);

    // calcularCentro(); // para que?


    // colores
    Tupla4f colorVertices = Tupla4f(1.0f, 0.0f, 0.0f, 1.0f);
    Tupla4f colorLineas = Tupla4f(0.0f, 0.0f, 1.0f, 1.0f);
    Tupla4f colorSolido = Tupla4f(1.0f, 0.0f, 0.0f, 1.0f);

    setColor(colorVertices, colorLineas, colorSolido);

}