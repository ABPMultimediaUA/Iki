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
    enemigo->escuchar();
    if(enemigo->isEnemySeeing(enemigo->getPosicionProta())){
        enemigo->GetFSM()->ChangeState(Escanear::Instance());
    }else{

        Player* play = static_cast<Player*>(EntityMgr->getEntityByID(0));

        if(play->getSpeed() == 2){
            enemigo->subirSospecha();
            if (enemigo->getSospecha() > 150){
                enemigo->resetSospecha();
                enemigo->setPosicionInteres(enemigo->getPosicionProta());
                enemigo->GetFSM()->ChangeState(Investigar::Instance());
            }
        }else{
            if (enemigo->getTiempo() > 3){
                enemigo->calcularAngulo(enemigo->getPPatrulla()->getPunto());
                enemigo->GetFSM()->ChangeState(Patrullar::Instance());
            }
        }
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
