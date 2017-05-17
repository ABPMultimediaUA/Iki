#include "Enemy.h"
#include "EntityManager.h"
#include "Enemies/StateMachine/Muerto.h"
#include "Enemies/StateMachine/Vigilar.h"

Muerto* Muerto::Instance()
{
  static Muerto instance;

  return &instance;
}

void Muerto::Enter(Enemy* enemigo){
    ///MATAR ENEMIGO

    switch (enemigo->getTipo()){
        case 1:
            SoundMgr->playSonido("AccionesRobots/muertedron");
        break;
        case 2:
            SoundMgr->playSonido("AccionesRobots/muertemedico");
        break;
        case 3:
            SoundMgr->playSonido("AccionesRobots/muertedron");
        break;
    }

    enemigo->muerto();
}

void Muerto::Execute(Enemy* enemigo){
    if(enemigo->getVida()>0)
        enemigo->GetFSM()->ChangeState(Vigilar::Instance());
}

void Muerto::Exit(Enemy* enemigo){

}
bool Muerto::OnMessage(Enemy* enemigo, const Mensaje& msg){

}
