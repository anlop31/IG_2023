#ifndef MUNDO_H_INCLUDED
#define MUNDO_H_INCLUDED

#include "auxiliar.h"
#include "malla.h"


class Mundo : public Malla3D{
   private:
   float lado;

   public:
   Mundo(const float l=1) ;

   float getLado();

};




#endif