#include "Enemy.h"
#include "EntityManager.h"
#include "Enemies/StateMachine/Revivir.h"
#include "Enemies/StateMachine/Vigilar.h"
#include "Enemies/Medico.h"

Revivir* Revivir::Instance()
{
  static Revivir instance;

  return &instance;
}

void Revivir::Enter(Enemy* enemigo){
    enemigo->resetTime();
    SoundMgr->playSonido("VocesRobots/Medico/reparando_medico");
}

void Revivir::Execute(Enemy* enemigo){
    //std::cout<<"Le revivo"<<std::endl;
    if(enemigo->getTiempo()>3){
        static_cast<Medico*>(enemigo)->revivir();
        enemigo->GetFSM()->RevertToPreviousState();
    }
}

void Revivir::Exit(Enemy* enemigo){

}
bool Revivir::OnMessage(Enemy* enemigo, const Mensaje& msg){

}
