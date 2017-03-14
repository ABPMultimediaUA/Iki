#include "TNodo.h"

TNodo::TNodo()
{
//    entidad = nullptr;
 //   padre = nullptr;
}

TNodo::~TNodo()
{
    //dtor
}

int TNodo::addHijo(TNodo* nodo)
{
    if (nodo){
        hijos.push_back(nodo);
    }
    return hijos.size();
}

int TNodo::remHijo(TNodo* nodo)
{
    //recorrer vector y si está eliminarlo y devolver 1, si no 0.
    if (nodo){
        vector<TNodo*>::iterator it = hijos.begin();
        while(it != hijos.end()){
            if(*it == nodo) {
                hijos.erase(it);
                return 1;
            }
            ++it;
        }
    }
    return 0;
}
/*
    for(int i=0; i < hijos.size(); i++)
    {
        if(hijos[i] == nodo)
        {
            hijos.erase(hijos.begin() + i);
            return 1;
        }
    }
*/

bool TNodo::setEntidad(TEntidad* ent)
{
    if(ent){
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
    if(entidad){
        entidad->beginDraw();
    }
    for(int i=0; i < hijos.size(); i++){
        //std::cout<<i<<std::endl;
        hijos[i]->draw();
    }
    if(entidad){
        entidad->endDraw();
    }
}
