#include "Trigger_Municion.h"
#include "GameEntity.h"
#include "Player.h"

Trigger_Municion::Trigger_Municion()
{
    //ctor
}

Trigger_Municion::~Trigger_Municion()
{
    //dtor
}

#include <iostream>

void Trigger_Municion::Try(GameEntity* ent)
{
    if (isActive() && ent->isPlayer() && isTouchingTrigger(ent->getPosition(), ent->getRadio())){
        static_cast<Player*>(ent)->CogerMunicion();
        Deactivate();
        std::cout << "lo cojo" << std::endl;
        //Desvisualizar body
    }
}

void Trigger_Municion::Update()
{

}

void Trigger_Municion::Render()
{

}
