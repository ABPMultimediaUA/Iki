#include "PhisicsWorld.h"

#define VELITER 10
#define POSITER 10
#define TIMESTEP 1.0f / 250.0f

PhisicsWorld::PhisicsWorld()
{
    gravity.x = 0.0f;
    gravity.y = 0.0f;
    phisics_world = new b2World(gravity);
}

PhisicsWorld::~PhisicsWorld()
{
    //dtor
}

void PhisicsWorld::Step(float DeltaTime){
    phisics_world->Step(DeltaTime*TIMESTEP, VELITER, POSITER);
}
