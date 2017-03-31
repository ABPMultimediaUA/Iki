#include "Escanear.h"
#include "Enemy.h"
#include "Patrullar.h"
#include "PedirAyuda.h"
#include "Atacar.h"
#include "Alarma.h"

Escanear* Escanear::Instance()
{
  static Escanear instance;

  return &instance;
}

void Escanear::Enter(Enemy* enemigo){
    enemigo->resetTime();
}

void Escanear::Execute(Enemy* enemigo){
    enemigo->escanear();
    if(enemigo->getSospecha()==99){
        ///COMBATEEE
        switch(enemigo->getTipo()){
        case 1:
            enemigo->GetFSM()->ChangeState(Atacar::Instance());
            break;
        case 2:
            enemigo->GetFSM()->ChangeState(PedirAyuda::Instance());
            break;
        case 3:
            enemigo->GetFSM()->ChangeState(Alarma::Instance());
            break;
        default:
            break;
        }
    }
    else if(enemigo->getTiempo()>1.5)
        enemigo->GetFSM()->ChangeState(Patrullar::Instance());

}

void Escanear::Exit(Enemy* enemigo){}
bool Escanear::OnMessage(Enemy*, const Mensaje&){}
