#include "Patrullar.h"
#include "Vigilar.h"
#include "PedirAyuda.h"
#include "Investigar.h"
#include "Enemy.h"
#include "StateMachine/Mensaje.h"


Patrullar* Patrullar::Instance()
{
  static Patrullar instance;

  return &instance;
}

void Patrullar::Enter(Enemy* enemigo){

}

void Patrullar::Execute(Enemy* enemigo){

    enemigo->patrullar();

    if(enemigo->getDistanciaPlayer() < 3){
        if(enemigo->getTipo()== 2){
            enemigo->GetFSM()->ChangeState(PedirAyuda::Instance());
        }
    }

    /*if(enemigo->getPatrulla()->getInicial() == enemigo->getPPatrulla()){
        enemigo->resetTime();
        enemigo->GetFSM()->ChangeState(Vigilar::Instance());
    }*/


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
