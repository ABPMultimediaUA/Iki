#include "Investigar.h"
#include "Vigilar.h"
#include "Enemy.h"
#include "Patrullar.h"
#include "Guardia.h"

Investigar* Investigar::Instance()
{
  static Investigar instance;

  return &instance;
}

void Investigar::Enter(Enemy* enemigo){
    std::cout<<"a investigar se ha dicho"<<std::endl;
    enemigo->crearPath(enemigo->getPosicionInteres());
}

void Investigar::Execute(Enemy* enemigo){
    static_cast<Guardia*>(enemigo)->investigar();
}

void Investigar::Exit(Enemy* enemigo){}
bool Investigar::OnMessage(Enemy*, const Mensaje&){}
