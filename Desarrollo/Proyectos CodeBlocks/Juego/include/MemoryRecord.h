#ifndef MEMORY_H
#define MEMORY_H

#include "Structs.h"

class MemoryRecord
{
public:

  float       fTimeLastSensed;
  float       fTimeBecameVisible;
  float       fTimeLastVisible;
  Structs::TPosicion    vLastSensedPosition;
  bool        bWithinFOV;
  bool        bShootable;

  MemoryRecord():fTimeLastSensed(-999),
            fTimeBecameVisible(-999),
            fTimeLastVisible(0),
            bWithinFOV(false),
            bShootable(false)
  {}
};



#endif // MEMORY_H
