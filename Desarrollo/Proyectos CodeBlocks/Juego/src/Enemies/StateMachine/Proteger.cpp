#include "Enemies/StateMachine/Proteger.h"
#include "Enemies/StateMachine/PedirAyuda.h"
#include "Enemy.h"
#include "Enemies/StateMachine/Patrullar.h"
#include "Enemies/Medico.h"
#include "Enemies/StateMachine/VolverALaPatrulla.h"


Proteger* Proteger::Instance()
{
  static Proteger instance;
  return &instance;
}

void Proteger::Enter(Enemy* enemigo){
    static_cast<Medico*>(enemigo)->setProtegido(enemigo->getGuardiaMasCercano());
}

void Proteger::Execute(Enemy* enemigo){
    static_cast<Medico*>(enemigo)->proteger();
    if(enemigo->getGuardiaMasCercano()->GetFSM()->isInState(*VolverALaPatrulla::Instance()))
        enemigo->GetFSM()->ChangeState(VolverALaPatrulla::Instance());
}

void Proteger::Exit(Enemy* enemigo){}
bool Proteger::OnMessage(Enemy*, const Mensaje&){}
