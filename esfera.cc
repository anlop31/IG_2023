#include "auxiliar.h"
#include "malla.h"
#include "esfera.h"
#include "objrevolucion.h"

/// @brief Constructor de esfera con parámetros
/// @param num_vert_perfil 
/// @param num_instancias_perf 
/// @param radio 
Esfera::Esfera(const int num_vert_perfil = 10, const int num_instancias_perf = 20, const float radio = 1.0 ){
   std::vector<Tupla3f> vertices;

   this->radio = radio;

   vertices.resize(num_vert_perfil);

   float angulo = 2.0*M_PI / float(num_vert_perfil-1);

   for(int i = 0; i < num_vert_perfil; i++){
      vertices[i] = {
         radio*sin(angulo*i), // x
         radio*cos(angulo*i), // y
         0                    // z
      };
   }

   crearMalla(vertices, num_instancias_perf); 

   setColor(
      Tupla4f(1.0f, 0.0f, 0.0f, 1.0f), // color vértices
      Tupla4f(1.0f, 0.0f, 1.0f, 1.0f), // color líneas
      Tupla4f(1.0f, 1.0f, 0.0f, 1.0f)  // color sólido
   );

   modo_textura = ESFERICA;
}

/// @brief Obtener el radio de la esfera
/// @return El radio de la esfera
float Esfera::getRadio(){
   return radio;
}