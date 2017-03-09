#include "Patrullar.h"
#include "Vigilar.h"
#include "Enemy.h"
#include "Guardia.h"


Patrullar* Patrullar::Instance()
{
  static Patrullar instance;

  return &instance;
}

void Patrullar::Enter(Enemy* enemigo){
    /*//if the miner is not already located at the gold mine, he must
    //change location to the gold mine
    if (pMiner->Location() != goldmine)
    {
    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
    << "Walkin' to the gold mine";
    pMiner->ChangeLocation(goldmine);
    }*/
}

void Patrullar::Execute(Enemy* enemigo){

    enemigo->patrullar();
    if(enemigo->getTiempo() > 11){
        enemigo->resetTime();
        static_cast<Guardia*>(enemigo)->GetFSM()->ChangeState(Vigilar::Instance());
    }

}

void Patrullar::Exit(Enemy* enemigo){}
bool Patrullar::OnMessage(Enemy*, const Telegram&){}
