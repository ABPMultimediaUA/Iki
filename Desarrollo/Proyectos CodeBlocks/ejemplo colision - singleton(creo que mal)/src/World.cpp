#include "World.h"
#include <Box2D/Box2D.h>
#include <MyContactListener.h>


World* World::pinstance= 0;

World::World()
{
    b2Vec2 gravity(0.0f, -10.0f);
    b2World *world= new b2World(gravity);
    MyContactListener colision;
/*ITimer* timer = device->getTimer();
    float32 timeStep = 1.0f / 250.0f;
    f32 TimeStamp = timer->getTime();
    f32 DeltaTime = timer->getTime() - TimeStamp;
*/

}

World::~World()
{
    //dtor
}

World* World::Instance(){
    if(pinstance == 0){
        pinstance= new World();
    }
    return pinstance;
}


void World::Step(float32 timeStep, int32 velocityIterations, int32 positionIterations){

}

void World::Update(){

}

void World::Render(){

}
