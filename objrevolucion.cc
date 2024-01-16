#include "auxiliar.h"
#include "objrevolucion.h"
#include "ply_reader.h"
#include "cono.h"
#include "cilindro.h"
#include "esfera.h"

using namespace std;


// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

/// @brief Constructor de objeto de revolución a través de un archivo
/// @param archivo 
/// @param num_instancias 
/// @param tapa_sup true si tiene, false si no
/// @param tapa_inf true si tiene, false si no
ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   // completar ......(práctica 2)
   std::vector<Tupla3f> vertices;
   ply::read_vertices(archivo, vertices);

   crearMalla(vertices, num_instancias);
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)


/// @brief Constructor de objeto de revolución a través de un vector de vértices
/// @param archivo 
/// @param num_instancias 
/// @param tapa_sup true si tiene, false si no
/// @param tapa_inf true si tiene, false si no
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   crearMalla(archivo, num_instancias);
}

/// @brief Método para crear la malla del objeto de revolución
/// @param perfil_original vértices
/// @param num_instancias número de instancias del perfil
void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias) {
   int cont = 0;
   int i, j;
   int polo_norte = -1;   
   int polo_sur = -1;     
   

   // N = numero instancias
   int N = num_instancias;
   this->N = N;
   // M = numero vertices del perfil
   int M = perfil_original.size();
   this->M = M;

   std::vector<Tupla3f> perfil_modificado;

   // Definimos el orden de lectura de los vertices (de arriba a abajo)
   int ini = 0, fin = perfil_original.size()-1, orientacion=1;
   if (perfil_original[fin][1] > perfil_original[ini][1]) {
      ini = fin;
      fin = 0;
      orientacion = -1;
   }

   // Comprobamos si existe Polo NORTE
   if (fabs(perfil_original[ini][0] - perfil_original[ini][0])  <= EPSILON
      && fabs(perfil_original[ini][2] - perfil_original[ini][2])  <= EPSILON) {
      polo_norte = ini;
      ini += orientacion;
      M--;
   }
   
   // Comprobamos si existe Polo SUR
   if (fabs(perfil_original[fin][0] - perfil_original[fin][0]) <= EPSILON
      && fabs(perfil_original[fin][2] - perfil_original[fin][2])  <= EPSILON) {
      polo_sur = fin;
      fin -= orientacion;
      M--;
   }

   perfil_modificado.resize(M);
   i=0;
   for (int j=ini; orientacion > 0 ? j<=fin : j>=fin; j += orientacion) {
      perfil_modificado[i] = perfil_original[j];
      i++;
   }

   // Definimos los tamaños de los vectores
   v.resize((N*M) + (perfil_original.size()-M)); // En funcion de los polos
   // f.resize(N*M*2);

   // Rotar los vertices (Solo los intermedios) 
   for (i = 0; i < N; ++i) { // 0 -> N 
      for(j = 0; j < M; ++j) { // 0 -> M
         v[(M*i)+j] = Tupla3f({
            perfil_modificado[j][0] * cos((2.0*M_PI*i)/float(N)),
            perfil_modificado[j][1],
            perfil_modificado[j][0] * sin((2.0*M_PI*i)/float(N))
         });
      }  
   }

   // Insertamos Polo norte
   if (polo_norte >= 0) {
      v[N*M] =  perfil_original[polo_norte];
   }
   // Insertamos Polo sur
   if (polo_sur >= 0)
      v[N*M + (polo_norte >= 0)] = perfil_original[polo_sur];

   // Generar las caras
   for (i = 0; i < N; ++i) {
      for(j = 0; j < M-1; ++j) {
         int a = M*i+j; // antes M*i+j
         int b = M*((i+1)%N)+j;

         // Triangulo Arriba
         f.push_back(Tupla3i( a, b, b+1 ));
         cont++;
         // Triangulo Abajo
         f.push_back(Tupla3i( a, b+1, a+1 ));

         cont++;
      }
   }
   
   // Generar las tapas
   if (polo_norte >= 0) {
      int indice = N*M;
      for (i=0; i<N; ++i) {
         f.push_back(Tupla3i( (M*i), indice, (M*(i+1))%(N*M) ));
         cont++;
      }
   }

   if (polo_sur >= 0) {
      int indice = M*N + (polo_norte >= 0);
      for (i = 1; i <=N; ++i) {
         f.push_back(Tupla3i( indice, ((M*i)-1), ((M*(i%N+1))-1) ));

         cont++;
      }
   }
   
   calcularNormales();
   calcularCentro();

   perfil = perfil_modificado;
   this->num_instancias = num_instancias;

   modo_textura = ESFERICA;
   asignarPuntosTextura(modo_textura);
}

/// @brief Método para asignar los puntos de textura del objeto de revolución
/// @param modo Modo de la textura (ESFERICA, CILINDRICA o PLANA)
void ObjRevolucion::asignarPuntosTextura(const modoTextura & modo){
  
   ct.resize(v.size());

   float alpha, beta, h;

	float s, t;

	switch (modo){
		case CILINDRICA:
			for (int i = 0; i < ct.size(); i++){
				alpha = atan2( v[i](2), v[i](0) ); // atan2(z,x)
				h = v[i](1); // h = y

            // se lo restamos a 1 porque alpha puede estar fuera de [0, 2*M_PI]
				s = 1 - ( 0.5 + (alpha/(M_PI*2)) ); // está entre [-0.5, 0.5]
				s += 0.5; // entre [0, 1]
				s = fmod(s, 1.0); // asegurarnos que esté entre [0, 1]

            // t = perfil[0](y) / (perfil[perfil.size](y) - perfil[0](y))
				t = (h - perfil.front()(1) ) / (perfil.back()(1) - perfil.front()(1)) ;

				ct[i] = {s, t};

			}

			for (int i = (perfil.size() * num_instancias); i < perfil.size() * (num_instancias + 1); i++){
				alpha = atan2( v[i](2), v[i](0) );
				h = v[i](1);

				s = 1.0f;
				t = (h - perfil.front()(1) ) / (perfil.back()(1) - perfil.front()(1)) ;

				ct[i] = {s, t};
			}

			break;

		case ESFERICA:
			for (int i = 0; i < ct.size(); i++){
            // atan2(z,x)
				alpha = atan2( v[i](2), v[i](0) );
            // atan2(y, raiz de x^2+z^2)
				beta = atan2( v[i](1), sqrt( pow(v[i](0), 2) + pow (v[i](2), 2) ) ); 

            // se lo restamos a 1 porque alpha puede estar fuera de [0, 2*M_PI]
				s = 1 - ( 0.5 + (alpha/(M_PI*2)) ); // está entre [-0.5, 0.5]
				s += 0.5; // entre [0, 1]
				s = fmod(s, 1.0); // asegurarnos que esté entre [0, 1]
				t = 0.5 + beta/M_PI;

				ct[i] = {s, t};
			}

			// Asignar coordenadas de textura a los extremos
			for (int i = 0; i < v.size(); i = i + perfil.size()){
            // Calcular el índice del vértice central del extremo
				int e = i + perfil.size()/2;
				alpha = atan2( v[e](2), v[e](0) );

				s = 1 - ( 0.5 + (alpha/(M_PI*2)) );
				s += 0.5;
				s = fmod(s, 1.0);

				ct[i] = {s, 0.0f};
				ct[i + perfil.size() - 1] = {s, 1.0f};

			}

			for (int i = perfil.size() * num_instancias ; i < v.size(); i++){
				alpha = atan2( v[i](2), v[i](0) );
				beta = atan2( v[i](1), sqrt( pow(v[i](0), 2) + pow (v[i](2), 2) ) );

				s = 1.0;
				t = 0.5 + beta/M_PI;

				ct[i] = {s, t};
			}



			break;
		case PLANA:
			for (int i = 0; i < ct.size(); i++){
				ct[i] = {v[i](0), (v[i](1) - v.front()(1) ) / (v.back()(1) - v.front()(1))} ;
			}
			break;
	}
}