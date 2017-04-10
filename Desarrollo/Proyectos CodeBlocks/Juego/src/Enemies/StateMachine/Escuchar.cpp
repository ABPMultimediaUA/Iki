#include "Escuchar.h"
#include "Enemy.h"


Escuchar* Escuchar::Instance()
{
  static Escuchar instance;
  return &instance;
}

void Escuchar::Enter(Enemy* enemigo)
{

}

void Escuchar::Execute(Enemy* enemigo)
{
    enemigo->escuchar();
    //si veo al player -> escanear
    //si no
        //si velocidad player == 2 -> sospecha ++
            //si sospecha == X -> escanear
        //si no
            //aguanta 3 segundos y vuelve al anterior
}

void Escuchar::Exit(Enemy* enemigo)
{

}

bool Escuchar::OnMessage(Enemy* enemigo, const Mensaje& msg)
{/*
    switch( msg.Msg )
    {
        case Msg_NeedHelp:
        {
            std::cout<<"recibo el mensajeee"<<std::endl;
            enemigo->GetFSM()->ChangeState(Investigar::Instance());
        }
    }*/
}
