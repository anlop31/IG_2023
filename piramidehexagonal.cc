#include "auxiliar.h"
#include "malla.h"
#include "piramidehexagonal.h"
#include "math.h"

/// @brief Constructor de pirámide hexagonal truncada
/// @param h Altura de la pirámide
/// @param r Radio de la base de la pirámide
/// @param r_trunc Radio de la parte de arriba de la pirámide
PiramideHexagonal::PiramideHexagonal(float h, float r, float r_trunc)
{

      altura = h;
      radioBase = r;
      radioTruncado = r_trunc;

      // inicializar la tabla de vértices
      v.resize(14);

      float angulo = (2*M_PI)/6; // 6 lados

      // Base hexagonal
      for(int i=0; i<6; i++){
            v[i](2) = r*sin(i*angulo); // z
            v[i](0) = r*cos(i*angulo); // x
            v[i](1) = 0; // y
      }


      v[6] = {0, 0, 0}; // punto central base

      // Hexagono truncado
      for(int i=7; i<13; i++){
            v[i](2) = r_trunc*sin(i*angulo); // z
            v[i](0) = r_trunc*cos(i*angulo); // x
            v[i](1) = h; // y
      }

      v[13] = {0, h, 0}; // punto central hexagono truncado


      // inicializar la tabla de caras o triángulos:

      // (es importante en cada cara ordenar los vértices en sentido contrario
      //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

      f.resize(24);

      // Caras de la base
      f[0] = {0, 1, 6}; 
      f[1] = {1, 2, 6};
      f[2] = {2, 3, 6};
      f[3] = {3, 4, 6};
      f[4] = {4, 5, 6};
      f[5] = {5, 0, 6};

      // Caras laterales
      f[6] = {1, 0, 7};
      f[7] = {7, 0, 12};

      f[8] = {2, 1, 7};
      f[9] = {2, 7, 8};

      f[10] = {3, 2, 9};
      f[11] = {9, 2, 8};
      //
      f[12] = {4, 3, 9};
      f[13] = {4, 9, 10};

      f[14] = {4, 10, 11};
      f[15] = {5, 4, 11};

      f[16] = {11, 0, 5};
      f[17] = {11, 12, 0};

      // caras arriba
      f[18] = {13, 7, 12}; 
      f[19] = {13, 8, 7};
      f[20] = {13, 9, 8};
      f[21] = {13, 10, 9};
      f[22] = {13, 11, 10};
      f[23] = {13, 12, 11};


      // inicializar la/s tabla/s de colores

      calcularNormales();


}

/* SET Y GET */

/// @brief Devuelve la altura de la pirámide
/// @return altura
float PiramideHexagonal::getAltura(){
      return altura;
}

/// @brief Devuelve el radio de la base de la pirámide
/// @return radioBase
float PiramideHexagonal::getRadioBase(){
      return radioBase;
}

/// @brief Devuelve el radio de la base truncada de la pirámide
/// @return radioTruncado
float PiramideHexagonal::getRadioTruncado(){
      return radioTruncado;
}