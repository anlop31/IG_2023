// #############################################################################
//
// Informática Gráfica D (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "auxiliar.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D
{
   public:

   // función que dibuja el objeto en modo diferido (usando VBOs)
   void draw() ;

   protected:

   GLuint CrearVBO (GLuint tipo_vbo, GLuint tam, GLvoid *puntero_ram);



   std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f ; // una terna de 3 enteros por cada cara o triángulo

   // completar P1: tabla de colores
   // Completar P1: vbo y método asociado
   
   // Variables vbo
   GLuint id_vbo_ver = 0;
   GLuint id_vbo_tri = 0;

   GLuint id_vbo_cd = 0; // vbo colores de los puntos
   GLuint id_vbo_cl = 0; // vbo colores de las lineas
   GLuint id_vbo_cs = 0; // vbo colores del solido

} ;


#endif
