#include "auxiliar.h"
#include "malla.h"
#include "esfera.h"
#include "objrevolucion.h"

Esfera::Esfera(const int num_vert_perfil = 10, const int num_instancias_perf = 20, const float radio = 1.0 ){
   std::vector<Tupla3f> vertices;

   vertices.resize(num_vert_perfil);

   float angulo = 2.0*M_PI/float(num_vert_perfil-1);

   for(int i=0; i<num_vert_perfil; i++){
      vertices[i] = {radio*sin(angulo*i),radio*cos(angulo*i), 0};
   }

   crearMalla(vertices, num_instancias_perf); 

   setColor(Tupla4f(1.0f, 0.0f, 0.0f, 1.0f), Tupla4f(1.0f, 0.0f, 1.0f, 1.0f), Tupla4f(1.0f, 1.0f, 0.0f, 1.0f));

}