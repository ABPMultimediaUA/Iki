#include "Trigger_Ruido.h"
#include "Fachada/GraphicsFacade.h"
#include "Player.h"

#include <iostream>

Trigger_Ruido::Trigger_Ruido()
{
    //ctor
    SetInactive();
}

Trigger_Ruido::~Trigger_Ruido()
{
    //dtor
}

void Trigger_Ruido::Try(GameEntity* ent)
{
    if (ent->isPlayer()){
        posicion = ent->getPosition();
        speed = static_cast<Player*>(ent)->getSpeed();
    }

    std::cout << "ARREGLA ESTO HIJODEPUTA" << std::endl;

    if (isActive() && !ent->isPlayer() && isTouchingTrigger(ent->getPosition(), ent->getRadio())){

        if (speed == 1){
            // se mueve lento y me detectan
            std::cout << "me ven despasico" << std::endl;
        }else{
            // static_cast<Enemigo*>(ent)->Sospechar();
            std::cout << "me ven MUCHO" << std::endl;
        }
    }
    else
        std::cout << "    " << std::endl;

}

void Trigger_Ruido::Update()
{

}
