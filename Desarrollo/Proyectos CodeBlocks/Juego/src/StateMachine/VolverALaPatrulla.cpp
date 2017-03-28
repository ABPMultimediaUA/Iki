#include "VolverALaPatrulla.h"
#include "Enemy.h"
#include "Patrullar.h"
#include "Escanear.h"
#include "Mensaje.h"


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
