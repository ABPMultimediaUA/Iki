#include "Vigilar.h"
#include "Enemy.h"
#include "Patrullar.h"

Vigilar* Vigilar::Instance()
{
  static Vigilar instance;

  return &instance;
}

void Vigilar::Enter(Enemy* enemigo){

}

void Vigilar::Execute(Enemy* enemigo){
    enemigo->vigilar();
    if(enemigo->getTiempo() > 5){
        enemigo->resetTime();
        enemigo->GetFSM()->ChangeState(Patrullar::Instance());
    }

}

void Vigilar::Exit(Enemy* enemigo){}
bool Vigilar::OnMessage(Enemy*, const Mensaje&){}
