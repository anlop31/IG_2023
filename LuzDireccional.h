#ifndef LUZDIRECCIONAL_H_INCLUDED
#define LUZDIRECCIONAL_H_INCLUDED

#include <luz.h>
#include <auxiliar.h>


class LuzDireccional : public Luz
{
    protected :
        float alpha ;
        float beta ;
        Tupla4f posicion_original;
        int step = 0;
        bool aumentarColor = true;
    public :
    // inicializar la fuente de luz
    LuzDireccional(     Tupla2f direccion,
                        GLenum idLuzOpenGL, 
                        Tupla4f colorAmbiente,
                        Tupla4f colorEspecular,
                        Tupla4f colorDifuso     );

    LuzDireccional ( const Tupla2f & orientacion ) ;
    
    // Cambiar ángulo:
    void variarAnguloAlpha ( float incremento ) ;
    void variarAnguloBeta ( float incremento ) ;
    void cambiarColor();
    void animarLuzDireccional();
    void actualizarPosicion();
};


#endif