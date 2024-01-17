

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
   cubo = new Cubo(80.0); // cubo creado
   cubo->setColor(
      Tupla4f(1.0f, 0.0f, 0.0f, 1.0f), // color vértices
      Tupla4f(0.0f, 0.0f, 1.0f, 1.0f), // color líneas
      Tupla4f(1.0f, 0.0f, 0.0f, 1.0f)  // color sólido
   );
   piramide = new PiramideHexagonal(80.0, 80.0, 40.0); // piramide creada
   piramide->setColor(
      Tupla4f(1.0f, 0.0f, 0.0f, 1.0f), // color puntos
      Tupla4f(0.0f, 0.0f, 1.0f, 1.0f), // color líneas
      Tupla4f(0.0f, 1.0f, 0.0f, 1.0f)  // color sólido
   );


   // Objetos de revolución
   esfera = new Esfera(30, 30, 40);
   cilindro = new Cilindro(4, 10, 50.0, 50.0); 
   cono = new Cono(3, 10, 70, 25);


   // Objetos PLY
   ObjPLY_1 = new ObjPLY("./plys/ant.ply");
   ObjPLY_2 = new ObjPLY("./plys/beethoven.ply");
      ObjPLY_2->setColor(
         Tupla4f(0.0f, 1.0f, 0.0f, 1.0f),
         Tupla4f(0.0f, 0.0f, 1.0f, 1.0f),
         Tupla4f(1.0f, 1.0f, 0.0f, 1.0f)
      );
   ObjPLY_3 = new ObjRevolucion("./plys/peon.ply", 10, false, true);
      ObjPLY_3->setColor(
         Tupla4f(1.0f, 1.0f, 0.0f, 1.0f),
         Tupla4f(0.0f, 0.0f, 1.0f, 1.0f),
         Tupla4f(0.1f, 0.6f, 0.1f, 1.0f)
      );

   // vehiculo = new ObjPLY("./plys/bike.ply");

   peon1 = new ObjRevolucion("./plys/peon.ply", 10, false, true);
   peon2 = new ObjRevolucion("./plys/peon.ply", 10, false, true);


   // para texturas
   cuadro = new Cuadro(60.0);

   // Carretera
   carretera = new Carretera(120, 8000);

   // Mundo
   mundo = new Mundo(8000);

   // Colores de selección
      cubo->setColorSeleccion({1.0f, 0.0f, 0.0f});
      piramide->setColorSeleccion({0.0f, 1.0f, 0.0f});

      esfera->setColorSeleccion({0.0f, 1.0f, 1.0f});
      cilindro->setColorSeleccion({0.0f, 0.0f, 1.0f});
      cono->setColorSeleccion({1.0f, 0.0f, 1.0f});

      // ObjPLY_1->setColorSeleccion({1.0f, 1.0f, 0.0f});
      // ObjPLY_2->setColorSeleccion({1.0f, 0.25f, 1.0f});
      // ObjPLY_3->setColorSeleccion({0.0f, 0.0f, 1.0f});

      // peon1->setColorSeleccion({0.5f, 0.0f, 0.0f});
      // peon2->setColorSeleccion({0.0f, 0.5f, 1.0f});

      cuadro->setColorSeleccion({1.0f, 0.5f, 1.0f});
      // robot->setColorSeleccion({0.5f, 0.5f, 0.7f});
   //

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
      {0.0, 1.0, 0.0, 1.0}); // color difuso (verde) [R-G-B]

   luz2 = new LuzPosicional(
      {200, 120, 200}, // posición en coordenadas
      GL_LIGHT2, // id
      {0.0, 0.0, 0.0, 1}, // color ambiente (negro)
      {1.0, 1.0, 1.0, 1.0}, // color especular (blanco)
      {1.0, 1.0, 1.0, 1.0}); // color difuso (blanco) [R-G-B]


      /* TEXTURAS */
      cuadro->setTextura("./img/cuadro.jpg");
      esfera->setTextura("./img/mapamundi.jpg");

      carretera->setTextura("./img/carretera.jpg");
      mundo->setTextura("./img/suelo2.jpg");


      /* CÁMARAS */
      Tupla3f eye = {0, 150, 220}; 
      Tupla3f at = {0, 0, 0};
      Tupla3f up = {0, 1, 0};
      float near = 50.0, far = 2000.0;
      float bottom = -50.0, top = 50.0, left = -50.0, right = 50.0;
      Camara cam0(eye, at, up, 0, near, far, bottom, top, left, right);

      eye = {0, 100, 1000}; 
      at = {0, 0, 0};
      up = {0, 1, 0};
      Camara cam1(eye, at, up, 1, near, far, bottom, top, left, right);

      eye = {-150, 200, -150}; 
      at = {0, 0, 100};
      up = {0, 1, 0};
      Camara cam2(eye, at, up, 0, near, far, bottom, top, left, right);



      camaras.push_back(cam0);
      camaras.push_back(cam1);
      camaras.push_back(cam2);
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

   /////// Deshabilitar cosas para la selección


   luz0->setActivada(true);
   luz1->setActivada(true);

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection();
	glViewport( 0, 0, UI_window_width, UI_window_height );

   mostrarMenuPrincipal();
}

/// @brief Animar el modelo jerárquico
void Escena::animarModeloJerarquico() {
   if(animacionAutomatica)
      robot->animarModeloJerarquico();
}

/// @brief Animar la luz direccional
void Escena::animarLuzDireccional(){
   if(animacionLuzDireccional)
      luz1->animarLuzDireccional();
}

/// @brief Animar la luz posicional
void Escena::animarLuzPosicional(){
   if(animacionLuzPosicional)
      luz0->animarLuzPosicional();
}

/// @brief Asignar los materiales a los objetos
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

   esfera->setMaterial(blanco);
   cilindro->setMaterial(turquesa);
   cono->setMaterial(oro);

   peon1->setMaterial(mat_peon_blanco);
   peon2->setMaterial(mat_peon_negro);

   ObjPLY_1->setMaterial(turquesa);
   ObjPLY_2->setMaterial(turquesa);


   robot->setMaterialRobot(oro);
   cuadro->setMaterial(blanco);
   carretera->setMaterial(blanco);

   mundo->setMaterial(perla);
}

/// @brief Activamos las luces
void Escena::activar_luces(){
   glEnable(GL_LIGHTING); // activamos luces
   glShadeModel(GL_SMOOTH); // sombreado suave

   if(luz0 != nullptr && luz0->getId() == GL_LIGHT0){
         luz0->activar();
   }

   if(luz1 != nullptr && luz1->getId() == GL_LIGHT1){
         luz1->activar();
   }

   if(luz2 != nullptr && luz2->getId() == GL_LIGHT2){
         luz2->activar();
   }
}

/// @brief Método para dibujar los objetos en la escena
void Escena::dibujarObjetos(bool seleccion){

      //// MUNDO
      glPushMatrix();
         glRotatef(-90, 1, 0, 0);
         glTranslatef(-mundo->getLado()/2.0f, -mundo->getLado()/2.0f, 0); 
         mundo->draw();      
      glPopMatrix();

      //// CARRETERA
      glPushMatrix();
         glTranslatef(0, 1, carretera->getLargo()/2.0f);
         glRotatef(-90, 1, 0, 0);
         glTranslatef(-carretera->getAncho()/2.0f, 0, 0); 
         carretera->draw();      
      glPopMatrix();


      //// CUBO
      //Si estamos en modo selección y todavía no ha terminado el pick
      if(modoSeleccion && !fin_pick){
         cubo->setColorSeleccionSolido(); // poner color de seleccion para que el pick lo lea
         establecidoOriginal = false;
      }
      // cuando acabe el pick y ya no estemos en modo seleccion, volvemos a la normalidad
      if(!modoSeleccion && fin_pick && !establecidoOriginal){
         cubo->setColorSolidoOriginal(); // haria falta comprobacion de si ya esta en el original
         // cout << "Establecido el color original" << endl;
         establecidoOriginal = true;
         modoSeleccion=false;
      }

      // Para resaltar el seleccionado, cambiamos color (si es que lo está)
      if(camaras[camaraActiva].getObjetoSeleccionado() == "CUBO" && establecidoOriginal){
         cubo->setColorSeleccionSolido();
         establecidoOriginal = false;
            // cout << ">>cubo SELECCIONADO... tiene color original?:" << (establecidoOriginal ? "si" : "no") << "\n";
      }else if(camaras[camaraActiva].getObjetoSeleccionado() != "CUBO"){ // deja de estar seleccionado, devolvemos el color original
         if(!establecidoOriginal){
            // cout << ">>ya no esta seleccionado... vuelta al color original" << endl;
            cubo->setColorSolidoOriginal();
            establecidoOriginal = true;
         }
      }


            // cout << "=debug=Color original:" << (establecidoOriginal ? "si" : "no") << "\n";
            // cout << "=debug=seleccionado por camara: " << camaras[camaraActiva].getObjetoSeleccionado() << endl;

      glPushMatrix();
         glTranslatef(200, 0, -100); 
         cubo->draw();      
      glPopMatrix();

      
      // debug
      // Tupla4f colorCuboActual = cubo->getColorSolido()[0];
      // cout << "color solido del cubo: "<< colorCuboActual(0) <<", "<<colorCuboActual(1)<<", "<<colorCuboActual(2)<<endl;
      //

      glPushMatrix();
         glTranslatef(
            200 - cuadro->getLado()/2.0f,
            (cubo->getLado()-cuadro->getLado())/2.0f,
            -99 + (cubo->getLado()/2.0f));  
         cuadro->draw();
      glPopMatrix();

      //// PIRAMIDE
      glPushMatrix();
         glTranslatef(-200, 0, -100); 
         piramide->draw();
      glPopMatrix();


      /*    PLYS   */
      //// HORMIGA (ObjPLY_1)
      glPushMatrix();
         glTranslatef(180, 0, -380);
         glScalef(2, 2, 2); 
         ObjPLY_1->draw(); // hormiga
      glPopMatrix();


      //// BEETHOVEN (ObjPLY_2)
      glPushMatrix();
         glTranslatef(200, 100, -300);
         glScalef(10, 10, 10);
         ObjPLY_2->draw(); // Beethoven
      glPopMatrix();


      // PEÓN BLANCO (material puramente difuso, sin brillos especulares)
      glPushMatrix();
         glTranslatef(-200, piramide->getAltura()+20, -100);
         glScalef(15, 15, 15);
         peon1->draw(); // peón
      glPopMatrix();

      //// PEÓN NEGRO (material especular de alto brillo)
      glPushMatrix();
         glTranslatef(200, cubo->getLado()+20, -100); // glTranslatef(200, 0, -100); 
         glScalef(15, 15, 15);
         peon2->draw(); // peón
      glPopMatrix();


      /*    OBJETOS DE REVOLUCIÓN   */
      //// ESFERA
      glPushMatrix();
         // glTranslatef(-20, -20, 0);
         glTranslatef(-150, 180, -150); 
         esfera->draw();
      glPopMatrix();


      //// CILINDRO
      glPushMatrix();
         glTranslatef(-200, 0, -300);
         cilindro->draw();
      glPopMatrix();


      //// CONO
      glPushMatrix();
         glTranslatef(150, 0, 0);
         cono->draw();
      glPopMatrix();

      //// ROBOT
      glPushMatrix();
         glTranslatef(0, 80, -200);
         robot->draw();
      glPopMatrix();

      //// VEHICULO
      // glPushMatrix();
      //    vehiculo->draw();
      // glPopMatrix();


}


// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

/// @brief Método dibujar 
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

   // cout << "modoseleccion: " << (modoSeleccion ? "si" : "no") << endl;
   // cout << "finpick: " << (fin_pick ? "si" : "no") << endl;
   // cout << "establecidoOriginal: " << (establecidoOriginal ? "si" : "no") << endl;
   // cout << endl;

   if (modoPunto && !modoSeleccion) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); // puntos (front)
      // cout << "-MODO PUNTOS ACTIVO-" << endl;
      dibujarObjetos(false);
   }
   if (modoLinea && !modoSeleccion) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // lineas
      // cout << "-MODO LINEAS ACTIVO-" << endl;
      dibujarObjetos(false);
   }
   if (modoSolido && !modoSeleccion) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // solido (back)
      // cout << "-MODO SOLIDO ACTIVO-" << endl;
      dibujarObjetos(false);
   }

    
}

void Escena::clickRaton(int boton, int estado, int x, int y){
   xant = x;
	yant = y;

   if (boton == GLUT_RIGHT_BUTTON){ // boton derecho 
      if(estado == GLUT_DOWN){ // pulsado 
         // Se pulsa el botón, por lo que se entra en el estado "moviendo cámara"
         if(camaras[camaraActiva].getObjetoSeleccionado() == "NINGUNO")
            estadoRaton = MOVIENDO_CAMARA_FIRSTPERSON;
         else // se selecciona algo
            estadoRaton = CAMARA_EXAMINAR;
         
      }
      else{
         // Se levanta el botón, por lo que sale del estado "moviendo cámara"
         estadoRaton = DESACTIVADO;
      }
   } else if(boton == MOUSE_WHEEL_UP){
      camaras[camaraActiva].zoom(0.8);
   } else if(boton == MOUSE_WHEEL_DOWN){
      camaras[camaraActiva].zoom(1.2);
   }
   else if(boton == GLUT_LEFT_BUTTON){
      if(estado == GLUT_UP){
         dibujaSeleccion(x,y);
         // fin_pick = true;
         // modoSeleccion=false;
      }
   }

   change_projection();

}

void Escena::ratonMovido(int x, int y){
   if(estadoRaton == MOVIENDO_CAMARA_FIRSTPERSON){ // MOVIENDO_CAMARA_FIRSTPERSON (1: MOVIENDO_EXAMINAR)
      camaras[camaraActiva].girar(x-xant, y-yant);
      xant = x;
      yant = y;
   } else if(estadoRaton == CAMARA_EXAMINAR){
      camaras[camaraActiva].girarExaminar(x-xant, y-yant);
      xant = x;
      yant = y;
   }
}

void Escena::dibujaSeleccion(int x, int y){
   glDisable(GL_DITHER);
   glDisable(GL_LIGHTING);
   glDisable(GL_TEXTURE);


   fin_pick = false;

      modoSeleccion=true;
      dibujarObjetos(true);
            pick(x,y);

   fin_pick = true;

   modoSeleccion=false;


   glEnable(GL_DITHER);
   glEnable(GL_LIGHTING);
   glEnable(GL_TEXTURE);
}

void Escena::pick(int x, int y){

   glDisable(GL_DITHER);

   GLint viewport[4];
	GLfloat pixel[3];

	glGetIntegerv(GL_VIEWPORT, viewport);

	glReadPixels(x, viewport[3]-y, 1, 1, GL_RGB, GL_FLOAT, (void *) pixel);

   Tupla3f pixel_leido = {pixel[0], pixel[1], pixel[2]};

      Tupla3f csCubo = cubo->getColorSeleccion();
      Tupla3f csCono = cono->getColorSeleccion();
      Tupla3f csEsfera = esfera->getColorSeleccion();
      Tupla3f csPiramide = piramide->getColorSeleccion();
      Tupla3f csCilindro = cilindro->getColorSeleccion();
      Tupla3f csObjPLY_1 = ObjPLY_1->getColorSeleccion();
      Tupla3f csObjPLY_2 = ObjPLY_2->getColorSeleccion();
      Tupla3f csObjPLY_3 = ObjPLY_3->getColorSeleccion();
      Tupla3f csPeon1 = peon1->getColorSeleccion();
      Tupla3f csPeon2 = peon2->getColorSeleccion();
      Tupla3f csCuadro = cuadro->getColorSeleccion();


   // cout << "\n\tPIXEL LEIDO: (" << pixel_leido(0) << ", " << pixel_leido(1) << ", " << pixel_leido(2) << ")" << endl;

   // cout << "\n";

   Tupla3f centro;

   if (compararColores(pixel_leido, csCubo)){
      cout << "\tCubo seleccionado!" << endl;
      // cubo->calcularCentroVista();
      centro = cubo->getCentroTransformado();
      centro = centroObjeto(centro);

      camaras[camaraActiva].setAt(centro);
      camaras[camaraActiva].setObjetoSeleccionado("CUBO");

      // cout << "\t\t->Centro del cubo: (" << cubo->getCentroTransformado()(0) << ", " << cubo->getCentroTransformado()(1) << ", " << cubo->getCentroTransformado()(2) << ")" << endl;
      // cout << "\t\t->Centro del cubo con funcion: (" << centro(0) << ", " << centro(1) << ", " << centro(2) << ")" << endl;
   }
   else if (compararColores(pixel_leido, csCono)){
      cout << "\tCono seleccionado!" << endl;
      camaras[camaraActiva].setAt(cono->getCentroTransformado());
      // cout << "->Centro del cono: (" << cono->getCentroTransformado()(0) << ", " << cono->getCentroTransformado()(1) << ", " << cono->getCentroTransformado()(2) << ")" << endl;
      camaras[camaraActiva].setObjetoSeleccionado("CONO");
   }
   else if (compararColores(pixel_leido, csCilindro)){
      cout << "\tCilindro seleccionado!" << endl;
      camaras[camaraActiva].setAt(cilindro->getCentroTransformado());
      // cout << "->Centro del cilindro: (" << cilindro->getCentroTransformado()(0) << ", " << cilindro->getCentroTransformado()(1) << ", " << cilindro->getCentroTransformado()(2) << ")" << endl;
      camaras[camaraActiva].setObjetoSeleccionado("CONO");
   }
   else if (compararColores(pixel_leido, csEsfera)){
      cout << "\tEsfera seleccionada!" << endl;
      camaras[camaraActiva].setAt(esfera->getCentroTransformado());
      camaras[camaraActiva].setObjetoSeleccionado("ESFERA");
   }
   else if (compararColores(pixel_leido, csPiramide)){
      cout << "\tPirámide seleccionada!" << endl;
      camaras[camaraActiva].setAt(piramide->getCentroTransformado());
      camaras[camaraActiva].setObjetoSeleccionado("PIRAMIDE");
   }
   else if (compararColores(pixel_leido, csObjPLY_1)){
      cout << "\tObjPLY_1 seleccionado!" << endl;
      camaras[camaraActiva].setAt(ObjPLY_1->getCentroTransformado());
      // cout << "->Centro del objply1: (" << ObjPLY_1->getCentroTransformado()(0) << ", " << ObjPLY_1->getCentroTransformado()(1) << ", " << ObjPLY_1->getCentroTransformado()(2) << ")" << endl;
      camaras[camaraActiva].setObjetoSeleccionado("OBJPLY_1");
   }
   else if (compararColores(pixel_leido, csObjPLY_2)){
      cout << "\tObjPLY_2 seleccionado!" << endl;
      camaras[camaraActiva].setAt(ObjPLY_2->getCentroTransformado());
      camaras[camaraActiva].setObjetoSeleccionado("OBJPLY_2");
   }
   else if (compararColores(pixel_leido, csObjPLY_3)){
      cout << "\tObjPLY_3 seleccionado!" << endl;
      camaras[camaraActiva].setAt(ObjPLY_3->getCentroTransformado());
      camaras[camaraActiva].setObjetoSeleccionado("OBJPLY_3");
   }
   else if (compararColores(pixel_leido, csPeon1)){
      cout << "\tPeon1 seleccionado!" << endl;
      camaras[camaraActiva].setAt(peon1->getCentroTransformado());
      camaras[camaraActiva].setObjetoSeleccionado("PEON1");  
   }
   else if (compararColores(pixel_leido, csPeon2)){
      cout << "\tPeon2 seleccionado!" << endl;
      camaras[camaraActiva].setAt(peon2->getCentroTransformado());
      camaras[camaraActiva].setObjetoSeleccionado("PEON2");
   }
   else if (compararColores(pixel_leido, csCuadro)){
      cout << "\tCuadro seleccionado!" << endl;
      camaras[camaraActiva].setAt(cuadro->getCentroTransformado());
      camaras[camaraActiva].setObjetoSeleccionado("CUADRO");   
   }
   else{
      // cout << "\tNada seleccionado!" << endl;
      camaras[camaraActiva].setObjetoSeleccionado("NINGUNO");   
   }

   cout << endl;

   glEnable(GL_DITHER);

   change_projection();

}

bool Escena::compararColores(Tupla3f pixel, Tupla3f color) {
   // cout <<"--Comparacion del color: ("<<color(0)<<", "<<color(1)<<", "<<color(2)<<")"<<endl;

   for (int i = 0; i < 3; i++) {
      if (std::abs(pixel[i] - color[i]) > UMBRAL) {
         return false;  // La diferencia es mayor que el umbral, los colores no son iguales
      }
   }

   return true;  // Los colores son iguales dentro del umbral de tolerancia
}

Tupla3f Escena::centroObjeto(Tupla3f centro){
   Tupla3f centroTransformado;

      GLfloat mat[16];
         glGetFloatv(GL_MODELVIEW_MATRIX, mat);

	GLfloat inv[16];

	invertirMatriz(mat, inv);


	// aplicamos la transformacion de la matriz al punto
	centroTransformado(0) = inv[0] * centro(0) + inv[4] * centro(1) + inv[8] * centro(2) + inv[12];
	centroTransformado(1) = inv[1] * centro(0) + inv[5] * centro(1) + inv[9] * centro(2) + inv[13];
	centroTransformado(2) = inv[2] * centro(0) + inv[6] * centro(1) + inv[10] * centro(2) + inv[14];

	return centroTransformado;
}


bool Escena::invertirMatriz(const float m[16], float invOut[16]){
   double inv[16], det;
    int i;

    inv[0] = m[5]  * m[10] * m[15] -
             m[5]  * m[11] * m[14] -
             m[9]  * m[6]  * m[15] +
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] -
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] +
              m[4]  * m[11] * m[14] +
              m[8]  * m[6]  * m[15] -
              m[8]  * m[7]  * m[14] -
              m[12] * m[6]  * m[11] +
              m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] -
             m[4]  * m[11] * m[13] -
             m[8]  * m[5] * m[15] +
             m[8]  * m[7] * m[13] +
             m[12] * m[5] * m[11] -
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] +
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] -
               m[8]  * m[6] * m[13] -
               m[12] * m[5] * m[10] +
               m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] +
              m[1]  * m[11] * m[14] +
              m[9]  * m[2] * m[15] -
              m[9]  * m[3] * m[14] -
              m[13] * m[2] * m[11] +
              m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] -
             m[0]  * m[11] * m[14] -
             m[8]  * m[2] * m[15] +
             m[8]  * m[3] * m[14] +
             m[12] * m[2] * m[11] -
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] +
              m[0]  * m[11] * m[13] +
              m[8]  * m[1] * m[15] -
              m[8]  * m[3] * m[13] -
              m[12] * m[1] * m[11] +
              m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] -
              m[0]  * m[10] * m[13] -
              m[8]  * m[1] * m[14] +
              m[8]  * m[2] * m[13] +
              m[12] * m[1] * m[10] -
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] -
             m[1]  * m[7] * m[14] -
             m[5]  * m[2] * m[15] +
             m[5]  * m[3] * m[14] +
             m[13] * m[2] * m[7] -
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] +
              m[0]  * m[7] * m[14] +
              m[4]  * m[2] * m[15] -
              m[4]  * m[3] * m[14] -
              m[12] * m[2] * m[7] +
              m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] -
              m[0]  * m[7] * m[13] -
              m[4]  * m[1] * m[15] +
              m[4]  * m[3] * m[13] +
              m[12] * m[1] * m[7] -
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] +
               m[0]  * m[6] * m[13] +
               m[4]  * m[1] * m[14] -
               m[4]  * m[2] * m[13] -
               m[12] * m[1] * m[6] +
               m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] +
              m[1] * m[7] * m[10] +
              m[5] * m[2] * m[11] -
              m[5] * m[3] * m[10] -
              m[9] * m[2] * m[7] +
              m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] -
             m[0] * m[7] * m[10] -
             m[4] * m[2] * m[11] +
             m[4] * m[3] * m[10] +
             m[8] * m[2] * m[7] -
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] +
               m[0] * m[7] * m[9] +
               m[4] * m[1] * m[11] -
               m[4] * m[3] * m[9] -
               m[8] * m[1] * m[7] +
               m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] -
              m[0] * m[6] * m[9] -
              m[4] * m[1] * m[10] +
              m[4] * m[2] * m[9] +
              m[8] * m[1] * m[6] -
              m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if (det == 0)
        return false;

    det = 1.0 / det;

    for (i = 0; i < 16; i++)
        invOut[i] = inv[i] * det;

    return true;
}

/* FUNCIONES PARA MOSTRAR MENÚ */

void Escena::mostrarMenuPrincipal(){
   cout << "\n\n\tOpciones de menú: " << endl;
   cout << "\t'V' -> Menú visualización" << endl;
   cout << "\t'A' -> Animación automática" << endl;
   cout << "\t'M' -> Animación manual" << endl;
   cout << "\t'C' -> Selección de cámara" << endl;
   cout << "\t'Y' -> Mover la cámara hacia delante" << endl;
   cout << "\t'H' -> Mover la cámara hacia atrás" << endl;
   cout << "\t'G' -> Mover la cámara hacia la izquierda" << endl;
   cout << "\t'J' -> Mover la cámara hacia la derecha" << endl;
   cout << "\t'Q' -> Fin del programa" << endl << endl;
}

void Escena::mostrarMenuGradosLibertad(){
   cout << "\n\n\tMenú de animación manual: " << endl;
   cout << "\t'0' a '3' -> Seleccionar grado de libertad" << endl;
   cout << "\t'+' -> Aumentar valor del grado de libertad seleccionado" << endl;
   cout << "\t'-' -> Disminuir valor del grado de libertad seleccionado" << endl;
   cout << "\t'Q' -> Salir de este menú" << endl << endl;

}

void Escena::mostrarMenuLuces(){
   cout << "\n\n\tMenú de luces: " << endl;
   cout << "\t'I' -> Activar/desactivar luces " << endl;
   cout << "\t'0' a '2' -> seleccionar luz" << endl;
   cout << "\t'A' -> Activará el modo variación del ángulo alfa" << endl;
   cout << "\t'B' -> Activará el modo variación del ángulo beta" << endl;
   cout << "\t'>' -> Incrementa el ángulo seleccionado" << endl;
   cout << "\t'<' -> Decrementa el ángulo seleccionado" << endl;
   cout << "\t'P' -> Se anima automáticamente la luz puntual" << endl;
   cout << "\t'D' -> Se anima automáticamente el color de la luz direccional" << endl;
   cout << "\t'Q' -> Salir de este menú" << endl << endl;
}

void Escena::mostrarMenuAnimacionAutomatica(){
   cout << "\n\n\tMenú animación automática: " << endl;
   cout << "\t'A' -> Activar/desactivar animación automática" << endl;
   cout << "\t'+' -> Aumentar valor del grado de libertad seleccionado" << endl;
   cout << "\t'-' -> Disminuir valor del grado de libertad seleccionado" << endl;
   cout << "\t'Q' -> Salir de este menú" << endl << endl;
}

void Escena::mostrarMenuSeleccionCamaras(){
   cout << "\n\n\tMenú de selección de cámaras" << endl;
   cout << "\t'0 a '7' -> Seleccionar cámara" << endl;
   cout << "\t'Q' -> Salir de este menú" << endl << endl;
}

void Escena::mostrarMenuVisualizacion(){
   cout << "\n\n\tMenú de visualización: " << endl;
   cout << "\t'P' -> Activar/desactivar modo puntos" << endl;
   cout << "\t'L' -> Activar/desactivar modo lineas" << endl;
   cout << "\t'S' -> Activar/desactivar modo solido" << endl;
   cout << "\t'I' -> Entrar en modo luces" << endl;
   cout << "\t'Q' -> Salir de este menú" << endl;
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
   // cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir=false;
         Tupla3f direccion = camaras[camaraActiva].getAt() - camaras[camaraActiva].getEye();


   switch( toupper(tecla) )
   {
      case 'Q' :
         if (modoMenu!=NADA){
            modoMenu=NADA;           
            primeraVezPulsadoI = true; 
            cout << "-->VOLVIENDO A MENÚ PRINCIPAL" << endl;
            mostrarMenuPrincipal();
         }
         else {
            salir=true ;
         }
         break ;
      // case 'O' :
      //    // ESTAMOS EN MODO SELECCION DE OBJETO
      //    cout << "-->ENTRANDO A MENÚ DE SELECCIÓN DE OBJETO" << endl;
      //    modoMenu=SELOBJETO; 
      //    break ;
      case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         // cout << "-->ENTRANDO A MENÚ DE VISUALIZACIÓN" << endl;
         modoMenu=SELVISUALIZACION;
         mostrarMenuVisualizacion();
         break ;
      case 'A':
         animacionAutomatica = !animacionAutomatica;
         cout << "-->ANIMACIÓN AUTOMÁTICA " << (animacionAutomatica ? "ACTIVADA" : "DESACTIVADA") << endl;
         if(modoMenu==NADA){ // si no está en ningun submenú
            modoMenu=ANIMACION;
         }
         mostrarMenuAnimacionAutomatica();
         break;
      case 'M': // se desactiva animacion automatica
         // cout << "-->ENTRANDO A SELECCIÓN DE GRADOS DE LIBERTAD" << endl;
         modoMenu=GRADOS;
         mostrarMenuGradosLibertad();
         break;
      case 'C':
         // cout << "-->ENTRANDO A SELECCIÓN DE CAMARAS" << endl;
         modoMenu=CAMARAS;
         mostrarMenuSeleccionCamaras();
         break;
      case 'Y': // arriba
         // camaras[camaraActiva].mover(0, 4, 0);
            direccion = direccion.normalized()*3;

            camaras[camaraActiva].mover(direccion(0), direccion(1), direccion(2));
         break;
      case 'G': // izquierda
         // camaras[camaraActiva].mover(-4, 0, 0);
            direccion = direccion.normalized();

				direccion = -direccion.cross(camaras[camaraActiva].getUp())*3;

				camaras[camaraActiva].mover(direccion(0), direccion(1), direccion(2));
         break;
      case 'J': // derecha
         // camaras[camaraActiva].mover(4, 0, 0);
            direccion = direccion.normalized();

				direccion = direccion.cross(camaras[camaraActiva].getUp())*3;

				camaras[camaraActiva].mover(direccion(0), direccion(1), direccion(2));
         break;
      case 'H': // abajo
         // camaras[camaraActiva].mover(0, -4, 0);
            direccion = -direccion.normalized()*3;

            camaras[camaraActiva].mover(direccion(0), direccion(1), direccion(2));
         break;
      case 'I': // activar iluminación
         if(modoMenu==SELVISUALIZACION){
            cout << "--ILUMINACIÓN " << (iluminacionActiva ? "ACTIVADA" : "DESACTIVADA") << endl << endl;
            modoMenu = LUCES;
            mostrarMenuLuces();
         } else if(modoMenu==LUCES){
            iluminacionActiva = !iluminacionActiva;
            cout << "--ILUMINACIÓN " << (iluminacionActiva ? "ACTIVADA" : "DESACTIVADA") << endl << endl;
            if(iluminacionActiva){
               modoLinea = false;
               modoPunto = false;
               modoSolido = true;
            }
            mostrarMenuLuces();
         }
         
         break;
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
            cout << "--MODO PUNTOS " << (modoPunto ? "ACTIVADO" : "DESACTIVADO") << endl << endl;
            mostrarMenuVisualizacion();
            break;
         case 'L': // modo líneas
            if(iluminacionActiva){
               iluminacionActiva = false;
            }
            modoLinea = !modoLinea; 
            cout << "--MODO LÍNEAS " << (modoLinea ? "ACTIVADO" : "DESACTIVADO") << endl << endl;
            mostrarMenuVisualizacion();
            break;
         case 'S': // modo sólido
            if(iluminacionActiva){
               iluminacionActiva = false;
            }
            modoSolido = !modoSolido; 
            cout << "\n\n--MODO SÓLIDO " << (modoSolido ? "ACTIVADO" : "DESACTIVADO") << endl << endl;
            mostrarMenuVisualizacion();
            break;
      }

   if(modoMenu == LUCES){
      switch (toupper(tecla))
      {
         case '0': // GL_LIGHT0
            if (luz0 != nullptr)
               luz0->setActivada(!luz0->estadoActivada());
            cout << "--LUZ 0 (POSICIONAL)" << (luz0->estadoActivada() ? "ACTIVADA" : "DESACTIVADA") << endl;
            mostrarMenuLuces();
            break;
         case '1': // GL_LIGHT1
            if (luz1 != nullptr)
                  luz1->setActivada(!luz1->estadoActivada());
            cout << "--LUZ 1 (DIRECCIONAL)" << (luz1->estadoActivada() ? "ACTIVADA" : "DESACTIVADA") << endl;
            mostrarMenuLuces();
            break;
         case '2': // GL_LIGHT2
            if (luz2 != nullptr)
                  luz2->setActivada(!luz2->estadoActivada());
            cout << "--LUZ 2 (POSICIONAL)" << (luz2->estadoActivada() ? "ACTIVADA" : "DESACTIVADA") << endl;
            mostrarMenuLuces();
            break;
         case 'A': // variar angulo alfa
            ultimaPulsada = 'A';
            cout << "--CAMBIAR ÁNGULO ALFA..." << endl;
            mostrarMenuLuces();
            break;
         case 'B': // variar angulo beta
            ultimaPulsada = 'B';
            cout << "--CAMBIAR ÁNGULO BETA..." << endl;
            mostrarMenuLuces();
            break;
         case '>': // incrementa el angulo
            if(ultimaPulsada == 'A'){
               luz1->variarAnguloAlpha(5*M_PI/180);
            }
            else if(ultimaPulsada == 'B'){
               luz1->variarAnguloBeta(5*M_PI/180);
            }
            break;
         case '<': // decrementa el angulo
            if(ultimaPulsada == 'A'){
               luz1->variarAnguloAlpha(-5*M_PI/180);
            }
            else if(ultimaPulsada == 'B'){ // la B
               luz1->variarAnguloBeta(-5*M_PI/180);
            }
            break;
         case 'P':
            // animar automaticamente luz puntual
            animacionLuzPosicional = !animacionLuzPosicional;
            cout << "-->ANIMACIÓN AUTOMÁTICA DE LUZ POSICIONAL " << (animacionLuzPosicional ? "ACTIVADA" : "DESACTIVADA") << endl;
            mostrarMenuLuces();
            break;
         case 'D':
            // animar automaticamente luz direccional
            animacionLuzDireccional = !animacionLuzDireccional;
            cout << "-->ANIMACIÓN AUTOMÁTICA DE LUZ DIRECCIONAL " << (animacionLuzDireccional ? "ACTIVADA" : "DESACTIVADA") << endl;
            mostrarMenuLuces();
            break;
         default:
            break;
      }
   }

   if(modoMenu == ANIMACION){ // tecla A
      switch (toupper(tecla))
      {
      case '+':
         /* aumenta velocidad */
         robot->cambiarVelocidad(0.4);
         cout << "-->AUMENTADA VELOCIDAD" << endl;
         mostrarMenuAnimacionAutomatica();
         break;
      case '-':
         /* disminuye velocidad */
         robot->cambiarVelocidad(-0.4);
         cout << "-->DISMINUIDA VELOCIDAD" << endl;
         mostrarMenuAnimacionAutomatica();
         break;
      default:
         break;
      }
   }

   if(modoMenu == GRADOS){ // tecla M
      switch(toupper(tecla)){
         case '0':
            numGrado = 0; 
            cout << "--GRADO 0 SELECCIONADO (PIERNAS)" << endl;
            mostrarMenuGradosLibertad();
            break;
         case '1':
            numGrado = 1;
            cout << "--GRADO 1 SELECCIONADO (BRAZOS)" << endl;
            mostrarMenuGradosLibertad();
            break;
         case '2':
            numGrado = 2;
            cout << "--GRADO 2 SELECCIONADO (MOVIMIENTO)" << endl;
            mostrarMenuGradosLibertad();
            break;
         case '3':
            numGrado = 3;
            cout << "--GRADO 3 SELECCIONADO (CABEZA)" << endl;
            mostrarMenuGradosLibertad();
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
               case 3:
                  robot->modificaDesplazamientoCabeza(5);
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
                  break;
               case 3:
                  robot->modificaDesplazamientoCabeza(-5);
                  break;
               default:
                  break;
            }
            break;
      } 
   }

   if(modoMenu == CAMARAS){
      switch (toupper(tecla))
      {
      case '0':
         if(camaras.size() >= 1){
            camaraActiva = 0;
            change_projection();
            change_observer();
            cout << "\n\n>> CÁMARA 0 ACTIVADA" << endl;
         }
         else{
            cout << "\n\n>> NO HAY CÁMARA 0 DEFINIDA" << endl;
         }
         mostrarMenuSeleccionCamaras();
         break;
      case '1':
         if(camaras.size() >= 2){
            camaraActiva = 1;
            change_projection();
            change_observer();
            cout << "\n\n>> CÁMARA 1 ACTIVADA" << endl;
         }
         else{
            cout << "\n\n>> NO HAY CÁMARA 1 DEFINIDA" << endl;
         }
         mostrarMenuSeleccionCamaras();
         break;
      case '2':
         if(camaras.size() >= 3){
            camaraActiva = 2;
            change_projection();
            change_observer();
            cout << "\n\n>> CÁMARA 2 ACTIVADA" << endl;
         }
         else{
            cout << "\n\n>> NO HAY CÁMARA 2 DEFINIDA" << endl;
         }
         mostrarMenuSeleccionCamaras();
         break;
      case '3':
         if(camaras.size() >= 4){
            camaraActiva = 3;
            change_projection();
            change_observer();
            cout << "\n\n>> CÁMARA 3 ACTIVADA" << endl;
         }
         else{
            cout << "\n\n>> NO HAY CÁMARA 3 DEFINIDA" << endl;
         }
         mostrarMenuSeleccionCamaras();
         break;
      case '4':
         if(camaras.size() >= 5){
            camaraActiva = 4;
            change_projection();
            change_observer();
            cout << "\n\n>> CÁMARA 4 ACTIVADA" << endl;
         }
         else{
            cout << "\n\n>> NO HAY CÁMARA 4 DEFINIDA" << endl;
         }
         mostrarMenuSeleccionCamaras();
         break;
      case '5':
         if(camaras.size() >= 6){
            camaraActiva = 5;
            change_projection();
            change_observer();
            cout << "\n\n>> CÁMARA 5 ACTIVADA" << endl;
         }
         else{
            cout << "\n\n>> NO HAY CÁMARA 5 DEFINIDA" << endl;
         }
         mostrarMenuSeleccionCamaras();
         break;
      case '6':
         if(camaras.size() >= 7){
            camaraActiva = 6;
            change_projection();
            change_observer();
            cout << "\n\n>> CÁMARA 6 ACTIVADA" << endl;
         }
         else{
            cout << "\n\n>> NO HAY CÁMARA 6 DEFINIDA" << endl;
         }
         mostrarMenuSeleccionCamaras();
         break;
      case '7':
         if(camaras.size() >= 8){
            camaraActiva = 7;
            change_projection();
            change_observer();
            cout << "\n\n>> CÁMARA 7 ACTIVADA" << endl;
         }
         else{
            cout << "\n\n>> NO HAY CÁMARA 7 DEFINIDA" << endl;
         }
         mostrarMenuSeleccionCamaras();
         break;
      default:
         break;
      }
   }

   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   // switch ( Tecla1 )
   // {
	//    case GLUT_KEY_LEFT:
   //       Observer_angle_y-- ;
   //       break;
	//    case GLUT_KEY_RIGHT:
   //       Observer_angle_y++ ;
   //       break;
	//    case GLUT_KEY_UP:
   //       Observer_angle_x-- ;
   //       break;
	//    case GLUT_KEY_DOWN:
   //       Observer_angle_x++ ;
   //       break;
	//    case GLUT_KEY_PAGE_UP:
   //       Observer_distance *=1.2 ;
   //       break;
	//    case GLUT_KEY_PAGE_DOWN:
   //       Observer_distance /= 1.2 ;
   //       break;
	// }

   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
			camaras[camaraActiva].rotarYExaminar(-1 * M_PI/180);
         break;
	   case GLUT_KEY_RIGHT:
			camaras[camaraActiva].rotarYExaminar(1 * M_PI/180);
         break;
	   case GLUT_KEY_UP:
			camaras[camaraActiva].rotarXExaminar(-1 * M_PI/180);

         break;
	   case GLUT_KEY_DOWN:
			camaras[camaraActiva].rotarXExaminar(1 * M_PI/180);
         break;
	   case GLUT_KEY_PAGE_UP:
			camaras[camaraActiva].zoom(0.8);
         break;
	   case GLUT_KEY_PAGE_DOWN:
			camaras[camaraActiva].zoom(1.2);
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

void Escena::change_projection()
{
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   camaras[camaraActiva].setProyeccion();
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   const float ratio = (float)newWidth/(float)newHeight;

	for (int i = 0; i < camaras.size(); i++){
		camaras[i].setLeft(camaras[i].getBottom()*ratio);
		camaras[i].setRight(camaras[i].getTop()*ratio);
	}

   change_projection();
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   // glMatrixMode(GL_MODELVIEW);
   // glLoadIdentity();
   // glTranslatef( 0.0, 0.0, -Observer_distance );
   // glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   // glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );


   // PRACTICA 6
    // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   camaras[camaraActiva].setObserver();


}
