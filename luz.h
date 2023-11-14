#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include <auxiliar.h> 

class Luz{
    protected:
        Tupla4f posicion;
        GLenum id;
        Tupla4f colorAmbiente;
        Tupla4f colorDifuso;
        Tupla4f colorEspecular;

        bool activada;
    public:
        Luz();
        void activar();
        bool estadoActivada();
        void setActivada(const bool nuevo_valor);
};

#endif