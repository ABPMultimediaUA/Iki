#include "Trigger_Ruido.h"
#include "Fachada/GraphicsFacade.h"

Trigger_Ruido::Trigger_Ruido()
{
    //ctor
    SetActive();
}

Trigger_Ruido::~Trigger_Ruido()
{
    //dtor
}

void Trigger_Ruido::Try(GameEntity* ent)
{
    if (ent->isPlayer())
        posicion = ent->getPosition();

    if (isActive() && !ent->isPlayer() && isTouchingTrigger(ent->getPosition(), ent->getRadio())){

        if(MyEventReceiver::getInstance().isKeyDown(KEY_KEY_X)){
            // se mueve lento y me detectan
        }else{
            // static_cast<Enemigo*>(ent)->Sospechar();
        }

    }

}

void Trigger_Ruido::Update()
{

}
