#include "auxiliar.h"
#include "malla.h"

using namespace std;


// *****************************************************************************
//
// IG_D Clase Malla3D
//
// *****************************************************************************
// -----------------------------------------------------------------------------
// Función de visualización de la malla,


// Malla3D::~Malla3D(){
// 	if (textura != nullptr){
// 		delete textura;
// 	}
// }

/// @brief Método dibujar de malla
void Malla3D::draw()
{
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   // completar (práctica 1)
   // .....

   crearVBOS();

   // Tamaño de los puntos
   glPointSize(5.0);
   

   // Aplicar materiales si se encienden las luces
   if(glIsEnabled(GL_LIGHTING)){
      glEnableClientState(GL_NORMAL_ARRAY);
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_nv);
      glNormalPointer(GL_FLOAT, 0, 0 );
      glBindBuffer(GL_ARRAY_BUFFER, 0);

      m.aplicar();

   } 
   //
         ///
         // if(seleccionado){
            GLfloat mat[16];
            glGetFloatv(GL_MODELVIEW_MATRIX, mat);

            Tupla3f n_centro;

            // aplicamos la transformacion de la matriz al punto
            n_centro(0) = mat[0] * centro(0) + mat[4] * centro(1) + mat[8] * centro(2) + mat[12];
            n_centro(1) = mat[1] * centro(0) + mat[5] * centro(1) + mat[9] * centro(2) + mat[13];
            n_centro(2) = mat[2] * centro(0) + mat[6] * centro(1) + mat[10] * centro(2) + mat[14];

            centroTransformado = n_centro;
         // }
         




   // Texturas
   if (textura != nullptr) {
      textura->activar();
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glTexCoordPointer(2, GL_FLOAT, 0, ct.data());
   }
   
   // Segun el modo de dibujo, activar un color u otro
   if (id_vbo_cd != 0 && id_vbo_cl != 0 && id_vbo_cs != 0) {
      GLint mode[2];

      // GLint mode;
      glGetIntegerv(GL_POLYGON_MODE, mode);

      // habilitar uso de array de colores
      glEnableClientState( GL_COLOR_ARRAY );

      // especificar cual es el VBO que vamos a usar
      if (mode[1] == GL_POINT) { // si está en modo puntos
         glBindBuffer( GL_ARRAY_BUFFER, id_vbo_cd);
      } else if (mode[1] == GL_LINE) { // si está en modo líneas
         glBindBuffer( GL_ARRAY_BUFFER, id_vbo_cl);
      } else if (mode[1] == GL_FILL) { // si está en modo sólido
         glBindBuffer(GL_ARRAY_BUFFER, id_vbo_cs);
      }

      // usar el buffer activo para el color
      glColorPointer(4, GL_FLOAT, 0, 0);

      glBindBuffer(GL_ARRAY_BUFFER, 0);
   }




   /* Para activar los VBOs */
   // activar buffer: VBO de vértices
   glBindBuffer ( GL_ARRAY_BUFFER , id_vbo_ver );
   // usar como buffer de vertices el actualmente activo
   glVertexPointer ( 3 , GL_FLOAT , 0 , 0 );
   // deactivar buffer: VBO de vértices.
   glBindBuffer ( GL_ARRAY_BUFFER , 0 );
   // habilitar el uso de tabla de vértices
   glEnableClientState ( GL_VERTEX_ARRAY );
   

   // activar buffer: VBO de triángulos
   glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , id_vbo_tri );
   // dibujar con el buffer de índices activo
   glDrawElements ( GL_TRIANGLES , 3 * f.size() , GL_UNSIGNED_INT , 0 ) ;
   // desactivar buffer: VBO de triángulos
   glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER , 0 );
   
   // desactivar texturas
   if (textura != nullptr) {
	  glDisable( GL_TEXTURE_2D );
	  glDisable(GL_TEXTURE_COORD_ARRAY);
   }

   // desactivar uso de array de vértices
   glDisableClientState ( GL_VERTEX_ARRAY );
   glDisableClientState ( GL_COLOR_ARRAY );

   // desactivar luces
   if (glIsEnabled(GL_LIGHTING)){
      glDisableClientState( GL_LIGHTING );
   }
   
}


/// @brief Método que calcula las normales de la malla
void Malla3D::calcularNormales(){
   Tupla3f vectorA;
   Tupla3f vectorB;

   Tupla3f perpendicular;
   Tupla3f normal;

   // La cara esta formada por los puntos p, q y r, A = q - p y B = r - p
   // Una normal por vértice
   nv.resize(v.size());


   for(int i = 0; i < nv.size(); i++){
      nv[i] = {0,0,0};
   }

   for(int i = 0; i < f.size(); i++){
      vectorA = v[f[i](1)] - v[f[i](0)];
      vectorB = v[f[i](2)] - v[f[i](0)];


      // calculamos la perpendicular haciendo el producto vectorial
      perpendicular = vectorA.cross(vectorB);

      // lo normalizamos si los vectores son nulos
		// por si repetimos los puntos de los polos
		if (perpendicular.lengthSq() > 0)
      	normal = perpendicular.normalized();


      nv[f[i](0)] = nv[f[i](0)] + normal;
      nv[f[i](1)] = nv[f[i](1)] + normal;
      nv[f[i](2)] = nv[f[i](2)] + normal;

   }

   for(int i = 0; i < nv.size(); i++){
      if(nv[i].lengthSq() > 0)
         nv[i] = nv[i].normalized();
   }

}


/// @brief Asigna los puntos de textura de la malla
/// @param modo 
void Malla3D::asignarPuntosTextura(const modoTextura & modo){

	ct.resize(v.size());


	for (int i = 0; i < ct.size(); i++){
		ct[i] = {v[i](0), (v[i](1) - v.front()(1) ) / (v.back()(1) - v.front()(1))} ;
	}

   std::cout << "asignarPuntosTextura" << std::endl;
}


/// @brief Asigna los puntos de textura de la malla si es un cuadro
/// @param modo 
void Malla3D::asignarPuntosTexturaCuadro(const modoTextura & modo){

	ct.clear();
   ct.resize(v.size());

   ct[0] = {0.0f, 0.0f};
   ct[1] = {1.0f, 0.0f};
   ct[2] = {0.0f, 1.0f};
   ct[3] = {1.0f, 1.0f};
}


/// @brief Calcula el centro de la malla
void Malla3D::calcularCentro(){

   for(int i=0; i<v.size(); i++){
      centro = centro + v[i];
   }

	centro = centro / v.size();

}

/// @brief Calcula el centro de la malla segun la matriz de vista
void Malla3D::calcularCentroVista(){
   GLfloat mat[16];
   glGetFloatv(GL_MODELVIEW_MATRIX, mat);

   Tupla3f n_centro;

   // aplicamos la transformacion de la matriz al punto
   n_centro(0) = mat[0] * centro(0) + mat[4] * centro(1) + mat[8] * centro(2) + mat[12];
   n_centro(1) = mat[1] * centro(0) + mat[5] * centro(1) + mat[9] * centro(2) + mat[13];
   n_centro(2) = mat[2] * centro(0) + mat[6] * centro(1) + mat[10] * centro(2) + mat[14];

   centroTransformado = n_centro;
}

/// @brief Establece cSolidoOriginal igual a cSolido
bool Malla3D::actualizarColorSolidoOriginal(){
   if(cSolido[0](0) == cSeleccion(0) &&
         cSolido[0](0) == cSeleccion(0) &&
         cSolido[0](0) == cSeleccion(0)) return false;

   for(int i=0; i<v.size(); i++){
      cSolidoOriginal[i] = cSolido[i];
   }

   return true;
}


/* SET Y GET */

// --- TEXTURAS

/// @brief Establece la textura
/// @param archivo archivo imagen de la textura
void Malla3D::setTextura(const std::string & archivo){

	if (textura != nullptr)
		delete textura;

	textura = new Textura(archivo);


   if(es_cuadro)
      asignarPuntosTexturaCuadro(modo_textura);
   // else
	//    asignarPuntosTextura(modo_textura);

}



// --- COLORES

/// @brief Establece el color de la malla
/// @param colorVertices 
/// @param colorLineas 
/// @param colorSolido 
void Malla3D::setColor(Tupla4f colorVertices, Tupla4f colorLineas, Tupla4f colorSolido){
   cVertices.resize(v.size());
   cLineas.resize(v.size()); ///
   cSolido.resize(v.size()); ///

   for(int i=0; i < v.size(); ++i){
      cVertices[i] = colorVertices;
      cLineas[i] = colorLineas;
      cSolido[i] = colorSolido;
   }

   cSolidoOriginal.resize(cSolido.size());
   for(int i=0; i<v.size(); i++){
      cSolidoOriginal[i] = cSolido[i];
   }
}


/// @brief Establece el color de selección
/// @param colorSeleccion 
void Malla3D::setColorSeleccion(Tupla3f colorSeleccion){
   cSeleccion = colorSeleccion;
}


/// @brief Devuelve el color de selección
/// @return 
Tupla3f Malla3D::getColorSeleccion(){
   return cSeleccion;
}


/// @brief Cambia el color sólido de la malla
/// @param nuevoColorSolido 
void Malla3D::setColorSolido(Tupla4f nuevoColorSolido){
   for(int i=0; i < v.size(); ++i){
      cSolido[i] = nuevoColorSolido;
   }
   actualizarColorSolidoOriginal();
}


/// @brief Devuelve el color sólido de la malla
/// @return cSolido (vector de Tupla4f)
std::vector<Tupla4f> Malla3D::getColorSolido(){
   return cSolido;
}


/// @brief Establece el color de sólido el mismo que de selección
void Malla3D::setColorSeleccionSolido(){
   // Hacemos copia del color sólido
   actualizarColorSolidoOriginal();

   // Nuevo color sólido --> el de selección
   Tupla4f nuevoColorSolido = {
      cSeleccion(0),
      cSeleccion(1),
      cSeleccion(2),
      1.0f
   };

   for(int i=0; i < v.size(); ++i){
      cSolido[i] = nuevoColorSolido;
   }
}


/// @brief Reestablece el color sólido a su valor original
void Malla3D::setColorSolidoOriginal(){
   for(int i=0; i < v.size(); ++i){
      cSolido[i] = cSolidoOriginal[i];
   }
}


/// @brief Establece el color sólido al de selección cuando está seleccionado
/// @param valor Si está seleccionado o no
void Malla3D::setSeleccionado(bool valor){
   seleccionado = valor;

   cSolidoOriginal.resize(v.size());

   actualizarColorSolidoOriginal();

   Tupla4f nuevoColorSolido = {
      cSeleccion(0),
      cSeleccion(1),
      cSeleccion(2),
      1.0f
   };

   if(seleccionado){ // se ha seleccionado
      for(int i=0; i < v.size(); ++i){
         cSolido[i] = nuevoColorSolido;
      }
   } else { // se ha deseleccionado
      for(int i=0; i < v.size(); ++i){
         cSolido[i] = cSolidoOriginal[i];
      }
   }
}



// --- MATERIALES 

/// @brief Establece el material
/// @param mat nuevo material
void Malla3D::setMaterial(Material mat){
   m = mat; 
}


/// @brief Devuelve el material de la malla
/// @param mat 
/// @return mmaterial de la malla
Material Malla3D::getMaterial(){
   return m;
}


/// @brief Establece el material de selección
/// @param matSelNuevo 
void Malla3D::setMaterialSeleccion(Material matSelNuevo){
   mSeleccion = matSelNuevo;
}


/// @brief Devuelve el material de selección de la malla
/// @return mSeleccion (material de selección)
Material Malla3D::getMaterialSeleccion(){
   return mSeleccion;
}



// --- OTROS

/// @brief Devuelve el centro
/// @return centro
Tupla3f Malla3D::getCentro(){
   return centro;
}


/// @brief Devuelve el centro con las transformaciones de la matriz de vista
/// @return centroTransformado
Tupla3f Malla3D::getCentroTransformado(){
   return centroTransformado;
}



/* MÉTODOS VBOS */
/// @brief Crea los VBOs de la malla
void Malla3D::crearVBOS(){
   // Crear VBO (si no creado (=0) se crea)
   if(id_vbo_ver == 0) // si no está creado el vbo de vértices
      id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, 3*v.size()*sizeof(float), v.data());

   if(id_vbo_tri == 0) // si no está creado el vbo de triángulos
      id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, 3*f.size()*sizeof(int), f.data());

   // Crear VBO colores
   if(id_vbo_cd == 0)
      id_vbo_cd = CrearVBO(GL_ARRAY_BUFFER, 4*cVertices.size()*sizeof(float), cVertices.data());
   if(id_vbo_cl == 0)
      id_vbo_cl = CrearVBO(GL_ARRAY_BUFFER, 4*cLineas.size()*sizeof(float), cLineas.data());
   if(id_vbo_cs == 0)
      id_vbo_cs = CrearVBO(GL_ARRAY_BUFFER, 4*cSolido.size()*sizeof(float), cSolido.data());

   // Crear VBO normales
   if(id_vbo_nc == 0)
      id_vbo_nc = CrearVBO(GL_ARRAY_BUFFER, 3*nc.size()*sizeof(float), nc.data());
   if(id_vbo_nv == 0)
      id_vbo_nv = CrearVBO(GL_ARRAY_BUFFER, 3*nv.size()*sizeof(float), nv.data());

   // Crear VBO texturas
   if(id_vbo_ct == 0)
      id_vbo_ct = CrearVBO(GL_ARRAY_BUFFER, 3*ct.size()*sizeof(float), ct.data());
   
   // if(id_vbo_cSel == 0)
   //    id_vbo_cSel = CrearVBO(GL_ARRAY_BUFFER, 3*cSeleccion.size()*sizeof(float), cSeleccion.data());

}


/// @brief Método para crear vbo
/// @param tipo_vbo 
/// @param tam 
/// @param puntero_ram 
/// @return id_vbo
GLuint Malla3D::CrearVBO ( GLuint tipo_vbo , GLuint tam , GLvoid * puntero_ram )
{
   GLuint id_vbo ; // resultado: identificador de VBO


   glGenBuffers ( 1 , & id_vbo ); // crear nuevo VBO, obtener identificador
   glBindBuffer ( tipo_vbo , id_vbo ); // activar el VBO usando su identificador

   // esta instrucción hace la transferencia de datos desde RAM hacia GPU
   glBufferData ( tipo_vbo , tam , puntero_ram , GL_STATIC_DRAW );

   glBindBuffer ( tipo_vbo , 0 ); // desactivacion del VBO
   
   return id_vbo ; // devolver el identificador resultado
}
