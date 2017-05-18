#include "Escuchar.h"
#include "Enemy.h"
#include "Escanear.h"
#include "Investigar.h"
#include "Patrullar.h"

#include "EntityManager.h"
#include "Player.h"

Escuchar* Escuchar::Instance()
{
  static Escuchar instance;
  return &instance;
}

void Escuchar::Enter(Enemy* enemigo)
{
    enemigo->resetTime();
    if(enemigo->getTimeSinceLastSensed() > 5 && enemigo->getTimePlayerHasBeenOutOfView() > 10){
        enemigo->resetSospecha();
        enemigo->borrarMemoria();
    }
}

void Escuchar::Execute(Enemy* enemigo)
{
    if(enemigo->isEnemySeeing(enemigo->getPosicionProta()))
        enemigo->GetFSM()->ChangeState(Escanear::Instance());

    Player* play = static_cast<Player*>(EntityMgr->getEntityByID(0));

    if(play->getSpeed() == 2){
        enemigo->escuchar();
        std::cout<<"sospecha: "<<enemigo->getSospecha()<<std::endl;
    }

    if (enemigo->getSospecha() > 90){
  //std::cout << "sospechando tete" << std::endl;
        enemigo->setPosicionInteres(enemigo->getPosicionProta());
        enemigo->GetFSM()->ChangeState(Investigar::Instance());
    }

    if (enemigo->getTiempo() > 2.5){
        enemigo->calcularAngulo(enemigo->getPPatrulla()->getPunto());
        enemigo->GetFSM()->ChangeState(Patrullar::Instance());
    }
}

void Escuchar::Exit(Enemy* enemigo)
{
}

bool Escuchar::OnMessage(Enemy* enemigo, const Mensaje& msg)
{/*
    switch( msg.Msg )
    {
        case Msg_NeedHelp:
        {
            std::cout<<"recibo el mensajeee"<<std::endl;
            enemigo->GetFSM()->ChangeState(Investigar::Instance());
        }
    }*/
}
