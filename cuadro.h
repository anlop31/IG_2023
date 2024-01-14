#ifndef CUADRO_H_INCLUDED
#define CUADRO_H_INCLUDED

#include "auxiliar.h"
#include "malla.h"


class Cuadro : public Malla3D{
   private:
   float lado;

   public:
   Cuadro(const float l=1) ;

   float getLado();

};




#endif