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
    if (isActive() && isTouchingTrigger(ent->getPosition(), ent->getRadio())){
        //Open la puerta
        //std::cout << "ejeje " << std::endl;
    }
    else{
        //Close la puerta
        //std::cout << "   " << std::endl;
    }
}

void Trigger_Puerta::Update()
{

}

void Trigger_Puerta::Render()
{

}
