#ifndef MEMORY_H
#define MEMORY_H

#include "Structs.h"

class MemoryRecord
{
public:
  //Tiempo que tarda en olvidar
  float       tiempoOlvido;
  //Cuanto tiempo ha sido visible el player
  float       tiempoVisible;
  //Hace cuanto que ha visto al player
  float       ultimaPercepcion;
  Structs::TPosicion    ultimaPosicion;
  bool        estaFOV;
  bool        sinObstaculos;

  MemoryRecord():tiempoOlvido(-999),
            tiempoVisible(-999),
            ultimaPercepcion(0),
            estaFOV(false),
            sinObstaculos(false)
  {}
};



#endif // MEMORY_H
