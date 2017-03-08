#include "StateMachine/Patrullar.h"
#include "Guardia.h"


Patrullar* Patrullar::Instance()
{
  static Patrullar instance;

  return &instance;
}
void Patrullar::Enter(Enemy* guardia){
    /*//if the miner is not already located at the gold mine, he must
    //change location to the gold mine
    if (pMiner->Location() != goldmine)
    {
    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
    << "Walkin' to the gold mine";
    pMiner->ChangeLocation(goldmine);
    }*/
}

void Patrullar::Execute(Enemy* guardia){

    guardia->patrullar();

}

void Patrullar::Exit(Enemy* guardia){}
bool Patrullar::OnMessage(Enemy*, const Telegram&){}
