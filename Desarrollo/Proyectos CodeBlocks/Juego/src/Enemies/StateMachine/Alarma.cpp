#include "Enemies/StateMachine/Alarma.h"
#include "Enemy.h"
#include "Enemies/StateMachine/Patrullar.h"
#include "Enemies/StateMachine/Escanear.h"
#include "Enemies/StateMachine/Mensaje.h"
#include "EntityManager.h"
#include "PatrolRoute.h"
#include "Enemies/StateMachine/Muerto.h"
#include "Enemies/StateMachine/Investigar.h"

Alarma* Alarma::Instance()
{
  static Alarma instance;

  return &instance;
}

void Alarma::Enter(Enemy* enemigo){
    enemigo->resetTime();
    SoundMgr->playSonido("AccionesRobots/alarma_sintetizada");
    Structs::TColor color = {0,255,0,0};
    enemigo->cambiarColor(color);
}

void Alarma::Execute(Enemy* enemigo){
    if(enemigo->getTiempo() > 3){
        SoundMgr->soundStop("AccionesRobots/alarma_sintetizada");
        SoundMgr->playSonido("AccionesRobots/capsulas_aterrizando");
        enemigo->GetFSM()->ChangeState(Muerto::Instance());
    }
}

void Alarma::Exit(Enemy* enemigo){
    EntityMgr->crearGuardia(enemigo->getPatrulla());
    int id = EntityMgr->getNextID()-1;
    Enemy* guardia = static_cast<Enemy*>(EntityMgr->getEntityByID(id));
    guardia->setPosicionInteres(enemigo->getPosition());
    guardia->GetFSM()->ChangeState(Investigar::Instance());
    /*PatrolRoute* ruta = enemigo->getPatrulla();
    ruta->setInicial(enemigo->getPatrulla()->getInicial()->getNext());
    EntityMgr->crearGuardia(ruta);*/

}
bool Alarma::OnMessage(Enemy* enemigo, const Mensaje& msg){

}
