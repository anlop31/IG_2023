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


// Cálculo de las normales
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

}



// Dibujar malla
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
   
   // Desactivar texturas
   if (textura != nullptr) {
	  glDisable( GL_TEXTURE_2D );
	  glDisable(GL_TEXTURE_COORD_ARRAY);
   }

   // desactivar uso de array de vértices
   glDisableClientState ( GL_VERTEX_ARRAY );
   glDisableClientState ( GL_COLOR_ARRAY );


   if (glIsEnabled(GL_LIGHTING)){
      glDisableClientState( GL_LIGHTING );
   }
   
}

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

void Malla3D::setColor(Tupla4f colorVertices, Tupla4f colorLineas, Tupla4f colorSolido){
   cVertices.resize(v.size());
   cLineas.resize(v.size()); ///
   cSolido.resize(v.size()); ///

   for(int i=0; i < v.size(); ++i){
      cVertices[i] = colorVertices;
      cLineas[i] = colorLineas;
      cSolido[i] = colorSolido;
   }
}

void Malla3D::setMaterial(Material mat){
   m = mat; // asignamos material
}


void Malla3D::setTextura(const std::string & archivo){

	if (textura != nullptr)
		delete textura;

	textura = new Textura(archivo);

	asignarPuntosTextura(modo_textura);

}

/// @brief Revisar
/// @param modo 
void Malla3D::asignarPuntosTextura(const modoTextura & modo){

	ct.resize(v.size());


	for (int i = 0; i < ct.size(); i++){
		ct[i] = {v[i](0), (v[i](1) - v.front()(1) ) / (v.back()(1) - v.front()(1))} ;
	}

}

void Malla3D::asignarPuntosTexturaCuadro(const modoTextura & modo){

	ct.clear();

   ct[0] = {0.0f, 0.0f};
   ct[1] = {1.0f, 0.0f};
   ct[2] = {0.0f, 1.0f};
   ct[3] = {1.0f, 1.0f};
}

