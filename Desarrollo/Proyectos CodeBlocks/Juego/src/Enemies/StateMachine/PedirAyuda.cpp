#include "Enemies/StateMachine/PedirAyuda.h"
#include "Enemy.h"
#include "Enemies/StateMachine/Patrullar.h"
#include "Enemies/Medico.h"
#include "Enemies/StateMachine/EnviarMensaje.h"
#include "Enemies/StateMachine/Proteger.h"
#include "Enemies/StateMachine/Huir.h"
#include "Enemies/StateMachine/Muerto.h"

PedirAyuda* PedirAyuda::Instance()
{
  static PedirAyuda instance;
  return &instance;
}

void PedirAyuda::Enter(Enemy* enemigo){
    if(enemigo->hayGuardias()){
        enemigo->getGuardiaMasCercano()->setPosicionInteres(enemigo->getPosition());
        enemigo->crearPath(enemigo->getGuardiaMasCercano()->getPosition());
    }

    SoundMgr->playSonido("VocesRobots/Medico/intruso_detectado_medico");
}

void PedirAyuda::Execute(Enemy* enemigo){
    if(enemigo->hayGuardias()){
        static_cast<Medico*>(enemigo)->pedirAyuda();
        if(enemigo->getPosition().Distance(enemigo->getGuardiaMasCercano()->getPosition())<10.0f){
            EnviarMsg->Envio(0,enemigo->ID(),enemigo->getGuardiaMasCercano()->ID(),Msg_NeedHelp,0);
            enemigo->GetFSM()->ChangeState(Proteger::Instance());
        }
   }
    else{
        enemigo->GetFSM()->ChangeState(Huir::Instance());
    }
}
void PedirAyuda::Exit(Enemy* enemigo){}
bool PedirAyuda::OnMessage(Enemy*, const Mensaje&){}
