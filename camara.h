#include "auxiliar.h"

class Camara {
    private:

    Tupla3f eye;
    Tupla3f at;
    Tupla3f up;

    int tipo;
    float left, right, near, far, bottom, top; // o bien aspect, fov, near, far;

    std::string objetoSeleccionado = "NINGUNO";

    public:
    Camara(
        Tupla3f eye, Tupla3f at, Tupla3f up,
        int tipo,
        float near, float far
    );

    void rotarXExaminar(float angle);
    void rotarYExaminar(float angle);
    void rotarZExaminar(float angle); 

    void rotarXFirstPerson(float angle);
    void rotarYFirstPerson(float angle);
    void rotarZFirstPerson(float angle);
    
    void mover(float x, float y, float z);
    void girar (float x, float y);
    void girarExaminar(float x, float y);
    void zoom(float factor);

    /* SET Y GET */
    void setObserver(); // { gluLookAt(...) } completar
    void setProyeccion();

    void setLeft(float new_left);
    void setRight(float new_right);
    void setBottom(float new_bottom);
    void setTop(float new_top);

    float getLeft();
    float getRight();
    float getBottom();
    float getTop();

    Tupla3f getAt();
    Tupla3f getEye();
    Tupla3f getUp();

    void setAt(Tupla3f newAt);
    void setEye(Tupla3f newEye);
    void setUp(Tupla3f newUp);  

    void setObjetoSeleccionado(std::string objetoSeleccionado);
    std::string getObjetoSeleccionado();  
};