#include "Enemies/StateMachine/Patrullar.h"
#include "Enemies/StateMachine/Vigilar.h"
#include "Enemies/StateMachine/PedirAyuda.h"
#include "Enemies/StateMachine/Investigar.h"
#include "Enemies/StateMachine/Escanear.h"
#include "Enemy.h"
#include "Enemies/StateMachine/Mensaje.h"


Patrullar* Patrullar::Instance()
{
  static Patrullar instance;

  return &instance;
}

void Patrullar::Enter(Enemy* enemigo){
}

void Patrullar::Execute(Enemy* enemigo){

    enemigo->patrullar();

    if(enemigo->getDistanciaPlayer() < 5){
        //std::cout<<"Escaneando..."<<std::endl;
        if(enemigo->isEnemySeeing(enemigo->getPosicionProta())){
            std::cout<<"Te he visto!..."<<std::endl;
            enemigo->GetFSM()->ChangeState(Escanear::Instance());
        }
    }

    if(enemigo->getPatrulla()->getInicial()->getNext()->getPunto() == enemigo->getPosition()){
        //std::cout<<"Vigilando..."<<std::endl;
        enemigo->GetFSM()->ChangeState(Vigilar::Instance());
    }


}

void Patrullar::Exit(Enemy* enemigo){}
bool Patrullar::OnMessage(Enemy* enemigo, const Mensaje& msg){
    switch( msg.Msg )
    {
        case Msg_NeedHelp:
        {
            std::cout<<"recibo el mensajeee"<<std::endl;
            enemigo->GetFSM()->ChangeState(Investigar::Instance());
        }
    }
}
