#include "Enemies/StateMachine/Alarma.h"
#include "Enemy.h"
#include "Enemies/StateMachine/Patrullar.h"
#include "Enemies/StateMachine/Escanear.h"
#include "Enemies/StateMachine/Mensaje.h"
#include "EntityManager.h"
#include "PatrolRoute.h"
#include "Enemies/StateMachine/Muerto.h"

Alarma* Alarma::Instance()
{
  static Alarma instance;

  return &instance;
}

void Alarma::Enter(Enemy* enemigo){
    enemigo->resetTime();
}

void Alarma::Execute(Enemy* enemigo){
    if(enemigo->getTiempo() > 3)
        enemigo->GetFSM()->ChangeState(Muerto::Instance());
}

void Alarma::Exit(Enemy* enemigo){
    EntityMgr->crearGuardia(enemigo->getPatrulla());
    PatrolRoute* ruta = enemigo->getPatrulla();
    ruta->setInicial(enemigo->getPatrulla()->getInicial()->getNext());
    EntityMgr->crearGuardia(ruta);
}
bool Alarma::OnMessage(Enemy* enemigo, const Mensaje& msg){

}
