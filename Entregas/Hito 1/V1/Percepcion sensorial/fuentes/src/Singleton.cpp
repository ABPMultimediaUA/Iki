#include "Singleton.h"
#include <Box2D/Box2D.h>

Singleton* Singleton::pinstance= nullptr;

Singleton * Singleton::Instance(){
    if(pinstance == nullptr){
        pinstance= new Singleton;
    }
    return pinstance;
}





Singleton::Singleton()
{
    //ctor
}

Singleton::~Singleton()
{
    //dtor
}
