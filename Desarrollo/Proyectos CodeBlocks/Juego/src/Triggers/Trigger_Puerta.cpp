#include "Trigger_Puerta.h"
#include "GameEntity.h"

Trigger_Puerta::Trigger_Puerta()
{

}

Trigger_Puerta::~Trigger_Puerta()
{
    //dtor
}

void Trigger_Puerta::Try(GameEntity* ent)
{
    if (isActive() && ent->isPlayer() && isTouchingTrigger(ent->getPosition(), ent->getRadio())){
       aniMesh->setVisible(false);
       body->SetActive(false);
    }
    else{
        aniMesh->setVisible(true);
        body->SetActive(true);
    }
}

void Trigger_Puerta::Update()
{

}
