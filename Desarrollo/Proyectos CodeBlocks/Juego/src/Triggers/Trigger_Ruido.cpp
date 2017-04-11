#include "Trigger_Ruido.h"
#include "Fachada/GraphicsFacade.h"
#include "Player.h"
#include "Enemy.h"

#include "Escuchar.h"
#include "Patrullar.h"
#include "Vigilar.h"
#include "Investigar.h"

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
    if (respawn)
        if (isActive() && !ent->isPlayer() && isTouchingTrigger(ent->getPosition(), ent->getRadio())){
            //show interrogante
            if (speed == 2){
                Enemy* enemigo = static_cast<Enemy*>(ent);

                if (   enemigo->GetFSM()->CurrentState() == Patrullar::Instance()
                    || enemigo->GetFSM()->CurrentState() == Vigilar::Instance()){

                    enemigo->GetFSM()->ChangeState(Escuchar::Instance());
                    respawn = false;
                }
            }
        }
}

void Trigger_Ruido::Update()
{
    GameEntity* ent = EntityMgr->getEntityByID(0);
    posicion = ent->getPosition();
    speed = static_cast<Player*>(ent)->getSpeed();
}
