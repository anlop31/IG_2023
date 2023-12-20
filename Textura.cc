#include "Textura.h"
#include "jpg_imagen.hpp"

Textura::Textura(std::string archivo){
    jpg::Imagen * img = new jpg::Imagen(archivo);

	unsigned char * leidos;

	width = img->tamX();
	height = img->tamY();

	for (unsigned i = 0; i < height; i++){
		for (unsigned j = 0; j < width; j++){
			leidos = img->leerPixel(j, height - i - 1);
			// introducimos R
			data.push_back(*leidos);
			leidos++;

			// introducimos G
			data.push_back(*leidos);
			leidos++;

			// introducimos B
			data.push_back(*leidos);
			leidos++;
		}


	}


	// inicializamos a valor nulo
	textura_id = -1;
}


/* 
*  Habilitar las texturas en opengl, habilitar el identificador
*  de textura, y si la textura tiene asociada generacion atuomatica
*  de coordenadas, fijar los parametros opengl para dicha generacion.
* 
*  La primera vez que se intenta activar una textura, se debe crear la
*  textura, esto significa que se deben leer los texels de un archivo y
*  enviarlos a la GPU, inicializadno el identificador de textura de OpenGL.
*/
void Textura::activar(){
    // if(textura_id == 0){ // no está creada?
    //     // leer texels de archivo y enviarlos a la GPU
    //     // textura_id = ; // qué valor se le da?

    // }

    // glGenTextures(1, &textura_id);



	glEnable( GL_TEXTURE_2D );

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// sin esta linea no funcionan
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (textura_id == -1){
		glGenTextures(1, &textura_id);
		glBindTexture(GL_TEXTURE_2D, textura_id);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.data());

	}

	glBindTexture(GL_TEXTURE_2D, textura_id);
}