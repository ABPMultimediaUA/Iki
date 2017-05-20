#include "TNodo.h"

TNodo::TNodo()
{
    entidad = nullptr;
    padre = nullptr;
}

TNodo::~TNodo()
{
    //dtor
}

int TNodo::addHijo(TNodo* nodo)
{
    if (nodo != nullptr){
        hijos.push_back(nodo);
        nodo->setPadre(this);
    }
    return hijos.size();
}

int TNodo::remHijo(TNodo* nodo)
{
    //recorrer vector y si está eliminarlo y devolver 1, si no 0.
    if (nodo != nullptr){
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
    if(ent != nullptr){
        entidad = ent;
        return true;
    }
    return false;
}

TEntidad *TNodo::getEntidad()
{
    return entidad;
}

void TNodo::setPadre(TNodo* padre)
{
    this->padre = padre;
}

TNodo *TNodo::getPadre()
{
    return padre;
}

void TNodo::draw()
{
    if(entidad != nullptr){
        entidad->beginDraw();
    }
    for(int i=0; i < hijos.size(); i++){
      //  std::cout << " >> Entro en la rama " << std::endl;
        hijos[i]->draw();
    }
    if(entidad != nullptr){
        //std::cout << " << Salgo " << std::endl;
        entidad->endDraw();
    }
}

void TNodo::Trasladar(TVector vec)
{
    static_cast<TTransform*>(padre->getPadre()->getEntidad())->trasladar(vec.X, vec.Y, vec.Z);
}

void TNodo::Rotar(float ang, TVector vec)
{
    static_cast<TTransform*>(padre->getPadre()->getEntidad())->rotar(ang, vec.X, vec.Y, vec.Z);
}

void TNodo::Rotar(float ang)
{
    static_cast<TTransform*>(padre->getPadre()->getEntidad())->rotar(ang);
}

void TNodo::EscalarAbs(float num)
{
    static_cast<TTransform*>(padre->getPadre()->getEntidad())->escalarAbs(num);
}

void TNodo::EscalarRel(TVector vec)
{
    static_cast<TTransform*>(padre->getPadre()->getEntidad())->escalarRel(vec.X, vec.Y, vec.Z);
}


