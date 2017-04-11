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
}

void Escuchar::Execute(Enemy* enemigo)
{
    if(enemigo->isEnemySeeing(enemigo->getPosicionProta()))
        enemigo->GetFSM()->ChangeState(Escanear::Instance());

    Player* play = static_cast<Player*>(EntityMgr->getEntityByID(0));

    if(play->getSpeed() == 2){
        enemigo->escuchar();
        enemigo->subirSospecha();
    }

    if (enemigo->getSospecha() > 80){
  //std::cout << "sospechando tete" << std::endl;
    //    enemigo->setPosicionInteres(enemigo->getPosicionProta());
      //  enemigo->GetFSM()->ChangeState(Investigar::Instance());
    }

    if (enemigo->getTiempo() > 2.5){
        enemigo->calcularAngulo(enemigo->getPPatrulla()->getPunto());
        enemigo->GetFSM()->ChangeState(Patrullar::Instance());
    }
}

void Escuchar::Exit(Enemy* enemigo)
{
    enemigo->resetSospecha();
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
