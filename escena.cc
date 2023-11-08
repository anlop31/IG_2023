

#include "auxiliar.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....
#include "objply.h"
#include "ply_reader.h"

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
   Front_plane       = 50.0;
   Back_plane        = 2000.0;
   Observer_distance = 4*Front_plane;
   Observer_angle_x  = 0.0 ;
   Observer_angle_y  = 0.0 ;

   ejes.changeAxisSize( 5000 );

   // crear los objetos de la escena....
   // .......completar: ...
   // .....

   cubo = new Cubo(60.0); // cubo creado
   piramide = new PiramideHexagonal(80.0, 80.0, 40.0); // piramide creada

   esfera = new Esfera(30, 30, 40);
   cilindro = new Cilindro(4, 10, 50.0, 50.0); 
   cono = new Cono(3, 10, 70, 25);

   ObjPLY_1 = new ObjPLY("./plys/ant.ply");
   ObjPLY_2 = new ObjPLY("./plys/beethoven.ply");
   ObjPLY_2->setColor(Tupla4f(0.0f, 1.0f, 0.0f, 1.0f), Tupla4f(0.0f, 0.0f, 1.0f, 1.0f), Tupla4f(1.0f, 0.0f, 0.0f, 1.0f));
   ObjPLY_3 = new ObjRevolucion("./plys/peon.ply", 10, false, true);
   ObjPLY_3->setColor(Tupla4f(1.0f, 1.0f, 0.0f, 1.0f), Tupla4f(0.0f, 0.0f, 1.0f, 1.0f), Tupla4f(0.1f, 0.6f, 0.1f, 1.0f));

   LuzPos = new LuzPosicional({200, 100, 200}, 1, {0.2, 0.2, 0.2, 1}, {0.6, 0.6, 0.6, 1.0}, {1.0, 1.0, 1.0, 1.0});   
   LuzDir = new LuzDireccional({20, 20}, 1, {0.2, 0.2, 0.2, 1}, {0.6, 0.6, 0.6, 1.0}, {1.0, 1.0, 1.0, 1.0});
    
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer

   glEnable( GL_CULL_FACE ); // se habilita cull face

   // para evitar que se altere la longitud de las normales:
   glEnable(GL_NORMALIZE);

   // Modo de visualización sombreado suave
   // glShadeModel(GL_SMOOTH);
   // glShadeModel(GL_FLAT);


	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );
}


void Escena::activar_luces(){
   glEnable(GL_LIGHTING); // activamos luces
   glShadeModel(GL_SMOOTH); // sombreado suave

   if(LuzPos != nullptr){
      glPushMatrix();
         LuzPos->activar();
      glPopMatrix();
   }


   if(LuzDir != nullptr){
      glPushMatrix();
         LuzDir->activar();
      glPopMatrix();
   }
}


void Escena::dibujarObjetos(){
   //// CUBO
   if(hayCubo){
      cubo->draw();
      std::cout << "---Cubo dibujado" << std::endl;
   }
   else{
      std::cout << "---Cubo ocultado" << std::endl;
   }


   //// PIRAMIDE
   if(hayPiramide){
      piramide->draw();
      std::cout << "---Piramide dibujada" << std::endl;
   }
   else{
      std::cout << "---Piramide ocultada" << std::endl;
   }


   //// PLYs
   if(hayPLY_1){
      std::cout << "---OBJPLY1 dibujado" << std::endl;
      glPushMatrix();
         glScalef(2, 2, 2);
         ObjPLY_1->draw();
      glPopMatrix();
   }
   else{
      std::cout << "---OBJPLY1 ocultado" << std::endl;
   }

   if(hayPLY_2){
      std::cout << "---OBJPLY2 dibujado" << std::endl;
      glPushMatrix();
         glScalef(10, 10, 10);
         ObjPLY_2->draw();
      glPopMatrix();
   }
   else{
      std::cout << "---OBJPLY2 ocultado" << std::endl;
   }

   if(hayPLY_3){
      std::cout << "---OBJPLY3 dibujado" << std::endl;
      glPushMatrix();
         glScalef(15, 15, 15);
         ObjPLY_3->draw();
      glPopMatrix();
   }
   else{
      std::cout << "---OBJPLY3 ocultado" << std::endl;
   }


   //// ESFERA
   glPushMatrix();
      glTranslatef(0, 160, 0);
      esfera->draw();
   glPopMatrix();


   //// CILINDRO
   glPushMatrix();
      glTranslatef(-150, 0, 0);
      cilindro->draw();
   glPopMatrix();


   //// CONO
   glPushMatrix();
      glTranslatef(100, 0, -100);
      cono->draw();
   glPopMatrix();
}


// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
   // no puedo usar opengl fuera de aqui
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();

   // ejes en color plano
   glDisable(GL_LIGHTING);
   ejes.draw();


   // asignar materiales
   if (iluminacionActiva)
      activar_luces();

   // para estos modos, las luces deben estar desactivadas
   // si hay luz, el color deja de tener efecto.
   if (modoPunto) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); // puntos (front)
      std::cout << "MODO PUNTOS ACTIVO" << std::endl;
      dibujarObjetos();
   }
   if (modoLinea) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // lineas
      std::cout << "MODO LINEAS ACTIVO" << std::endl;
      dibujarObjetos();
   }
   if (modoSolido) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // solido (back)
      std::cout << "MODO SOLIDO ACTIVO" << std::endl;
      dibujarObjetos();
   }


    
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir=false;
   switch( toupper(tecla) )
   {
      case 'Q' :
         if (modoMenu!=NADA)
            modoMenu=NADA;            
         else {
            salir=true ;
         }
         break ;
      case 'O' :
         // ESTAMOS EN MODO SELECCION DE OBJETO
         modoMenu=SELOBJETO; 
         break ;
      case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         modoMenu=SELVISUALIZACION;
         break ;
      case '1':
         hayPLY_1 = !hayPLY_1;
         break;
      case '2':
         hayPLY_2 = !hayPLY_2;
         break;
      case '3':
         hayPLY_3 = !hayPLY_3;
         break;
   }

   // SELECCION OBJETO
   if(modoMenu == SELOBJETO)
      switch (toupper(tecla)){
         case 'C': 
            hayCubo = !hayCubo; // cubo
            break;
         case 'P': 
            hayPiramide = !hayPiramide; // modo lineas
            break;
      }

   // SELECCION VISUALIZACION
   if(modoMenu == SELVISUALIZACION)
      switch (toupper(tecla)){
         case 'D': 
            modoPunto = !modoPunto; // modo puntos
            break;
         case 'L': 
            modoLinea = !modoLinea; // modo lineas
            break;
         case 'S': 
            modoSolido = !modoSolido; // modo solido
            break;
      }


   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy ;
   glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}
