#include "Trigger_Aceite.h"

#include "Player.h"


Trigger_Aceite::Trigger_Aceite()
{

}

Trigger_Aceite::~Trigger_Aceite()
{
    //dtor
}

void Trigger_Aceite::Try(GameEntity* ent)
{
    if (isActive() && ent->isPlayer() && isTouchingTrigger(ent->getPosition(), ent->getRadio())){
        static_cast<Player*>(ent)->subirVelocidad();
        Deactivate();
        aniMesh->setVisible(false);
    }
}

void Trigger_Aceite::Update()
{

}
