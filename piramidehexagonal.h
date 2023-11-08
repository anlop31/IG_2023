// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: piramidepentagonal.h

//
// #############################################################################

#ifndef PIRAMIDE_HEXAGONAL_H_INCLUDED
#define PIRAMIDE_HEXAGONAL_H_INCLUDED

#include "auxiliar.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Pirámide de base pentagonal con base centrada en el origen 

class PiramideHexagonal: public Malla3D
{
   public:
      PiramideHexagonal(float h=1.0,float r=0.5, float r_trunc=0.25);

} ;




#endif
