#include "cabeza.h"


Cabeza::Cabeza(float r_cabeza){
    cabeza = new Esfera(10, 20, r_cabeza); 

    // altura y radio
    oreja1 = new Cilindro(10, 20, r_cabeza * 4, r_cabeza * 0.2);
    oreja2 = new Cilindro(10, 20, r_cabeza * 4, r_cabeza * 0.2);


    cabeza->setColor(
        Tupla4f(1.0f, 0.0f, 0.0f, 1.0f), // color vértices
        Tupla4f(1.0f, 0.0f, 1.0f, 1.0f), // color líneas
        Tupla4f(1.0f, 0.0f, 0.0f, 1.0f)  // color sólido
    );

    oreja1->setColor(
        Tupla4f(1.0f, 0.0f, 0.0f, 1.0f), // color vértices
        Tupla4f(1.0f, 0.0f, 1.0f, 1.0f), // color líneas
        Tupla4f(1.0f, 0.0f, 1.0f, 1.0f)  // color sólido
    );

    oreja2->setColor(
        Tupla4f(1.0f, 0.0f, 0.0f, 1.0f), // color vértices
        Tupla4f(1.0f, 0.0f, 1.0f, 1.0f), // color líneas
        Tupla4f(1.0f, 0.0f, 1.0f, 1.0f)  // color sólido
    );

}

/// @brief Método draw de la cabeza
void Cabeza::draw(){
    glPushMatrix();
        glPushMatrix();
            glTranslatef(-r_cabeza * 0.7, r_cabeza, 0);
            oreja2->draw();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(r_cabeza * 0.7, r_cabeza, 0);
            oreja1->draw();
        glPopMatrix();
        cabeza->draw();
    glPopMatrix();
}

/* MÉTODOS SET Y GET */

/// @brief Obtener el radio de la cabeza
/// @return Radio de la cabeza (r_cabeza)
float Cabeza::getRadioCabeza(){
    return r_cabeza;
}


/* MATERIALES */

/// @brief Establecer el material de la cabeza
/// @param m 
void Cabeza::setMaterialCabeza(Material m){
    cabeza->setMaterial(m);
}

void Cabeza::setMaterialOrejas(Material m){
    oreja1->setMaterial(m);
    oreja2->setMaterial(m);
}


/* MODIFICADORES */
/// @brief Modifica el desplazamiento de la cabeza
/// @param valor 
// void Cabeza::modificaDesplazamientoCabeza(float valor){
//     if(desplazamientoCabeza + valor <= -limiteCabeza )
//         desplazamientoCabeza = -limiteCabeza;
//     else if(desplazamientoCabeza + valor >= limiteCabeza )
//         desplazamientoCabeza = limiteCabeza;
//     else
//         desplazamientoCabeza += valor;    
// }