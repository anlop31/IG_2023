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

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   // completar ......(práctica 2)
   std::vector<Tupla3f> vertices;
   ply::read_vertices(archivo, vertices);

   crearMalla(vertices, num_instancias);
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   crearMalla(archivo, num_instancias);
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias) {
   int cont = 0;
   int i, j;
   int polo_norte = -1;   
   int polo_sur = -1;     
   

   // N = numero instancias
   int N = num_instancias;
   // M = numero vertices del perfil
   int M = perfil_original.size();

   std::vector<Tupla3f> perfil;

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

   perfil.resize(M);
   i=0;
   for (int j=ini; orientacion > 0 ? j<=fin : j>=fin; j += orientacion) {
      perfil[i] = perfil_original[j];
      i++;
   }

   // Definimos los tamaños de los vectores
   v.resize((N*M) + (perfil_original.size()-M)); // En funcion de los polos
   // f.resize(N*M*2);

   // Rotar los vertices (Solo los intermedios) 
   for (i = 0; i < N; ++i) { // 0 -> N 
      for(j = 0; j < M; ++j) { // 0 -> M
         v[(M*i)+j] = Tupla3f({
            perfil[j][0] * cos((2.0*M_PI*i)/float(N)),
            perfil[j][1],
            perfil[j][0] * sin((2.0*M_PI*i)/float(N))
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


}


void ObjRevolucion::asignarPuntosTextura(const modoTextura & modo){
   ct.resize(v.size());

	float alpha, beta, h;

	float s, t;

   switch (modo) {
      case CILINDRICA:
      break;
      case ESFERICA:
      break;
      case PLANA:
      break;
   }
}