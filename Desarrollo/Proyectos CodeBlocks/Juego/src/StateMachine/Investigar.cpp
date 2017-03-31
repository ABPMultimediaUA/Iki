#include "Investigar.h"
#include "Vigilar.h"
#include "Enemy.h"
#include "Patrullar.h"
#include "Guardia.h"
#include "Escanear.h"
#include "VolverALaPatrulla.h"

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
    if(enemigo->getDistanciaPlayer()<10){
        if(enemigo->isEnemySeeing(enemigo->getPosicionProta()))
            //static_cast<Guardia*>(enemigo)->atacar();
            enemigo->GetFSM()->ChangeState(Escanear::Instance());
    }
    if(enemigo->getPosition() == enemigo->getPosicionInteres()){
            enemigo->GetFSM()->ChangeState(Vigilar::Instance());
    }
    static_cast<Guardia*>(enemigo)->investigar();

}

void Investigar::Exit(Enemy* enemigo){

}
bool Investigar::OnMessage(Enemy*, const Mensaje&){}
