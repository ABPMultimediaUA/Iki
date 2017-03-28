#include "Enemies/StateMachine/Escanear.h"
#include "Enemy.h"
#include "Enemies/StateMachine/Patrullar.h"
#include "Enemies/StateMachine/PedirAyuda.h"
#include "Enemies/StateMachine/Atacar.h"

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
            if(enemigo->getTipo()== 2){
               // std::cout<<"Pidiendo ayuda..."<<std::endl;
                enemigo->GetFSM()->ChangeState(PedirAyuda::Instance());
            }
            else if(enemigo->getTipo()== 1){
               // std::cout<<"Atacando..."<<std::endl;
                enemigo->GetFSM()->ChangeState(Atacar::Instance());
            }
        }
    else if(enemigo->getTiempo()>3)
        enemigo->GetFSM()->ChangeState(Patrullar::Instance());

}

void Escanear::Exit(Enemy* enemigo){}
bool Escanear::OnMessage(Enemy*, const Mensaje&){}
