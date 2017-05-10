#ifndef MEMORY_H
#define MEMORY_H

#include "Structs.h"

class MemoryRecord
{
public:
  //ultima vez que vio al player
  float       ultimaVista;
  //primera vez que vio al player (currentTime - primeraVista) y sabremos cuanto tiempo ha sido visible el player
  float       primeraVista;
  //hace cuanto que ha percibido al player (escuchado o visto)
  float       ultimaPercepcion;
  //ultima posicion en ver el player
  Structs::TPosicion    ultimaPosicion;
  //si esta en el fieldOfView
  bool        estaFOV;
  //Si es shootable
  bool        sinObstaculos;

  MemoryRecord():ultimaVista(-999),
            primeraVista(-999),
            ultimaPercepcion(0),
            estaFOV(false),
            sinObstaculos(false)
  {}
};



#endif // MEMORY_H
