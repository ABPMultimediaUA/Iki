#include "Trigger_Ruido.h"

Trigger_Ruido::Trigger_Ruido()
{
    //ctor
}

Trigger_Ruido::~Trigger_Ruido()
{
    //dtor
}

void Trigger_Ruido::Try(GameEntity* ent)
{
    if (isActive() && !ent->isPlayer() && isTouchingTrigger(ent->getPosition(), ent->getRadio())){
       // static_cast<Enemigo*>(ent)->Sospechar();
    }
}

void Trigger_Ruido::Update()
{

}
