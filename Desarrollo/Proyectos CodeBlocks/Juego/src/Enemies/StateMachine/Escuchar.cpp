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
        std::cout << "te he visto tete" << std::endl;
    }

    else if (enemigo->getSospecha() > 90){
        enemigo->setPosicionInteres(enemigo->getPosicionProta());
            enemigo->GetFSM()->ChangeState(Investigar::Instance());
    }
    //si ha pasado mas de 2,5seg y aun no ha subido la sospecha a mas de 90, sigue su camino
    else if (enemigo->getTiempo() > 2.5){
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
