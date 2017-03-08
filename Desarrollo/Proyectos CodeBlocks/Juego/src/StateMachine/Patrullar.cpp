#include "StateMachine/Patrullar.h"
#include "Enemy.h"


Patrullar* Patrullar::Instance()
{
  static Patrullar instance;

  return &instance;
}
void Patrullar::Enter(Enemy* guardia){}
void Patrullar::Execute(Enemy* guardia){}
void Patrullar::Exit(Enemy* guardia){}
bool Patrullar::OnMessage(Enemy*, const Telegram&){}
