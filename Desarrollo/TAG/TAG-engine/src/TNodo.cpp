#include <iostream>

#include "TNodo.h"

TNodo::TNodo()
{
    //ctor
}

TNodo::~TNodo()
{
    //dtor
}

int TNodo::addHijo(TNodo* nodo)
{
    if (nodo != nullptr)
    {
        hijos.push_back(nodo);
    }
    return hijos.size();
}

int TNodo::remHijo(TNodo* nodo)
{
    return 0;

}

bool TNodo::setEntidad(TEntidad* ent)
{
    if(ent != nullptr)
    {
        entidad = ent;
        return true;
    }
    return false;
}

TEntidad *TNodo::getEntidad()
{
    return entidad;
}

TNodo *TNodo::getPadre()
{
    return padre;

}

void TNodo::draw()
{
    entidad->beginDraw();
    for(int i=0; i < hijos.size(); i++)
    {
        //std::cout<<i<<std::endl;
        hijos[i]->draw();
    }
    entidad->endDraw();
}
