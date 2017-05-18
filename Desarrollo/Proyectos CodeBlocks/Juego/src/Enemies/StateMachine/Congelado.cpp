#include "Enemies/StateMachine/Congelado.h"
#include "Enemy.h"

Congelado* Congelado::Instance()
{
  static Congelado instance;

  return &instance;
}

void Congelado::Enter(Enemy* enemigo){
    enemigo->activeAtaque(false);
}

void Congelado::Execute(Enemy* enemigo){
    //std::cout<<"holi"<<std::endl;
    if(enemigo->getTiempo() > 4){
            enemigo->GetFSM()->RevertToPreviousState();
    }
}

void Congelado::Exit(Enemy* enemigo){}
