#include "StateMachine/Patrullar.h"


Patrullar* Patrullar::Instance()
{
  static Patrullar instance;

  return &instance;
}
