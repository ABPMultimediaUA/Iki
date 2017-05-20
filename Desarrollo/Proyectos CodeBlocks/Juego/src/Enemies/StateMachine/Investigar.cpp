#include "Enemies/StateMachine/Investigar.h"
#include "Enemies/StateMachine/Vigilar.h"
#include "Enemy.h"
#include "Enemies/StateMachine/Patrullar.h"
#include "Enemies/Guardia.h"
#include "Enemies/StateMachine/Escanear.h"
#include "Enemies/StateMachine/VolverALaPatrulla.h"
#include "Enemies/StateMachine/Atacar.h"

Investigar* Investigar::Instance()
{
  static Investigar instance;

  return &instance;
}

void Investigar::Enter(Enemy* enemigo){
    //std::cout<<"a investigar se ha dicho"<<std::endl;
    enemigo->crearPath(enemigo->getPosicionInteres());
    if(enemigo->GetFSM()->wasInState(*Atacar::Instance())){
        switch (enemigo->getTipo()){
            case 1:
                SoundMgr->playSonido("VocesRobots/Guardia/investigando");
            break;
            case 2:
                SoundMgr->playSonido("VocesRobots/Medico/investigando_medico");
            break;
            case 3:
                SoundMgr->playSonido("VocesRobots/Dron/beepinvestigar");
            break;
        }
    }
     std::cout<<"entra en investigarr"<<std::endl;
}

void Investigar::Execute(Enemy* enemigo){
    if(enemigo->getDistanciaPlayer()<15 && enemigo->isEnemySeeing(enemigo->getPosicionProta())){
        if(enemigo->isGuardia() && enemigo->GetFSM()->PreviousState() == Atacar::Instance()){
            enemigo->GetFSM()->ChangeState(Atacar::Instance());
        }else{
            enemigo->GetFSM()->ChangeState(Escanear::Instance());
        }
    }
    if(enemigo->getPosition() == enemigo->getPosicionInteres()){
        enemigo->GetFSM()->ChangeState(Vigilar::Instance());
    }
    static_cast<Guardia*>(enemigo)->investigar();

}

void Investigar::Exit(Enemy* enemigo){

    switch (enemigo->getTipo()){
        case 1:
            SoundMgr->soundStop("VocesRobots/Guardia/investigando");
        break;
        case 2:
            SoundMgr->soundStop("VocesRobots/Medico/investigando_medico");
        break;
        case 3:
            SoundMgr->soundStop("VocesRobots/Dron/beepinvestigar");
        break;
    }

}
bool Investigar::OnMessage(Enemy*, const Mensaje&){}
