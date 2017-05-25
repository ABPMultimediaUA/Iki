#include "Enemies/StateMachine/Atacar.h"
#include "Enemies/StateMachine/Investigar.h"
#include "Enemy.h"
#include "Enemies/Guardia.h"


Atacar* Atacar::Instance()
{
  static Atacar instance;

  return &instance;
}

void Atacar::Enter(Enemy* enemigo){

    if(enemigo->GetFSM()->PreviousState() != Investigar::Instance()){
        switch (enemigo->getTipo()){
            case 1:
                SoundMgr->playSonido("VocesRobots/Guardia/protocolo_combate_guardia");
            break;
            case 2:

            break;
            case 3:

            break;
        }
    }
    //std::cout<<"entra en atacar"<<std::endl;
    //Structs::TColor color = {0,255,0,0};
    //enemigo->cambiarColor(color);
}

void Atacar::Execute(Enemy* enemigo){

    //std::cout<<"holi"<<std::endl;
    SoundMgr->transicionMusicas(2);
    enemigo->showExcMark(true);
    /*if(!enemigo->isEnemySeeing(enemigo->getPosicionProta())){
        enemigo->setPosicionInteres(enemigo->getPosicionProta());
    }*/
    if(enemigo->getDistanciaPlayer()> 5 && !static_cast<Guardia*>(enemigo)->getAtacando()){
        //if(enemigo->isPathObstructured(enemigo->getPosicionProta()))
        static_cast<Guardia*>(enemigo)->perseguir();
    }
    else
        static_cast<Guardia*>(enemigo)->ataque();

}

void Atacar::Exit(Enemy* enemigo){

    std::cout<<"holi"<<std::endl;
    enemigo->showExcMark(false);
    //SoundMgr->playMusica("Musica/musica_general");
    //SoundMgr->transicionMusicas(3);
    /*switch (enemigo->getTipo()){
        case 1:
            SoundMgr->soundStop("VocesRobots/Guardia/protocolo_combate");
        break;
        case 2:

        break;
        case 3:

        break;
    }*/
}
bool Atacar::OnMessage(Enemy*, const Mensaje&){}
