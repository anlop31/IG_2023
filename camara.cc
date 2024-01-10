#include "auxiliar.h"
#include "camara.h"

using namespace std;

/// @brief Constructor de cámara
/// @param eye Dónde está la cámara
/// @param at Adónde mira
/// @param up "hacia arriba"
/// @param tipo Ortogonal o perspectiva
/// @param near Parámetro near
/// @param far Parámetro far
Camara::Camara(
    Tupla3f eye, Tupla3f at, Tupla3f up,
    int tipo,
    float near, float far)
{
    this->eye = eye;
    this->at = at;
    this->up = up;

    this->tipo = tipo;
    
    this->near = near;
    this->far = far;
}

/* ROTACIONES, MOVIMIENTOS Y ZOOM */

/// @brief Rotar en x cuando examinas un objeto
/// @param angle Ángulo de rotación
void Camara::rotarXExaminar(float angle){

    Tupla3f eye_at = eye - at; // es el vector de eye a at?

	eye_at(1) = cos(angle) * eye_at(1) - sin(angle) * eye_at(2);
	eye_at(2) = sin(angle) * eye_at(1) + cos(angle) * eye_at(2);

	eye = eye_at + at;
}

/// @brief 
/// @param angle Ángulo de rotación
void Camara::rotarYExaminar(float angle){
    Tupla3f eye_at = eye - at;

    eye_at(0) = cos(angle) * eye_at(0) + sin(angle) * eye_at(2);
    eye_at(2) = -sin(angle) * eye_at(0) + cos(angle) * eye_at(2);

	eye = eye_at + at;
}

/// @brief 
/// @param angle Ángulo de rotación 
void Camara::rotarZExaminar(float angle){

}

/// @brief Rota la cámara sobre el ángulo x en primera persona
/// @param angle Ángulo de rotación
void Camara::rotarXFirstPerson(float angle){
    Tupla3f at_eye = at - eye;

	at_eye(1) = cos(angle) * at_eye(1) - sin(angle) * at_eye(2);
    at_eye(2) = sin(angle) * at_eye(1) + cos(angle) * at_eye(2);

	at = at_eye + eye; // lo que cambia es el at
}

/// @brief Rota la cámara sobre el ángulo y en primera persona
/// @param angle Ángulo de rotación
void Camara::rotarYFirstPerson(float angle){
    Tupla3f at_eye = at - eye;

	at_eye(0) = cos(angle) * at_eye(0) + sin(angle) * at_eye(2);
    at_eye(2) = -sin(angle) * at_eye(0) + cos(angle) * at_eye(2);

	at = at_eye + eye; // lo que cambia es el at
}

/// @brief Rota la cámara sobre el ángulo z en primera persona
/// @param angle Ángulo de rotación
void Camara::rotarZFirstPerson(float angle){

	// up(0) = cos(angle) * up(0) + sin(angle) * up(2);
    // up(2) = -sin(angle) * up(0) + cos(angle) * up(2);
}

/// @brief Cambia la posición de la cámara
/// @param x 
/// @param y 
/// @param z 
void Camara::mover(float x, float y, float z){
    at = {
        at(0) + x,
        at(1) + y,
        at(2) + z
    };
	
    eye = {
        eye(0) + x,
        eye(1) + y,
        eye(2) + z
    };
}

/// @brief La cámara recalcula el valor de sus parámetros de giro en x y en y en primera persona
/// @param x observer_angle_x
/// @param y observer_angle_y
void Camara::girar(float x, float y){
    if ((at - eye)(2) > 0) y = -y;

	rotarXFirstPerson(-y *  M_PI/180);
    rotarYFirstPerson(-x * M_PI/180);
}

/// @brief La cámara recalcula el valor de sus parámetros de giro en x y en y examinando
/// @param x observer_angle_x
/// @param y observer_angle_y
void Camara::girarExaminar(float x, float y){
    rotarXExaminar( y * M_PI/180);
    rotarYExaminar( x * M_PI/180);
}

/// @brief 
/// @param factor 
void Camara::zoom(float factor){
    bottom *= factor;
    top *= factor;
    left *= factor;
    right *= factor;
}


/* SET Y GET */

/// @brief Establece la cámara
void Camara::setObserver(){
    gluLookAt(  eye(0), eye(1), eye(2),
                at(0), at(1), at(2),
                up(0), up(1), up(2)
            );
}

/// @brief Establece la proyección perspectiva u ortogonal
void Camara::setProyeccion(){
    if(tipo == 0){ // 0: perspectiva
        glFrustum(left, right, bottom, top, near, far);
    }
    else{ // 1: ortogonal
        glOrtho(left, right, bottom, top, near, far);
    }
}

/// @brief Establece un nuevo valor de left
/// @param new_left 
void Camara::setLeft(float new_left){
    left = new_left;
}

/// @brief Establece un nuevo valor de right
/// @param new_right 
void Camara::setRight(float new_right){
    right = new_right;
}

/// @brief Establece un nuevo valor de bottom
/// @param new_bottom 
void Camara::setBottom(float new_bottom){
    bottom = new_bottom;
}

float Camara::getLeft(){
    return left;
}

float Camara::getRight(){
    return right;
}

/// @brief Establece un nuevo valor de top
/// @param new_top 
void Camara::setTop(float new_top){
    top = new_top;
}

/// @brief Devuelve el valor bottom de la cámara
/// @return 
float Camara::getBottom(){
    return bottom;
}

/// @brief Devuelve el valor top de la cámara
/// @return 
float Camara::getTop(){
    return top;
}

/// @brief Devuelve el parámetro at de la cámara
/// @return at
Tupla3f Camara::getAt(){
    return at;
}

/// @brief Devuelve el parámetro eye de la cámara
/// @return eye
Tupla3f Camara::getEye(){
    return eye;
}

/// @brief Devuelve el parámetro up de la cámara
/// @return up
Tupla3f Camara::getUp(){
    return up;
}

/// @brief Establece el valor de at
/// @param newAt 
void Camara::setAt(Tupla3f newAt){
    at = newAt;
}

/// @brief Establece el valor de eye
/// @param newEye 
void Camara::setEye(Tupla3f newEye){
    eye = newEye;
}

/// @brief Establece el valor de Up
/// @param newUp 
void Camara::setUp(Tupla3f newUp){
    up = newUp;
}

/// @brief Establece el objeto seleccionado por la cámara
/// @param objetoSeleccionado 
void Camara::setObjetoSeleccionado(std::string objeto){
    objetoSeleccionado = objeto;
}

/// @brief Devuelve el objeto que tiene seleccionado la cámara
/// @return 
std::string Camara::getObjetoSeleccionado(){
    return objetoSeleccionado;
}