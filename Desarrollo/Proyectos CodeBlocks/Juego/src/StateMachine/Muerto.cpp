#include "Enemy.h"
#include "EntityManager.h"
#include "Enemies/StateMachine/Muerto.h"

Muerto* Muerto::Instance()
{
  static Muerto instance;

  return &instance;
}

void Muerto::Enter(Enemy* enemigo){

}

void Muerto::Execute(Enemy* enemigo){
 ///MATAR ENEMIGO
    enemigo->muerto();
}

void Muerto::Exit(Enemy* enemigo){

}
bool Muerto::OnMessage(Enemy* enemigo, const Mensaje& msg){

}
