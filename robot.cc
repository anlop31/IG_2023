#include "robot.h"

Robot::Robot(){

}

void Robot::draw(){
        glPushMatrix ();
            // Posibles operaciones de transformación
            tronco . draw ();
            // transformacionCuello
            cabeza . draw ();
            // transformacion IngleIzda
            piernaIzda . draw ();
            // transformacion IngleDcha
            piernaDcha . draw ();
            // transformacion HombroIzdo
            brazoIzdo . draw ();
            // transformacion HombroDcho
            brazoDcho . draw ();
        glPopMatrix ();
}