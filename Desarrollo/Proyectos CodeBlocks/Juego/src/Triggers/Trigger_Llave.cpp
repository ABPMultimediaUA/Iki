#include "Trigger_Llave.h"
#include "Player.h"


Trigger_Llave::Trigger_Llave()
{
    //ctor
    SetActive();
}

Trigger_Llave::~Trigger_Llave()
{
    //dtor
}

void Trigger_Llave::Try(GameEntity* ent)
{
    if (isActive() && ent->isPlayer() && isTouchingTrigger(ent->getPosition(), ent->getRadio())){
        static_cast<Player*>(ent)->CogerLlave();
        Deactivate();
        //std::cout << ">>>> si cojo " << std::endl;
        aniMesh->setVisible(false);
    }
}

void Trigger_Llave::Update()
{

}

void Trigger_Llave::Render()
{

}
