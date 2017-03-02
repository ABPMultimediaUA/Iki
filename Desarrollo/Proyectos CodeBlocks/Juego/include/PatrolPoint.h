#ifndef PATROLPOINT_H
#define PATROLPOINT_H

#include "Structs.h"

class PatrolPoint
{
    public:
        PatrolPoint(int enem, int cont, int n, Structs::TPosicion v);
        ~PatrolPoint();

        Structs::TPosicion getPunto()   { return punto;   }
        int                getEnemigo() { return enemigo; }
        int                getID()      { return id;      }
        int                getNext0()   { return next0;   }

        void setNext(PatrolPoint* point);
        void setPrev(PatrolPoint* point);
        PatrolPoint* getNext();
        PatrolPoint* getPrev();

    protected:

    private:
        // enemigo es el enemigo al que se le asocia el PatrolPoint
        // id es la id dentro de la ruta de patrulla, cada ruta de patrulla empezara por un PatrolPoint con id 1
        // next0 indica la direccion hacia la que va el PatrolPoint, si es 0 va hacia el next, si es 1 va hacia el prev
        int enemigo, id, next0;

        Structs::TPosicion punto;
        PatrolPoint* next;
        PatrolPoint* prev;


};

#endif // PATROLPOINT_H
