#include "Trigger_PuertaNivel.h"
#include "Player.h"
#include "PhisicsWorld.h"
#include "EntityManager.h"

Trigger_PuertaNivel::Trigger_PuertaNivel(float x, float z, float r)
{

}

Trigger_PuertaNivel::~Trigger_PuertaNivel()
{
    //dtor
}


void Trigger_PuertaNivel::Try(GameEntity* ent)
{
    if (isActive() && ent->isPlayer() && isTouchingTrigger(ent->getPosition(), ent->getRadio())){
        if (!EntityMgr->hayEnemyEscaneandoOAtacando()){
            static_cast<Player*>(ent)->setNivelFinished(true);
        }

    }
}

void Trigger_PuertaNivel::Update()
{

}
