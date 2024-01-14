#include "TroncoCabeza.h"

/// @brief Constructor del tronco y la cabeza
/// @param h Altura del tronco
/// @param r Radio del tronco
TroncoCabeza::TroncoCabeza(float h=1, float r=0.5){
    h_tronco = h;
    r_tronco = r;

    
    tronco = new Cilindro(4, 10, h_tronco, r_tronco);
    cabeza = new Esfera(10, 20, r_tronco-r_tronco*0.40); // menos el 40%

    // cabeza = new Cabeza(r_tronco-r_tronco*0.40);

    r_cabeza = cabeza->getRadio();

    cabeza->setColor(
      Tupla4f(1.0f, 0.0f, 0.0f, 1.0f), // color vértices
      Tupla4f(1.0f, 0.0f, 1.0f, 1.0f), // color líneas
      Tupla4f(1.0f, 0.0f, 0.0f, 1.0f)  // color sólido
   );

    limiteCabeza = tronco->getRadio() * 0.8;
}

/// @brief Método draw del tronco y la cabeza
void TroncoCabeza::draw(){
    glPushMatrix();
        glPushMatrix();
            glTranslatef(0,0, desplazamientoCabeza); // AÑADIDA TRASLACION
            glTranslatef(0, h_tronco+r_cabeza, 0);
            cabeza->draw();
        glPopMatrix();
        tronco->draw();
    glPopMatrix();
}

/* MÉTODOS SET Y GET */

/// @brief Obtener la altura del tronco
/// @return Altura del tronco (h_tronco)
float TroncoCabeza::getAlturaTronco(){
    return h_tronco;
}

/// @brief Obtener el radio del tronco
/// @return Radio del tronco (r_tronco)
float TroncoCabeza::getRadioTronco(){
    return r_tronco;
}

/// @brief Obtener el radio de la cabeza
/// @return Radio de la cabeza (r_cabeza)
float TroncoCabeza::getRadioCabeza(){
    return r_cabeza;
}


/* MATERIALES */

/// @brief Establecer el material del cuerpo
/// @param m 
void TroncoCabeza::setMaterialCuerpo(Material m){
    cabeza->setMaterial(m);
    tronco->setMaterial(m);
}

/// @brief Establecer el material del tronco
/// @param m 
void TroncoCabeza::setMaterialTronco(Material m){
    tronco->setMaterial(m);
}

/// @brief Establecer el material de la cabeza
/// @param m 
void TroncoCabeza::setMaterialCabeza(Material m){
    cabeza->setMaterial(m);
}


/* MODIFICADORES */
/// @brief Modifica el desplazamiento de la cabeza
/// @param valor 
void TroncoCabeza::modificaDesplazamientoCabeza(float valor){
    if(desplazamientoCabeza + valor <= -limiteCabeza )
        desplazamientoCabeza = -limiteCabeza;
    else if(desplazamientoCabeza + valor >= limiteCabeza )
        desplazamientoCabeza = limiteCabeza;
    else
        desplazamientoCabeza += valor;    
}