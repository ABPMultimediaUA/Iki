#include "Enemies/StateMachine/Huir.h"
#include "Enemy.h"
#include "Enemies/Medico.h"



Huir* Huir::Instance()
{
  static Huir instance;
  return &instance;
}

void Huir::Enter(Enemy* enemigo){
    enemigo->crearPath(static_cast<Medico*>(enemigo)->getPosHuida());
}

void Huir::Execute(Enemy* enemigo){
    static_cast<Medico*>(enemigo)->huir();
}

void Huir::Exit(Enemy* enemigo){}
bool Huir::OnMessage(Enemy*, const Mensaje&){}
