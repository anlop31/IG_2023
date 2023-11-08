#include "auxiliar.h"
#include "cilindro.h"

Cilindro::Cilindro(const int num_vert_perfil = 2, const int num_instancias_perf = 20, const float altura = 1.0, const float radio = 1.0 ){
   std::vector<Tupla3f> vertices;

   vertices.resize(num_vert_perfil);
   vertices[0] = {0, altura, 0}; // polo norte
   vertices[1] = {radio, altura, 0};
   vertices[2] = {radio, 0, 0};
   vertices[3] = {0, 0, 0}; // polo sur

   
   crearMalla(vertices, num_instancias_perf);
   setColor(Tupla4f(1.0f, 0.0f, 1.0f, 1.0f), Tupla4f(0.0f, 1.0f, 1.0f, 1.0f), Tupla4f(0.0f, 0.0f, 1.0f, 1.0f));
}