#include "PhisicsWorld.h"
#include  "Fachada/GraphicsFacade.h"

#define VELITER 10
#define POSITER 10
#define TIMESTEP 1.0f / 250.0f

PhisicsWorld::PhisicsWorld()
{
    gravity.x = 0.0f;
    gravity.y = 0.0f;

    TimeStamp = GraphicsFacade::getInstance().getTime();
    DeltaTime = 0;

    phisics_world = new b2World(gravity);
}

PhisicsWorld::~PhisicsWorld()
{
    //dtor
}

void PhisicsWorld::Step(){
    DeltaTime = GraphicsFacade::getInstance().getTime() - TimeStamp;
    TimeStamp = GraphicsFacade::getInstance().getTime();
    phisics_world->Step(DeltaTime * TIMESTEP, VELITER, POSITER);
}
