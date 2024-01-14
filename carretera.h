#ifndef CARRETERA_H_INCLUDED
#define CARRETERA_H_INCLUDED

#include "auxiliar.h"
#include "malla.h"


class Carretera : public Malla3D{
    private:
    float ancho;
    float largo;

    public:
    Carretera(const float ancho=10, const float largo=20) ;
    
    // SET y GET
    float getAncho();
    float getLargo();

};




#endif