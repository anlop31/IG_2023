#include "auxiliar.h"
#include "malla.h"
#include "cubo.h"

/// @brief Constructor de cubo
/// @param lado 
Cubo::Cubo(float lado)
{
   this->lado = lado;

   // inicializar la tabla de vértices
   v.resize(8);

   v[0] = {-lado/2, 0, lado/2};
   v[1] = {lado/2, 0, lado/2};
   v[2] = {lado/2, lado, lado/2};
   v[3] = {-lado/2, lado, lado/2};
   v[4] = {-lado/2, lado, -lado/2};
   v[5] = {-lado/2, 0, -lado/2};
   v[6] = {lado/2, 0, -lado/2};
   v[7] = {lado/2, lado, -lado/2};


   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   f.resize(12);

   // cambiar
   // cara frontal
   f[0] = {1, 2, 0};
   f[1] = {0, 2, 3};

   // cara izquierda
   f[2] = {5, 0, 4};
   f[3] = {4, 0, 3};

   // cara derecha
   f[4] = {1, 6, 2};
   f[5] = {2, 6, 7};

   // cara de atrás
   f[6] = {5, 4, 6};
   f[7] = {6, 4, 7};

   // cara de arriba
   f[8] = {3, 2, 4};
   f[9] = {4, 2, 7};

   // cara de abajo
   f[10] = {5, 6, 0};
   f[11] = {0, 6, 1};


   calcularNormales();
   calcularCentro();

}

/// @brief Devuelve el lado del cubo
/// @return lado
float Cubo::getLado(){
   return lado;
}