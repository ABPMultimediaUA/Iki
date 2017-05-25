#include "Enemies/StateMachine/VolverALaPatrulla.h"
#include "Enemy.h"
#include "Enemies/StateMachine/Patrullar.h"
#include "Enemies/StateMachine/Escanear.h"
#include "Enemies/StateMachine/Mensaje.h"


VolverALaPatrulla* VolverALaPatrulla::Instance()
{
  static VolverALaPatrulla instance;

  return &instance;
}

void VolverALaPatrulla::Enter(Enemy* enemigo){
    //std::cout<<"voviendo a la patrulla"<<std::endl;
    enemigo->crearPath(enemigo->getPPatrulla()->getPunto());
    SoundMgr->playMusica("Musica/musica_general");

    switch (enemigo->getTipo()){
        case 1:
            SoundMgr->playSonido("VocesRobots/Guardia/area_despejada_guardia");
        break;
        case 2:
            SoundMgr->playSonido("VocesRobots/Medico/area_despejada_medico");
        break;
        case 3:
            SoundMgr->playSonido("VocesRobots/Dron/beepaliviado");
        break;
    }
}

void VolverALaPatrulla::Execute(Enemy* enemigo){
    enemigo->volverALaPatrulla();
    SoundMgr->transicionMusicas(3);
    if(enemigo->getDistanciaPlayer() < 25 && enemigo->isEnemySeeing(enemigo->getPosicionProta())){
            enemigo->GetFSM()->ChangeState(Escanear::Instance());
    }
    if(enemigo->getPosition() == enemigo->getPPatrulla()->getPunto()){
        enemigo->GetFSM()->ChangeState(Patrullar::Instance());
    }

}

void VolverALaPatrulla::Exit(Enemy* enemigo){
}
bool VolverALaPatrulla::OnMessage(Enemy* enemigo, const Mensaje& msg){

}
