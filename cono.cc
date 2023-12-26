#include "auxiliar.h"
#include "malla.h"
#include "cono.h"
#include "objrevolucion.h"

/// @brief Constructor de cono con parámetros
/// @param num_vert_perfil 
/// @param num_instancias_perf 
/// @param altura 
/// @param radio 
Cono::Cono(const int num_vert_perfil = 2, const int num_instancias_perf = 20, const float altura = 1.0, const float radio = 1.0){
   std::vector<Tupla3f> vertices;

   vertices.resize(num_vert_perfil);

   vertices[0] = Tupla3f({0, altura, 0});
   vertices[1] = Tupla3f({radio, 0, 0});
   vertices[2] = Tupla3f({0, 0, 0});

   crearMalla(vertices, num_instancias_perf);

   setColor(
      Tupla4f(1.0f, 0.0f, 0.0f, 1.0), // color vértices
      Tupla4f(1.0f, 1.0f, 0.0f, 1.0), // color líneas
      Tupla4f(1.0f, 0.0f, 1.0f, 1.0)  // color sólido
   );

   modo_textura = CILINDRICA;
}