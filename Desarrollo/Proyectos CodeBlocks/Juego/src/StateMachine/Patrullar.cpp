#include "StateMachine/Patrullar.h"
#include "Guardia.h"


Patrullar* Patrullar::Instance()
{
  static Patrullar instance;

  return &instance;
}
void Patrullar::Enter(Guardia* guardia){}
void Patrullar::Execute(Guardia* guardia){}
void Patrullar::Exit(Guardia* guardia){}
bool Patrullar::OnMessage(Guardia*, const Telegram&){}
