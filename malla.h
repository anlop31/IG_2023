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
#include "Material.h"

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
   void setColor(Tupla4f colorVertices, Tupla4f colorLineas, Tupla4f colorSolido);
   void setMaterial(Material mat);
   void calcularNormales();

   protected:

   // Material
   // Material m; // definir un constructor por defecto

   GLuint CrearVBO (GLuint tipo_vbo, GLuint tam, GLvoid *puntero_ram);



   std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f ; // una terna de 3 enteros por cada cara o triángulo

   // vector de normales de caras
   std::vector<Tupla3f> nc;
   // vector de normales de vértices
   std::vector<Tupla3f> nv;

   // completar P1: tabla de colores
   // Completar P1: vbo y método asociado
   
   // Tabla de colores
   std::vector<Tupla4f> cVertices;
   std::vector<Tupla4f> cLineas;
   std::vector<Tupla4f> cSolido;

   // Variables vbo
   GLuint id_vbo_ver = 0;
   GLuint id_vbo_tri = 0;

   GLuint id_vbo_cd = 0; // vbo colores de los puntos
   GLuint id_vbo_cl = 0; // vbo colores de las lineas
   GLuint id_vbo_cs = 0; // vbo colores del solido
   GLuint id_vbo_nc = 0; // vbo normales de las caras
   GLuint id_vbo_nv = 0; // vbo normales de los vértices


} ;


#endif
