#include <Material.h>

Material::Material(){
    ambiente = {0.2, 0.2, 0.2, 1.0f};
    difuso = {0.8, 0.8, 0.8, 1.0f};
    especular = {0.0, 0.0, 0.0, 1.0f};
    brillo = 0;
}

Material::Material(Tupla4f mdifuso, Tupla4f mespecular, Tupla4f mambiente, float brillo){
    ambiente = mambiente;
    difuso = mdifuso;
    especular = mespecular;
    this->brillo = brillo;
}

void Material::aplicar(){

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiente);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ambiente);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ambiente);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
    glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

}

void Material::operator = (const Material & otro){
   ambiente  = otro.ambiente;
   difuso    = otro.difuso;
   especular = otro.especular;
   brillo    = otro.brillo;
}