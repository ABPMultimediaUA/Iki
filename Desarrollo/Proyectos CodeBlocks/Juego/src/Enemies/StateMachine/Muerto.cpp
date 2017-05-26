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
    enemigo->getBody()->SetActive(false);
    if(enemigo->GetFSM()->PreviousState() != Muerto::Instance()){
        if(!EntityMgr->hayEnemyAtacando()){
            SoundMgr->playMusica("Musica/musica_general");
            SoundMgr->transicionMusicas(3);
        }

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
    }

    enemigo->muerto();
}

void Muerto::Execute(Enemy* enemigo){
    if(enemigo->getVida()>0)
        enemigo->GetFSM()->ChangeState(Vigilar::Instance());
}

void Muerto::Exit(Enemy* enemigo){
    enemigo->getBody()->SetActive(true);
}
bool Muerto::OnMessage(Enemy* enemigo, const Mensaje& msg){

}
