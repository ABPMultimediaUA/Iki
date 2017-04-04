#include "Trigger_Ruido.h"
#include "Fachada/GraphicsFacade.h"
#include "Player.h"
#include "Enemy.h"

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

    if (isActive() && !ent->isPlayer() && isTouchingTrigger(ent->getPosition(), ent->getRadio())){

        if (speed == 1){
            // se mueve lento y me detectan

        }else{
            static_cast<Enemy*>(ent)->calcularAngulo(this->posicion);
            //static_cast<Enemy*>(ent)->escanear();
        }
    }
    else{
        //std::cout << "    " << std::endl;
    }

}

void Trigger_Ruido::Update()
{

}
