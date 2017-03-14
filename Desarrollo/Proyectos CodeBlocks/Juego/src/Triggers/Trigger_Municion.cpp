#include "Trigger_Municion.h"
#include "Player.h"


Trigger_Municion::Trigger_Municion()
{
    //ctor
    SetActive();
}

Trigger_Municion::~Trigger_Municion()
{
    //dtor
}

void Trigger_Municion::Try(GameEntity* ent)
{
    if (isActive() && ent->isPlayer() && isTouchingTrigger(ent->getPosition(), ent->getRadio())){
        static_cast<Player*>(ent)->CogerMunicion();
        Deactivate();
        //std::cout << ">>>> si cojo " << std::endl;
        aniMesh->setVisible(false);
    }
}

void Trigger_Municion::Update()
{

}

void Trigger_Municion::Render()
{

}
