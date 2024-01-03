#include "auxiliar.h"
#include "camara.h"

/// @brief Constructor de cámara
/// @param eye Dónde está la cámara
/// @param at Adónde mira
/// @param up "hacia arriba"
/// @param tipo Ortogonal o perspectiva
/// @param left 
/// @param right 
/// @param near
/// @param far
Camara::Camara(
    Tupla3f eye, Tupla3f at, Tupla3f up,
    int tipo,
    float left, float right, float near, float far)
{
    this->eye = eye;
    this->at = at;
    this->up = up;

    this->tipo = tipo;

    this->left = left;
    this->right = right;
    this->near = near;
    this->far = far;
}

/* ROTACIONES, MOVIMIENTOS Y ZOOM */

/// @brief Rotar en x cuando examinas un objeto
/// @param angle Ángulo de rotación
void Camara::rotarXExaminar(float angle){
    // cambia el eye????
    // eye.x += angle??
}

/// @brief 
/// @param angle Ángulo de rotación
void Camara::rotarYExaminar(float angle){

}

/// @brief 
/// @param angle Ángulo de rotación 
void Camara::rotarZExaminar(float angle){

}

/// @brief 
/// @param angle Ángulo de rotación
void Camara::rotarXFirstPerson(float angle){
    // cambia el at????
    // at.x += angle??
}

/// @brief 
/// @param angle Ángulo de rotación
void Camara::rotarYFirstPerson(float angle){

}

/// @brief 
/// @param angle Ángulo de rotación
void Camara::rotarZFirstPerson(float angle){

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

}

/// @brief La cámara recalcula el valor de sus parámetros de giro en x y en y examinando
/// @param x observer_angle_x
/// @param y observer_angle_y
void Camara::girarExaminar(float x, float y){

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

/// @brief 
void Camara::setObserver(){
    gluLookAt(  eye(0), eye(1), eye(2),
                at(0), at(1), at(2),
                up(0), up(1), up(2)
            );
}

/// @brief 
void Camara::setProyeccion(){
    if(tipo == 0){ // 0: perspectiva
        glFrustum(left, right, bottom, top, near, far);
    }
    else{ // 1: ortogonal
        glOrtho(left, right, bottom, top, near, far);
    }
}
