#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "piramidehexagonal.h"
#include "objply.h"
#include "objrevolucion.h"
#include "esfera.h"
#include "cilindro.h"
#include "cono.h"
#include <LuzDireccional.h>
#include <LuzPosicional.h>

typedef enum {NADA, SELOBJETO,SELVISUALIZACION} menu;
class Escena
{

   private:

   

 // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)
       
       // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();
    


   void clear_window();

   menu modoMenu=NADA;
   // Objetos de la escena
   Ejes ejes;
   Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
   PiramideHexagonal * piramide = nullptr ; // es importante inicializarlo a 'nullptr'
   Esfera * esfera = nullptr;
   Cilindro * cilindro = nullptr;
   Cono * cono = nullptr;
   
   ObjPLY * ObjPLY_1 = nullptr;
   ObjPLY * ObjPLY_2 = nullptr;
   ObjRevolucion * ObjPLY_3 = nullptr;

    // variables para controlar la figura a visualizar
    bool hayCubo = false;
    bool hayPiramide = false;

    bool hayPLY_1 = false;
    bool hayPLY_2 = false;
    bool hayPLY_3 = false;
    

    // variables para controlar el modo de visualización, y poder combinarlos
    bool modoPunto = false;
    bool modoLinea = false;
    bool modoSolido = true;


    /* LUCES */ 
    Tupla2f direccion={(float)M_PI/2,(float)M_PI/2};
    LuzDireccional * LuzDir = nullptr;
    LuzPosicional * LuzPos = nullptr;  
    // Iluminacion activa
    bool iluminacionActiva = false;

   public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
    void dibujarObjetos();
	void dibujar() ;
    void activar_luces();

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

};
#endif
