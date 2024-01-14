#include "robot.h"

/// @brief Constructor de Robot
Robot::Robot(){
    /* Brazos */
    brazo_izq = new Brazo(80, 10);
    brazo_der = new Brazo(80, 10);
    brazo_der->setSentidoPositivo(true);

    r_brazo_izq = brazo_izq->getRadioBrazo();
    r_brazo_der = brazo_der->getRadioBrazo();

    h_brazo_izq = brazo_izq->getAlturaBrazo();
    h_brazo_der = brazo_der->getAlturaBrazo();

    /* troncoPiernas */
    troncoPiernas = new TroncoPiernas();

    h_tronco = troncoPiernas->getAlturaTronco();
    r_tronco = troncoPiernas->getRadioTronco();

    troncoPiernas->setSentidoPositivoPiernaIzq(true);
}

/// @brief Método draw de robot
void Robot::draw(){
    glPushMatrix();
        glTranslatef(0, 0, desplazamiento);

        // RESTO DEL CUERPO
        glPushMatrix();
            troncoPiernas->draw();
        glPopMatrix();

        // BRAZOS
        glPushMatrix();
            glPushMatrix(); // brazo derecho
                glTranslatef(r_tronco+r_brazo_der/2, h_brazo_der/2, 0); // colocarlo a la der y arriba 
                brazo_der->draw();
            glPopMatrix();

            glPushMatrix(); // brazo izquierdo
                glTranslatef(-( r_tronco+r_brazo_izq/2 ), h_brazo_izq/2, 0); // colocarlo a la izq y arriba
                brazo_izq->draw();
            glPopMatrix();
        glPopMatrix();

    glPopMatrix();
}


/* GRADOS DE LIBERTAD INDIVIDUALES */

/// @brief Modifica el ángulo de giro del brazo derecho
/// @param valor 
void Robot::modificaGiroBrazoDer(float valor){
    brazo_der->modificaGiroBrazo(valor);
}

/// @brief Modifica el ángulo de giro del brazo izquierdo
/// @param valor 
void Robot::modificaGiroBrazoIzq(float valor){
    brazo_izq->modificaGiroBrazo(valor);
}

/// @brief Modifica el ángulo de giro de la pierna izquierda
/// @param valor 
void Robot::modificaGiroPiernaIzq(float valor){
    troncoPiernas->modificaGiroPiernaIzq(valor);
}

/// @brief Modifica el ángulo de giro de la pierna derecha
/// @param valor 
void Robot::modificaGiroPiernaDer(float valor){
    troncoPiernas->modificaGiroPiernaDer(valor);
}


/* GRADOS DE LIBERTAD */ 

/// @brief Modifica el ángulo de giro de las piernas
/// @param valor 
void Robot::modificaGiroPiernas(float valor){
    troncoPiernas->modificaGiroPiernaIzq(valor);
    troncoPiernas->modificaGiroPiernaDer(valor);
}

/// @brief Modifica el ángulo de giro de los brazos
/// @param valor 
void Robot::modificaGiroBrazos(float valor){
    brazo_izq->modificaGiroBrazo(valor);
    brazo_der->modificaGiroBrazo(valor);
}

/// @brief Modifica el desplazamiento del robot
/// @param valor 
void Robot::modificaDesplazamiento(float valor){
    
    desplazamiento += valor;

    // que se muevan los brazos y piernas cuando se mueve
    // modificaGiroBrazos(5);
    // modificaGiroPiernas(5);
}

/// @brief Modifica el desplazamiento del robot
/// @param valor 
void Robot::modificaDesplazamientoAislado(float valor){
    desplazamiento += valor;
}

void Robot::modificaDesplazamientoCabeza(float valor){
    troncoPiernas->modificaDesplazamientoCabeza(valor);
}

/// @brief Cambiar el sentido de ambos brazos
void Robot::cambiarSentidosBrazos(){
    brazo_izq->setSentidoPositivo(!brazo_izq->getSentidoPositivo());
    brazo_der->setSentidoPositivo(!brazo_der->getSentidoPositivo());
}

/// @brief Cambiar el sentido de ambas piernas
void Robot::cambiarSentidosPiernas(){
    troncoPiernas->setSentidoPositivoPiernaIzq(!troncoPiernas->getSentidoPositivoPiernaIzq());
    troncoPiernas->setSentidoPositivoPiernaDer(!troncoPiernas->getSentidoPositivoPiernaDer());
}

/* ANIMAR MODELO JERÁRQUICO */

/// @brief Animar modelo jerárquico modificando todos sus grados de libertad
void Robot::animarModeloJerarquico(){
    modificaDesplazamientoAislado(velDesplazamiento);

    modificaGiroBrazos(velBrazos);
    modificaGiroPiernas(velPiernas);
}

/// @brief Cambiar la velocidad de todos sus grados de libertad
/// @param valor 
void Robot::cambiarVelocidad(float valor){
    cambiarVelocidadDesplazamiento(valor);
    cambiarVelocidadGiroBrazos(valor);
    cambiarVelocidadGiroPiernas(valor);
}

/// @brief Cambiar velocidad del desplazamiento
/// @param valor 
void Robot::cambiarVelocidadDesplazamiento(float valor){
    if( (velDesplazamiento + valor) <= 0 )
        velDesplazamiento = 0;
    else
        velDesplazamiento += valor;
}

/// @brief Cambiar la velocidad del giro de los brazos
/// @param valor 
void Robot::cambiarVelocidadGiroBrazos(float valor){
    if( (velBrazos + valor) <= 0 )
        velBrazos = 0;
    else
        velBrazos += valor;
}

/// @brief Cambiar la velocidad del giro de las piernas
/// @param valor 
void Robot::cambiarVelocidadGiroPiernas(float valor){
    if( (velPiernas + valor) <= 0 )
        velPiernas = 0;
    else
        velPiernas += valor;
}


/* MÉTODOS SET Y GET */

/// @brief Obtener el sentido de giro del brazo izquierdo
/// @return true si el sentido positivo y false si al contrario
bool Robot::getSentidoPositivoBrazoIzq(){
    return brazo_izq->getSentidoPositivo();
}

/// @brief Obtener el sentido de giro del brazo derecho
/// @return true si el sentido positivo y false si al contrario
bool Robot::getSentidoPositivoBrazoDer(){
    return brazo_der->getSentidoPositivo();
}

/// @brief Obtener el ángulo de giro del brazo izquierdo
/// @return El ángulo de giro del brazo izquierdo
float Robot::getAnguloBrazoIzq(){
    return brazo_izq->getGiroBrazo();
}

/// @brief Obtener el ángulo de giro del brazo derecho
/// @return El ángulo de giro del brazo derecho
float Robot::getAnguloBrazoDer(){
    return brazo_der->getGiroBrazo();
}


/* MATERIALES */

/// @brief Establecer el material del robot
/// @param m 
void Robot::setMaterialRobot(Material m){
    troncoPiernas->setMaterialCuerpo(m);
    brazo_izq->setMaterialBrazo(m);
    brazo_der->setMaterialBrazo(m);
}

/// @brief Establecer el material de las piernas
/// @param m 
void Robot::setMaterialPiernas(Material m){
    troncoPiernas->setMaterialPiernas(m);
}

/// @brief Establecer el material de los brazos
/// @param m 
void Robot::setMaterialBrazos(Material m){
    brazo_izq->setMaterialBrazo(m);
    brazo_der->setMaterialBrazo(m);
}

/// @brief Establecer el material del tronco
/// @param m 
void Robot::setMaterialTronco(Material m){
    troncoPiernas->setMaterialTronco(m);
}

/// @brief Establecer el material de la cabeza
/// @param m 
void Robot::setMaterialCabeza(Material m){
    troncoPiernas->setMaterialCabeza(m);
}