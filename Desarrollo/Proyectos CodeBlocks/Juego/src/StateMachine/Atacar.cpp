#include "Atacar.h"
#include "Enemy.h"
#include "Guardia.h"


Atacar* Atacar::Instance()
{
  static Atacar instance;

  return &instance;
}

void Atacar::Enter(Enemy* enemigo){
}

void Atacar::Execute(Enemy* enemigo){
    static_cast<Guardia*>(enemigo)->atacar();
}

void Atacar::Exit(Enemy* enemigo){}
bool Atacar::OnMessage(Enemy*, const Mensaje&){}
