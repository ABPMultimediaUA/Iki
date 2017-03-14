#include "Trigger_Puerta.h"
#include "GameEntity.h"
#include <iostream>

Trigger_Puerta::Trigger_Puerta()
{
    //ctor
    SetActive();
}

Trigger_Puerta::~Trigger_Puerta()
{
    //dtor
}

void Trigger_Puerta::Try(GameEntity* ent)
{
    if (isActive() && ent->isPlayer() && isTouchingTrigger(ent->getPosition(), ent->getRadio())){
        //Open la puerta
        //std::cout << " abierta " << std::endl;
       aniMesh->setVisible(false);
       body->SetActive(false);
    }
    else{
        //Close la puerta
        //std::cout << " cerrada " << std::endl;
        aniMesh->setVisible(true);
        body->SetActive(true);
    }
}

void Trigger_Puerta::Update()
{

}

void Trigger_Puerta::Render()
{

}
