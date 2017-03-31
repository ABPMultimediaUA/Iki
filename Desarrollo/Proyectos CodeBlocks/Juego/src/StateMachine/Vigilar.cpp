#include "Vigilar.h"
#include "Enemy.h"
#include "Patrullar.h"
#include "Escanear.h"
#include "Mensaje.h"
#include "Investigar.h"
#include "VolverALaPatrulla.h"

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
    if(enemigo->getDistanciaPlayer() < 20){
        if(enemigo->isEnemySeeing(enemigo->getPosicionProta()))
        //std::cout<<"Escaneando..."<<std::endl;
            enemigo->GetFSM()->ChangeState(Escanear::Instance());
    }
    if(enemigo->getTiempo() > 6){
        //std::cout<<"Patrullando..."<<std::endl;
        if(enemigo->GetFSM()->PreviousState() == Investigar::Instance()){
            enemigo->GetFSM()->ChangeState(VolverALaPatrulla::Instance());
        }
        else
        enemigo->GetFSM()->ChangeState(Patrullar::Instance());
    }

   /* if(enemigo->isEnemySeeing(enemigo->getPosicionProta())){
        Structs::TColor color = {0,0,0,0};
        enemigo->cambiarColor(color);
    }
    else{
        Structs::TColor color = {0,0,0,255};
        enemigo->cambiarColor(color);
    }
    if(enemigo->getTiempo() > 6){
        enemigo->resetTime();
    }*/
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
