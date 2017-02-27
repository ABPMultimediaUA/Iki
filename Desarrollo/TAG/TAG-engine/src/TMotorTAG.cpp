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

    return camara;
}

TLuz *TMotorTAG::crearLuz()
{
    TLuz *luz = new TLuz();

    return luz;
}

TMalla *TMotorTAG::crearMalla(char* fichero)
{

}

int TMotorTAG::registrarCamara(TNodo* nod)
{
    //meter el nodo en el registro de camaras,
    //devuelve la posicion en la que ha entrado.
    return 0;
}
int TMotorTAG::registrarLuz(TNodo* nod)
{
    //meter el nodo en el registro de luces,
    //devuelve la posicion en la que ha entrado.
    return 0;
}

void TMotorTAG::setLuzActiva(int i)
{
    //activar la luz del array;
}

void TMotorTAG::setCamaraActiva(int i)
{
    //activar la luz del array;
}
void TMotorTAG::draw()
{
    for(int i= 0; i < camaras.length; i++)
    {
        //recorrer el arbol a la inversa

    }
}
