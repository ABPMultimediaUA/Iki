#ifndef MEMORY_H
#define MEMORY_H

#include "Structs.h"

enum EstadoEntity
        {
            todoCorrecto,
            sospechoso,
            muerto,
            abierta,
            yaLoSabia
        };

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
  //estado de la ultima vez que lo vio
  EstadoEntity estado;
  //si esta en el fieldOfView sin obstaculos
  bool        entraEnFOV;
  //si no hay obstaculos
  bool        sinObstaculos;

  MemoryRecord():ultimaVista(-999),
            primeraVista(-999),
            ultimaPercepcion(0),
            estado(todoCorrecto),
            entraEnFOV(false),
            sinObstaculos(false)
  {}
};



#endif // MEMORY_H
