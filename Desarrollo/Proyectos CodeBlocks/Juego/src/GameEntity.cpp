#include "GameEntity.h"
#include "PhisicsWorld.h"

GameEntity::GameEntity()
{

}

GameEntity::~GameEntity()
{

}

void GameEntity::setBody(b2BodyDef bodyDef)
{
    body = PhisicsWorld::getInstance()->getWorld()->CreateBody(&bodyDef);
}

