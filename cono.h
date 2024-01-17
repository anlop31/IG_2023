#ifndef CONO_H_INCLUDED
#define CONO_H_INCLUDED

#include "auxiliar.h"
#include "objrevolucion.h"


class Cono : public ObjRevolucion
{
      private:
      float altura, radio;

      public:
      Cono( const int num_vert_perfil,
            const int num_instancias_perf,
            const float altura,
            const float radio );

      float getRadio();
      float getAltura();
};

#endif