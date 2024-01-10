// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cubo.h

//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "auxiliar.h"
#include "malla.h"

#define EPSILON 0.0001


// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad por defecto
// (tiene 9 vertices y 6 caras)

class ObjRevolucion : public Malla3D
{
   public:
       ObjRevolucion();
   ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true) ;
   ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true) ;
protected:
    void crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias);
    void asignarPuntosTextura(const modoTextura & modo);

    std::vector<Tupla3f> perfil;
    int num_instancias = 0;
    int N, M;

} ;




#endif
