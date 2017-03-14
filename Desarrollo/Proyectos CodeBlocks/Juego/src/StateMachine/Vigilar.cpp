#include "Vigilar.h"
#include "Enemy.h"
#include "Patrullar.h"

Vigilar* Vigilar::Instance()
{
  static Vigilar instance;

  return &instance;
}

void Vigilar::Enter(Enemy* enemigo){
    /*//if the miner is not already located at the gold mine, he must
    //change location to the gold mine
    if (pMiner->Location() != goldmine)
    {
    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
    << "Walkin' to the gold mine";
    pMiner->ChangeLocation(goldmine);
    }*/
}

void Vigilar::Execute(Enemy* enemigo){

    enemigo->vigilar();
    if(enemigo->getTiempo() > 5){
        enemigo->resetTime();
        enemigo->GetFSM()->ChangeState(Patrullar::Instance());
    }

}

void Vigilar::Exit(Enemy* enemigo){}
bool Vigilar::OnMessage(Enemy*, const Mensaje&){}
