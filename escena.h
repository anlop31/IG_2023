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
#include "math.h"
#include "carretera.h"
#include "mundo.h"

#define MOUSE_WHEEL_UP 3
#define MOUSE_WHEEL_DOWN 4

#define UMBRAL 0.01

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,ANIMACION,GRADOS,LUCES,CAMARAS} menu;

typedef enum {MOVIENDO_CAMARA_FIRSTPERSON, CAMARA_EXAMINAR, DESACTIVADO} estado_raton;

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

    /* OBJETOS DE LA ESCENA */
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

    ObjPLY * vehiculo = nullptr;

    // Modelo jerárquico
    Robot * robot = nullptr;

    // Texturas
    Cuadro * cuadro = nullptr;

    // Carretera
    Cuadro * carretera_cuadro = nullptr;

    Carretera * carretera = nullptr;

    // Mundo
    Mundo * mundo = nullptr;

    /* LUCES */ 
    LuzPosicional * luz0 = nullptr;  
    LuzDireccional * luz1 = nullptr;
    LuzPosicional * luz2 = nullptr;  

    /****/

    // Variables para controlar la figura a visualizar
    bool hayCubo = false;
    bool hayPiramide = false;

    bool hayPLY_1 = false;
    bool hayPLY_2 = false;
    bool hayPLY_3 = false;
    

    // Variables para controlar el modo de visualización, y poder combinarlos
    bool modoPunto = false;
    bool modoLinea = false;
    bool modoSolido = true;

    // Iluminacion activa
    bool iluminacionActiva = true;

    // Variables para controlar las teclas pulsadas
    unsigned char ultimaPulsada = 'N';

    bool primeraVezPulsado0 = true;
    bool primeraVezPulsado1 = true;

    bool primeraVezPulsadoI = true;

    bool entradoMenu = false;

    // Variables cámara y pick
    int camaraActiva = 0;
    std::vector<Camara> camaras;

    int xant = 0,
        yant = 0;
    bool fin_pick = true;

    bool modoSeleccion = false;
    bool establecidoOriginal = true;

    estado_raton estadoRaton = DESACTIVADO;

    // Variables animación
    bool animacionAutomatica = true;
    bool animacionLuzDireccional = false;
    bool animacionLuzPosicional = false;
    int numGrado = 0; // grado de libertad seleccionado

   public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
    void animarModeloJerarquico();
    void animarLuzDireccional();
    void animarLuzPosicional();
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
    void activar_luces();
    void asignar_materiales();
    void dibujarObjetos(bool seleccion);
	void dibujar();

    // Camara e interaccion
    void clickRaton(int boton, int estado, int x, int y);
    void ratonMovido(int x, int y);
    void dibujaSeleccion(int x, int y);
    void pick(int x, int y);
    bool compararColores(Tupla3f pixel, Tupla3f color);
    Tupla3f centroObjeto(Tupla3f centro);
    bool invertirMatriz(const float m[16], float invOut[16]);

	// Interacción con la escena
    void mostrarMenuPrincipal();
    void mostrarMenuGradosLibertad();
    void mostrarMenuLuces();
    void mostrarMenuAnimacionAutomatica();
    void mostrarMenuSeleccionCamaras();
    void mostrarMenuVisualizacion();
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );


};
#endif
