#ifndef ESFERA_H_INCLUDED
#define ESFERA_H_INCLUDED

#include "auxiliar.h"
#include "objrevolucion.h"


class Esfera : public ObjRevolucion
{
   float radio;

   public:
   Esfera(  const int num_vert_perfil,
            const int num_instancias_perf,
            const float radio );

   float getRadio();
};

#endif