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
#include "Textura.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

typedef enum {CILINDRICA, ESFERICA, PLANA} modoTextura;

class Malla3D
{
   public:

   // función que dibuja el objeto en modo diferido (usando VBOs)
   void draw() ;

   void calcularNormales();
   void asignarPuntosTextura(const modoTextura & modo);
   void asignarPuntosTexturaCuadro(const modoTextura & modo);
   
   void calcularCentro();
   void calcularCentroVista();
   bool actualizarColorSolidoOriginal();

   /* SET Y GET */
   // Texturas
   void setTextura(const std::string & n);

   // Colores
   void setColor(Tupla4f colorVertices, Tupla4f colorLineas, Tupla4f colorSolido);
   void setColorSeleccion(Tupla3f colorSeleccion);
   Tupla3f getColorSeleccion();
   void setColorSolido(Tupla4f nuevoColorSolido);
   std::vector<Tupla4f> getColorSolido();
   void setColorSeleccionSolido();
   void setColorSolidoOriginal();

   void setSeleccionado(bool valor);

   // Materiales
   void setMaterial(Material mat);
   Material getMaterial();
   void setMaterialSeleccion(Material matSelNuevo);
   Material getMaterialSeleccion();

   // Otros
   Tupla3f getCentro();
   Tupla3f getCentroTransformado();
   
   protected:

   // Material
   Material m;

   Material mSeleccion;
   
   // Textura
   Textura * textura = nullptr;
   bool es_cuadro = false;

   // Métodos VBOS
   GLuint CrearVBO (GLuint tipo_vbo, GLuint tam, GLvoid *puntero_ram);
   void crearVBOS();


   std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f ; // una terna de 3 enteros por cada cara o triángulo

   std::vector<Tupla3f> nc; // vector de normales de caras
   std::vector<Tupla3f> nv; // vector de normales de vértices

   std::vector<Tupla2f> ct; // vector de coordenadas de textura
   
   // Tabla de colores
   std::vector<Tupla4f> cVertices;
   std::vector<Tupla4f> cLineas;
   std::vector<Tupla4f> cSolido;

   std::vector<Tupla4f> cSolidoOriginal;

   Tupla3f cSeleccion; // color de seleccion
   
   Tupla3f centro; // vértice que está en el centro
   Tupla3f centroTransformado;

   bool seleccionado = false;

   // Variables vbo
   GLuint id_vbo_ver = 0;
   GLuint id_vbo_tri = 0;

   GLuint id_vbo_cd = 0; // vbo colores de los puntos
   GLuint id_vbo_cl = 0; // vbo colores de las lineas
   GLuint id_vbo_cs = 0; // vbo colores del solido
   GLuint id_vbo_nc = 0; // vbo normales de las caras
   GLuint id_vbo_nv = 0; // vbo normales de los vértices

   GLuint id_vbo_ct = 0; // vbo coordenadas de textura

   GLuint id_vbo_cSel = 0; // vbo colores de seleccion


   modoTextura modo_textura = PLANA;
} ;


#endif
