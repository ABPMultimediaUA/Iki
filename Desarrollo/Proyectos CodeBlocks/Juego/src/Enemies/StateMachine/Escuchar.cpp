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
    tiempo = enemigo->getTiempo();
}

void Escuchar::Execute(Enemy* enemigo)
{
    if(enemigo->isEnemySeeing(enemigo->getPosicionProta()))
        enemigo->GetFSM()->ChangeState(Escanear::Instance());

    Player* play = static_cast<Player*>(EntityMgr->getEntityByID(0));

    if(play->getSpeed() == 2){
        enemigo->escuchar();
        enemigo->subirSospecha();
        if (enemigo->getSospecha() > 150){
            enemigo->setPosicionInteres(enemigo->getPosicionProta());
            enemigo->GetFSM()->ChangeState(Investigar::Instance());
        }
        if(play->getPosition().Distance(enemigo->getPosition()) >= 20){
            if (enemigo->getSospecha() > 100){
                enemigo->setPosicionInteres(enemigo->getPosicionProta());
                enemigo->GetFSM()->ChangeState(Investigar::Instance());
            }
        }else{
            std::cout << "he sido yo " << std::endl;
            enemigo->calcularAngulo(enemigo->getPPatrulla()->getPunto());
            enemigo->GetFSM()->ChangeState(Patrullar::Instance());
        }
    }else{
        if (enemigo->getTiempo() - tiempo > 3){
            enemigo->calcularAngulo(enemigo->getPPatrulla()->getPunto());
            enemigo->GetFSM()->ChangeState(Patrullar::Instance());
        }
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
