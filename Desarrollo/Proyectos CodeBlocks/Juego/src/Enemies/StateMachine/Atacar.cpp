#include "Enemies/StateMachine/Atacar.h"
#include "Enemy.h"
#include "Enemies/Guardia.h"


Atacar* Atacar::Instance()
{
  static Atacar instance;

  return &instance;
}

void Atacar::Enter(Enemy* enemigo){
}

void Atacar::Execute(Enemy* enemigo){
    Structs::TColor color = {0,255,0,0};
    enemigo->cambiarColor(color);

    if(enemigo->getDistanciaPlayer()> 5 && !static_cast<Guardia*>(enemigo)->getAtacando()){
        //if(enemigo->isPathObstructured(enemigo->getPosicionProta()))
        static_cast<Guardia*>(enemigo)->perseguir();
    }
    else
        static_cast<Guardia*>(enemigo)->ataque();

}

void Atacar::Exit(Enemy* enemigo){}
bool Atacar::OnMessage(Enemy*, const Mensaje&){}
