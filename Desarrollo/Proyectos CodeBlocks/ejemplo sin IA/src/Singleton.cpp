#include "Singleton.h"
#include <Box2D/Box2D.h>
#include <iostream>

Singleton* Singleton::pinstance= 0;

Singleton * Singleton::Instance(){
    if(pinstance == 0){
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
