#include "World.h"
#include <Box2D/Box2D.h>
#include <iostream>

#define VELITER 10              //NUMERO DE ITERACION POR TICK PARA CALCULAR LA VELOCIDAD
#define POSITER 10              //NUMERO DE ITERACIONES POR TICK PARA CALCULAR LA POSICION
#define TIMESTEP 1.0f / 250.0f     //TIEMPO DE REFRESCO

World* World::pinstance = 0;

World::World()
{
    gravity.x = 0.0f;
    gravity.y = 0.0f;
    world= new b2World(gravity);
}

World::~World()
{
    //dtor
}

void World::Step(float DeltaTime){
    world->Step(DeltaTime*TIMESTEP, VELITER, POSITER);
}


World* World::Instance(){
    if(pinstance == 0){
        pinstance = new World();
    }
    return pinstance;
}

void World::Update(){

}

void World::Render(){

}

b2World* World::getWorld(){
    return world;
}
