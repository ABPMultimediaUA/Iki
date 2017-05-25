#include "Enemies/StateMachine/Proteger.h"
#include "Enemies/StateMachine/PedirAyuda.h"
#include "Enemy.h"
#include "Enemies/StateMachine/Patrullar.h"
#include "Enemies/Medico.h"
#include "Enemies/StateMachine/VolverALaPatrulla.h"
#include "Enemies/StateMachine/Huir.h"
#include "Enemies/StateMachine/Muerto.h"


Proteger* Proteger::Instance()
{
  static Proteger instance;
  return &instance;
}

void Proteger::Enter(Enemy* enemigo){
    static_cast<Medico*>(enemigo)->setProtegido(enemigo->getGuardiaMasCercano());
    enemigo->resetTime();
}

void Proteger::Execute(Enemy* enemigo){
    if(enemigo->hayGuardias()){
        if(static_cast<Medico*>(enemigo)->getProtegido()->getVida() == 0){//Si su protegido esta muerto
            enemigo->GetFSM()->ChangeState(PedirAyuda::Instance());//Pide ayuda a otro
        }

        if(static_cast<Medico*>(enemigo)->getProtegido()->GetFSM()->isInState(*VolverALaPatrulla::Instance()))
            enemigo->GetFSM()->ChangeState(VolverALaPatrulla::Instance());

        static_cast<Medico*>(enemigo)->proteger();
    }
    else{
        enemigo->GetFSM()->ChangeState(Huir::Instance());
    }
}

void Proteger::Exit(Enemy* enemigo){}
bool Proteger::OnMessage(Enemy*, const Mensaje&){}
