#include "Enemies/StateMachine/Vigilar.h"
#include "Enemy.h"
#include "Enemies/StateMachine/Patrullar.h"
#include "Enemies/StateMachine/Escanear.h"
#include "Enemies/StateMachine/Mensaje.h"
#include "Enemies/StateMachine/Investigar.h"
#include "Enemies/StateMachine/Atacar.h"
#include "Enemies/StateMachine/VolverALaPatrulla.h"
#include "Enemies/StateMachine/Muerto.h"


Vigilar* Vigilar::Instance()
{
  static Vigilar instance;

  return &instance;
}

void Vigilar::Enter(Enemy* enemigo){
    enemigo->resetTime();

    switch (enemigo->getTipo()){
        case 1:
            SoundMgr->playSonido("VocesRobots/Guardia/diagnostico_terreno");
        break;
        case 2:
            SoundMgr->playSonido("VocesRobots/Medico/diagnostico_terreno_medico");
        break;
        case 3:
            SoundMgr->playSonido("VocesRobots/Dron/beepvigilar");
        break;
    }
}

void Vigilar::Execute(Enemy* enemigo){
    enemigo->vigilar();
    if(enemigo->getDistanciaPlayer() < 30 && enemigo->isEnemySeeing(enemigo->getPosicionProta())){
        //std::cout<<"Escaneando..."<<std::endl;
        if(enemigo->GetFSM()->wasInState(*Investigar::Instance())){
            enemigo->GetFSM()->ChangeState(Atacar::Instance());
        }
        else{
            enemigo->GetFSM()->ChangeState(Escanear::Instance());
        }
    }
    if(enemigo->getTiempo() > 6){
            //if(enemigo->GetFSM()->PreviousState())
        if(enemigo->GetFSM()->wasInState(*Investigar::Instance()) || enemigo->GetFSM()->wasInState(*Muerto::Instance())){
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
            enemigo->GetFSM()->ChangeState(Investigar::Instance());
            return true;
        }
    }
    return false;
}
