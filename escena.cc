

#include "auxiliar.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....
#include "objply.h"
#include "ply_reader.h"

using namespace std;

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

   /* OBJETOS */

   // Objetos iniciales
   cubo = new Cubo(60.0); // cubo creado
   piramide = new PiramideHexagonal(80.0, 80.0, 40.0); // piramide creada

   // Objetos de revolución
   esfera = new Esfera(30, 30, 40);
   cilindro = new Cilindro(4, 10, 50.0, 50.0); 
   cono = new Cono(3, 10, 70, 25);

   // Objetos PLY
   ObjPLY_1 = new ObjPLY("./plys/ant.ply");
   ObjPLY_2 = new ObjPLY("./plys/beethoven.ply");
   ObjPLY_2->setColor(Tupla4f(0.0f, 1.0f, 0.0f, 1.0f), Tupla4f(0.0f, 0.0f, 1.0f, 1.0f), Tupla4f(1.0f, 0.0f, 0.0f, 1.0f));
   ObjPLY_3 = new ObjRevolucion("./plys/peon.ply", 10, false, true);
   ObjPLY_3->setColor(Tupla4f(1.0f, 1.0f, 0.0f, 1.0f), Tupla4f(0.0f, 0.0f, 1.0f, 1.0f), Tupla4f(0.1f, 0.6f, 0.1f, 1.0f));

   peon1 = new ObjRevolucion("./plys/peon.ply", 10, false, true);
   peon2 = new ObjRevolucion("./plys/peon.ply", 10, false, true);


   /* MODELO JERÁRQUICO */
   robot = new Robot();


   /* Asignar materiales a los objetos */
   asignar_materiales();


   /* LUCES */
   luz0 = new LuzPosicional(
      {-200, 120, 200}, // posición en coordenadas
      GL_LIGHT0, // id
      {0.0, 0.0, 0.0, 1}, // color ambiente (negro)
      {1.0, 1.0, 1.0, 1.0}, // color especular (blanco)
      {1.0, 1.0, 1.0, 1.0}); // color difuso (blanco) [R-G-B]

   luz1 = new LuzDireccional(
      {0, 0}, // posicion (alfa, beta)
      GL_LIGHT1, // id
      {0.0, 0.0, 0.0, 1.0}, // color ambiente (negro)
      {1.0, 1.0, 1.0, 1.0}, // color especular (blanco)
      {1.0, 1.0, 1.0, 1.0}); // color difuso (verde) [R-G-B]

   luz2 = new LuzPosicional(
      {200, 120, 200}, // posición en coordenadas
      GL_LIGHT2, // id
      {0.0, 0.0, 0.0, 1}, // color ambiente (negro)
      {1.0, 1.0, 1.0, 1.0}, // color especular (blanco)
      {1.0, 1.0, 1.0, 1.0}); // color difuso (blanco) [R-G-B]
//
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


void Escena::animarModeloJerarquico() {
   if(animacionAutomatica)
      robot->animarModeloJerarquico();
}

void Escena::asignar_materiales(){
   // Constructor material: (difuso, especular, ambiente, brillo)

   // Lista de materiales:
   Material oro ({0.24725, 0.1995, 0.0745, 1}, {0.75164, 0.60648, 0.22648, 1}, {0.628281, 0.555802, 0.366065, 1}, 0.8*128.0f);
   Material ruby({0.1745, 0.01175, 0.01175, 1}, {0.61424, 0.04136, 0.04136, 1}, {0.727811, 0.626959, 0.626959, 1}, 128.0f * 0.6f );
   Material perla({0.25, 0.20725, 0.20725, 1}, {1, 0.829, 0.829, 1}, {0.296648, 0.296648, 0.296648, 1}, 128.0f * 0.088);
   Material esmeralda({0.0215, 0.1745, 0.0215, 1}, {0.07568, 0.61424, 0.07568, 1}, {0.633, 0.727811,0.633, 1}, 0.6 * 128.0f);
   Material plata({0.19225, 0.19225, 0.19225, 1}, {0.50754, 0.50754, 0.50754, 1}, {0.508273,0.508273, 0.508273, 1}, 0.4*128.0f);
   Material turquesa({0.1, 0.18725, 0.1745, 1}, {0.396, 0.74151, 0.69102, 1}, {0.297254, 0.30829, 0.306678, 1} ,0.1 * 128.0f);
   Material blanco({1.0, 1.0, 1.0, 1}, {1.0, 1.0, 1.0, 1}, {1.0, 1.0, 1.0, 1} , 0.1 * 128.0f);


   // blanco puramente difuso sin brillos especulares
   Material mat_peon_blanco({1.0, 1.0, 1.0, 1}, {0.0, 0.0, 0.0, 1}, {1.0, 1.0, 1.0, 1} , 0);
   
   // negro con material especular de alto brillo
   Material mat_peon_negro({0.0, 0.0, 0.0, 1}, {1.0, 1.0, 1.0, 1}, {0.2, 0.2, 0.2, 1} , 128.0f);


   // Asociamos materiales a los objetos
   cubo->setMaterial(ruby);
   piramide->setMaterial(esmeralda);

   esfera->setMaterial(plata);
   cilindro->setMaterial(turquesa);
   cono->setMaterial(oro);

   peon1->setMaterial(mat_peon_blanco);
   peon2->setMaterial(mat_peon_negro);

   ObjPLY_1->setMaterial(turquesa);
   ObjPLY_2->setMaterial(turquesa);


   robot->setMaterialRobot(oro);
}


void Escena::activar_luces(){
   glEnable(GL_LIGHTING); // activamos luces
   glShadeModel(GL_SMOOTH); // sombreado suave

   if(luz0 != nullptr){
      glPushMatrix();
         luz0->activar();
      glPopMatrix();
   }

   if(luz1 != nullptr){
      glPushMatrix();
         luz1->activar();
      glPopMatrix();
   }

   if(luz2 != nullptr){
      glPushMatrix();
         luz2->activar();
      glPopMatrix();
   }
}


void Escena::dibujarObjetos(){
   //// CUBO
   glPushMatrix();
      glTranslatef(-180, 0, -120); 
      cubo->draw();
   glPopMatrix();


   //// PIRAMIDE

   glPushMatrix();
      glTranslatef(200, 0, -150); 
      piramide->draw();
   glPopMatrix();


   /*    PLYS   */
   //// HORMIGA (ObjPLY_1)
   glPushMatrix();
      glTranslatef(100, 0, 100);
      glScalef(2, 2, 2); 
      ObjPLY_1->draw(); // hormiga
   glPopMatrix();


   //// BEETHOVEN (ObjPLY_2)
   glPushMatrix();
      glTranslatef(200, 0, 0);
      glScalef(10, 10, 10);
      ObjPLY_2->draw(); // Beethoven
   glPopMatrix();


   // PEÓN BLANCO (material puramente difuso, sin brillos especulares)
   glPushMatrix();
      glTranslatef(-120, 0, 80);
      glScalef(15, 15, 15);
      peon1->draw(); // peón
   glPopMatrix();

   //// PEÓN NEGRO (material especular de alto brillo)
   glPushMatrix();
      glTranslatef(-180, 0, 80);
      glScalef(15, 15, 15);
      peon2->draw(); // peón
   glPopMatrix();


   /*    OBJETOS DE REVOLUCIÓN   */
   //// ESFERA
   glPushMatrix();
      glTranslatef(-200, 130, -100);
      esfera->draw();
   glPopMatrix();


   //// CILINDRO
   glPushMatrix();
      glTranslatef(-150, 0, 0);
      cilindro->draw();
   glPopMatrix();


   //// CONO
   glPushMatrix();
      glTranslatef(100, 0, 0);
      cono->draw();
   glPopMatrix();

   //// ROBOT
   glPushMatrix();
      glTranslatef(0, 0, -200);
      robot->draw();
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


   if (iluminacionActiva){
      activar_luces();
   }


   if (modoPunto) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); // puntos (front)
      // cout << "-MODO PUNTOS ACTIVO-" << endl;
      dibujarObjetos();
   }
   if (modoLinea) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // lineas
      // cout << "-MODO LINEAS ACTIVO-" << endl;
      dibujarObjetos();
   }
   if (modoSolido) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // solido (back)
      // cout << "-MODO SOLIDO ACTIVO-" << endl;
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
         if (modoMenu!=NADA){
            modoMenu=NADA;            
            cout << "-->VOLVIENDO A MENÚ PRINCIPAL" << endl;
         }
         else {
            salir=true ;
         }
         break ;
      case 'O' :
         // ESTAMOS EN MODO SELECCION DE OBJETO
         cout << "-->ENTRANDO A MENÚ DE SELECCIÓN DE OBJETO" << endl;
         modoMenu=SELOBJETO; 
         break ;
      case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         cout << "-->ENTRANDO A MENÚ DE VISUALIZACIÓN" << endl;
         modoMenu=SELVISUALIZACION;
         break ;
      case 'A':
         if(modoMenu==NADA){ // si no está en ningun submenú
            animacionAutomatica = !animacionAutomatica;
            cout << "-->ANIMACIÓN AUTOMÁTICA " << (animacionAutomatica ? "ACTIVADA" : "DESACTIVADA") << endl;
            modoMenu=ANIMACION;
         }
         break;
      case 'M': // se desactiva animacion automatica
         cout << "-->ENTRANDO A SELECCIÓN DE GRADOS DE LIBERTAD" << endl;
         modoMenu=GRADOS;
   }

   // SELECCION OBJETO
   // if(modoMenu == SELOBJETO)
   //    switch (toupper(tecla)){
   //       case 'C': 
   //          hayCubo = !hayCubo; // cubo
   //          break;
   //       case 'P': 
   //          hayPiramide = !hayPiramide; // modo lineas
   //          break;
   //    }

   // SELECCION VISUALIZACION
   if(modoMenu == SELVISUALIZACION)
      switch (toupper(tecla)){
         case 'P': // modo puntos
            if(iluminacionActiva){
               iluminacionActiva = false;
            }
            modoPunto = !modoPunto; 
            cout << "--MODO PUNTOS " << (modoPunto ? "ACTIVADO" : "DESACTIVADO") << endl;
            break;
         case 'L': // modo líneas
            if(iluminacionActiva){
               iluminacionActiva = false;
            }
            modoLinea = !modoLinea; 
            cout << "--MODO LÍNEAS " << (modoLinea ? "ACTIVADO" : "DESACTIVADO") << endl;
            break;
         case 'S': // modo sólido
            if(iluminacionActiva){
               iluminacionActiva = false;
            }
            modoSolido = !modoSolido; 
            cout << "--MODO SÓLIDO " << (modoSolido ? "ACTIVADO" : "DESACTIVADO") << endl;
            break;
         case 'T': // activar iluminación
            iluminacionActiva = !iluminacionActiva;
            if(iluminacionActiva){
               modoLinea = false;
               modoPunto = false;
               modoSolido = true;
            }
            cout << "--ILUMINACIÓN " << (iluminacionActiva ? "ACTIVADA" : "DESACTIVADA") << endl;

            break;
         case '0': // GL_LIGHT0
            if (luz0 != nullptr)
               luz0->setActivada(!luz0->estadoActivada());
            cout << "--LUZ 0 " << (luz0->estadoActivada() ? "ACTIVADA" : "DESACTIVADA") << endl;
            break;
         case '1': // GL_LIGHT1
            if (luz1 != nullptr)
                  luz1->setActivada(!luz1->estadoActivada());
            cout << "--LUZ 1 " << (luz1->estadoActivada() ? "ACTIVADA" : "DESACTIVADA") << endl;

            break;
         case '2': // GL_LIGHT2
            if (luz2 != nullptr)
                  luz2->setActivada(!luz2->estadoActivada());
            cout << "--LUZ 2 " << (luz2->estadoActivada() ? "ACTIVADA" : "DESACTIVADA") << endl;
            break;
         case 'A': // variar angulo alfa
            ultimaPulsada = 'A';
            cout << "--CAMBIAR ÁNGULO ALFA..." << endl;
            break;
         case 'B': // variar angulo beta
            ultimaPulsada = 'B';
            cout << "--CAMBIAR ÁNGULO BETA..." << endl;
            break;
         case '>': // incrementa el angulo
            if(ultimaPulsada == 'A'){
               cout << "--INCREMENTA ALFA" << endl;
               luz1->variarAnguloAlpha(-5*M_PI/180);
            }
            else if(ultimaPulsada == 'B'){ // la B
               cout << "--INCREMENTA BETA" << endl;
               luz1->variarAnguloBeta(-5*M_PI/180);
            }
            break;
         case '<': // decrementa el angulo
            if(ultimaPulsada == 'A'){
               luz1->variarAnguloAlpha(-5*M_PI/180);
               cout << "--DECREMENTA ALFA" << endl;
            }
            else if(ultimaPulsada == 'B'){ // la B
               luz1->variarAnguloBeta(-5*M_PI/180);
               cout << "--DECREMENTA BETA" << endl;
            }
            break;
      }


   if(modoMenu == ANIMACION){
      switch (toupper(tecla))
      {
      case '+':
         /* aumenta velocidad */
         robot->cambiarVelocidad(2);
         break;
      case '-':
         /* disminuye velocidad */
         robot->cambiarVelocidad(-2);
         break;
      
      default:
         break;
      }
   }

   if(modoMenu == GRADOS){
      switch(toupper(tecla)){
         case '0':
            numGrado = 0; 
            cout << "--GRADO 0 SELECCIONADO (PIERNAS)" << endl;
            break;
         case '1':
            numGrado = 1;
            cout << "--GRADO 1 SELECCIONADO (BRAZOS)" << endl;
            break;
         case '2':
            numGrado = 2;
            cout << "--GRADO 2 SELECCIONADO (MOVIMIENTO)" << endl;
            break;
         case '+':
            switch (numGrado)
            {
               case 0:
                  if(!primeraVezPulsado0){
                     robot->cambiarSentidosPiernas();
                     primeraVezPulsado0 = true;
                  }
                  robot->modificaGiroPiernas(5);
                  break;
               case 1:
                  if(!primeraVezPulsado1){
                     robot->cambiarSentidosBrazos();
                     primeraVezPulsado1 = true;
                  }
                  robot->modificaGiroBrazos(5);
                  break;
               case 2:
                  robot->modificaDesplazamiento(5);
                  break;
               default:
                  break;
            }
            break;
         case '-':
            switch (numGrado)
            {
               case 0:
                  if(primeraVezPulsado0){
                     robot->cambiarSentidosPiernas();
                     primeraVezPulsado0 = false;
                  }
                  robot->modificaGiroPiernas(5);
                  break;
               case 1:
                  if(primeraVezPulsado1){
                     robot->cambiarSentidosBrazos();
                     primeraVezPulsado1 = false;
                  }
                  robot->modificaGiroBrazos(5);
                  break;
               case 2:
                  robot->modificaDesplazamiento(-5);
               default:
                  break;
            }
            break;
      } 
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
