#ifndef LUZPOSICIONAL_H_INCLUDED
#define LUZPOSICIONAL_H_INCLUDED

#include <auxiliar.h>
#include <luz.h>

class LuzPosicional : public Luz {
    public :
        LuzPosicional ( const Tupla3f & posicion ) ;

        LuzPosicional(  Tupla3f posicion, 
                        GLenum idLuzOpenGL,
                        Tupla4f colorAmbiente,
                        Tupla4f colorEspecular,
                        Tupla4f colorDifuso     );

        void variarPosicion(int x, int y, int z);
        void animarLuzPosicional();

};

#endif