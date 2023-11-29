#ifndef BRAZO_H_INCLUDED
#define BRAZO_H_INCLUDED

#include "auxiliar.h"
#include "objrevolucion.h"

class Brazo : public ObjRevolucion
{

    // sera un cilindro

   public:
    Brazo();
    void draw();
};

#endif