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
#include "robot.h"
#include "cuadro.h"
#include "camara.h"

#define MOUSE_WHEEL_UP 3
#define MOUSE_WHEEL_DOWN 4

#define UMBRAL 0.01

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,ANIMACION,GRADOS,LUCES,CAMARAS} menu;

typedef enum {MOVIENDO_CAMARA_FIRSTPERSON, MOVIENDO_CAMARA_EXAMINAR, DESACTIVADO} estado_raton;

// typedef enum {BOTON_DERECHO, BOTON_IZQUIERDO, RUEDA} boton;

// typedef enum {PULSADO, SIN_PULSAR} estadoBoton;

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
    void change_projection ();
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
   ObjRevolucion * peon1 = nullptr;
   ObjRevolucion * peon2 = nullptr;

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
    LuzPosicional * luz0 = nullptr;  
    LuzDireccional * luz1 = nullptr;
    LuzPosicional * luz2 = nullptr;  

    // Iluminacion activa
    bool iluminacionActiva = false;

    unsigned char ultimaPulsada = 'N';

    bool primeraVezPulsado0 = true;
    bool primeraVezPulsado1 = true;

    bool modoSeleccion = false;
    bool establecidoOriginal = true;

    // texturas
    Cuadro * cuadro = nullptr;

   public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
    void animarModeloJerarquico(); // animacion
    void animarLuzDireccional();
    void animarLuzPosicional();
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
    void dibujarObjetos(bool seleccion);
	void dibujar() ;
    void activar_luces();
    void asignar_materiales();

    // Camara e interaccion
    void clickRaton(int boton, int estado, int x, int y);
    void ratonMovido(int x, int y);
    void dibujaSeleccion(int x, int y);
    void pick(int x, int y);
    bool compararColores(Tupla3f pixel, Tupla3f color);

    int camaraActiva = 0;
    std::vector<Camara> camaras;

    int xant = 0,
        yant = 0;
    bool fin_pick = true;

    estado_raton estadoRaton = MOVIENDO_CAMARA_FIRSTPERSON;

    // animacion
    bool animacionAutomatica = false;
    bool animacionLuzDireccional = false;
    bool animacionLuzPosicional = false;
    int numGrado = 0; // grado de libertad seleccionado

    // modelo jerárquico
    Robot * robot = nullptr;


	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );


};
#endif
