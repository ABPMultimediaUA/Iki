#include "Trigger_PuertaNivel.h"
#include "Player.h"
#include "PhisicsWorld.h"

Trigger_PuertaNivel::Trigger_PuertaNivel()
{

}

Trigger_PuertaNivel::~Trigger_PuertaNivel()
{
    //dtor
}


void Trigger_PuertaNivel::Try(GameEntity* ent)
{

    if (isActive() && ent->isPlayer() && isTouchingTrigger(ent->getPosition(), ent->getRadio())){

        static_cast<Player*>(ent)->setNivelFinished(true);

    }

}

void Trigger_PuertaNivel::Update()
{

}
