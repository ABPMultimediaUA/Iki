#include "Vigilar.h"
#include "Enemy.h"
#include "Patrullar.h"
#include "Escanear.h"
#include "Mensaje.h"
#include "Investigar.h"

Vigilar* Vigilar::Instance()
{
  static Vigilar instance;

  return &instance;
}

void Vigilar::Enter(Enemy* enemigo){
    enemigo->resetTime();
}

void Vigilar::Execute(Enemy* enemigo){
    enemigo->vigilar();
    if(enemigo->getDistanciaPlayer() < 10){
        if(enemigo->isEnemySeeing(enemigo->getPosicionProta()))
        //std::cout<<"Escaneando..."<<std::endl;
            enemigo->GetFSM()->ChangeState(Escanear::Instance());
    }
    if(enemigo->getTiempo() > 5){
        //std::cout<<"Patrullando..."<<std::endl;
        enemigo->GetFSM()->ChangeState(Patrullar::Instance());
    }

}

void Vigilar::Exit(Enemy* enemigo){
    //enemigo->setPPatrulla(enemigo->getPPatrulla()->getNext());
}
bool Vigilar::OnMessage(Enemy* enemigo, const Mensaje& msg){
    switch( msg.Msg )
    {
        case Msg_NeedHelp:
        {
            std::cout<<"recibo el mensajeee"<<std::endl;
            enemigo->GetFSM()->ChangeState(Investigar::Instance());
        }
    }
}
