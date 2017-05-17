#include "Trigger_PuertaNivel.h"
#include "Player.h"
#include "PhisicsWorld.h"

Trigger_PuertaNivel::Trigger_PuertaNivel(float x, float z, float r)
{
    //b2body
    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;
    bodyDef.position.Set(x,z);
    body = PhisicsWorld::getInstance()->getWorld()->CreateBody(&bodyDef);

    b2PolygonShape bodyShape;
    if (r==90)                  bodyShape.SetAsBox(5.f,1.f);
    else                        bodyShape.SetAsBox(1.f,5.f);
    body->CreateFixture(&bodyShape, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &bodyShape;
    body->CreateFixture(&fixtureDef);
}

Trigger_PuertaNivel::~Trigger_PuertaNivel()
{
    //dtor
}


void Trigger_PuertaNivel::Try(GameEntity* ent)
{
    if (isActive() && ent->isPlayer() && isTouchingTrigger(ent->getPosition(), ent->getRadio())){

        std::cout << "fin del nivel" << std::endl;

    }

}

void Trigger_PuertaNivel::Update()
{

}
