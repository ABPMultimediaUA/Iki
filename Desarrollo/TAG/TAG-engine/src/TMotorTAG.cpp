#include "TMotorTAG.h"

TMotorTAG::TMotorTAG()
{
    //ctor
}

TMotorTAG::~TMotorTAG()
{
    //dtor
}

TNodo *TMotorTAG::crearNodo(TNodo *padre, TEntidad *ent)
{
    TNodo *nodo = new TNodo();
    nodo->setEntidad(ent);
    padre->addHijo(nodo);

    return nodo;
}

TTransform *TMotorTAG::crearTransform()
{
    TTransform *tranformacion = new TTransform();

    return tranformacion;

}

TCamara *TMotorTAG::crearCamara()
{
    TCamara *camara= new TCamara();

    return camara
}

TLuz *TMotorTAG::crearLuz()
{
    TLuz *luz = new TLuz();
}

TMalla *TMotorTAG::crearMalla(char* fichero)
{

}

