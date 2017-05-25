#include "Enemies/StateMachine/Escanear.h"
#include "Enemy.h"

#include "Enemies/StateMachine/Patrullar.h"
#include "Enemies/StateMachine/PedirAyuda.h"
#include "Enemies/StateMachine/Atacar.h"
#include "Enemies/StateMachine/Alarma.h"
#include "Enemies/StateMachine/Investigar.h"
#include "Enemies/StateMachine/VolverALaPatrulla.h"



Escanear* Escanear::Instance()
{
  static Escanear instance;

  return &instance;
}

void Escanear::Enter(Enemy* enemigo){

    //enemigo->activeHoloScan(true);
    enemigo->scanTimerToZero();
    //enemigo->scanRotation();
    enemigo->resetTime();

    switch (enemigo->getTipo()){
        case 1:
            SoundMgr->playSonido("VocesRobots/Guardia/escaneando");
        break;
        case 2:
            SoundMgr->playSonido("VocesRobots/Medico/escaneando_medico");
        break;
        case 3:
            SoundMgr->playSonido("VocesRobots/Dron/beepveralgo");
        break;
    }
}

void Escanear::Execute(Enemy* enemigo){
    enemigo->escanear();

    if(enemigo->getTiempo()>2){
        //std::cout<<"ID: "<< enemigo->ID()<<"Sospecha: "<<enemigo->getSospecha()<<std::endl;
        if(enemigo->getSospecha()>=95){
            ///COMBATEEE
            switch(enemigo->getTipo()){
            case 1:
                enemigo->GetFSM()->ChangeState(Atacar::Instance());
                break;
            case 2:
                enemigo->GetFSM()->ChangeState(PedirAyuda::Instance());
                break;
            case 3:
                enemigo->GetFSM()->ChangeState(Alarma::Instance());
                break;
            default:
                break;
            }
        }
        else if( enemigo->getSospecha() < 55){
            enemigo->calcularAngulo(enemigo->getPPatrulla()->getPunto());
            if(enemigo->GetFSM()->wasInState(*Investigar::Instance()))
                enemigo->GetFSM()->ChangeState(VolverALaPatrulla::Instance());
            else
                enemigo->GetFSM()->ChangeState(Patrullar::Instance());
        }
        else if(enemigo->getSospecha() >= 55){
            enemigo->setPosicionInteres(enemigo->getPosicionProta());
            enemigo->GetFSM()->ChangeState(Investigar::Instance());
        }
    }
}

void Escanear::Exit(Enemy* enemigo){

    enemigo->activeHoloScan(false);
    switch (enemigo->getTipo()){
        case 1:
            SoundMgr->soundStop("VocesRobots/Guardia/escaneando");
        break;
        case 2:
            SoundMgr->soundStop("VocesRobots/Medico/escaneando_medico");
        break;
        case 3:
            SoundMgr->soundStop("VocesRobots/Dron/beepveralgo");
        break;
    }
}
bool Escanear::OnMessage(Enemy*, const Mensaje&){}
