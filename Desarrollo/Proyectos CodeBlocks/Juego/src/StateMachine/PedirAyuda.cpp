#include "PedirAyuda.h"
#include "Enemy.h"
#include "Patrullar.h"
#include "Medico.h"
#include "EnviarMensaje.h"
#include "Proteger.h"

PedirAyuda* PedirAyuda::Instance()
{
  static PedirAyuda instance;
  return &instance;
}

void PedirAyuda::Enter(Enemy* enemigo){
    //std::cout<<"ID guardia mas cercano"<<enemigo->getGuardiaMasCercano()->ID()<<std::endl;
    enemigo->getGuardiaMasCercano()->setPosicionInteres(enemigo->getPosition());
    enemigo->crearPath(enemigo->getGuardiaMasCercano()->getPosition());
}

void PedirAyuda::Execute(Enemy* enemigo){
    static_cast<Medico*>(enemigo)->pedirAyuda();
    if(enemigo->getPosition().Distance(enemigo->getGuardiaMasCercano()->getPosition())<10.0f){
        EnviarMsg->Envio(0,enemigo->ID(),enemigo->getGuardiaMasCercano()->ID(),Msg_NeedHelp,0);
        enemigo->GetFSM()->ChangeState(Proteger::Instance());
    }


}

void PedirAyuda::Exit(Enemy* enemigo){}
bool PedirAyuda::OnMessage(Enemy*, const Mensaje&){}
