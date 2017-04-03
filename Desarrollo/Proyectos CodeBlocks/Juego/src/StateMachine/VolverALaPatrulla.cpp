#include "Enemies/StateMachine/VolverALaPatrulla.h"
#include "Enemy.h"
#include "Enemies/StateMachine/Patrullar.h"
#include "Enemies/StateMachine/Escanear.h"
#include "Enemies/StateMachine/Mensaje.h"


VolverALaPatrulla* VolverALaPatrulla::Instance()
{
  static VolverALaPatrulla instance;

  return &instance;
}

void VolverALaPatrulla::Enter(Enemy* enemigo){
    enemigo->crearPath(enemigo->getPPatrulla()->getPunto());
}

void VolverALaPatrulla::Execute(Enemy* enemigo){
    enemigo->volverALaPatrulla();
    if(enemigo->getPosition() == enemigo->getPPatrulla()->getPunto()){
        enemigo->GetFSM()->ChangeState(Patrullar::Instance());
    }

}

void VolverALaPatrulla::Exit(Enemy* enemigo){
}
bool VolverALaPatrulla::OnMessage(Enemy* enemigo, const Mensaje& msg){

}
