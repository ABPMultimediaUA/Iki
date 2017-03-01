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
        int enemigo, id, next0;

        Structs::TPosicion punto;
        PatrolPoint* next;
        PatrolPoint* prev;


};

#endif // PATROLPOINT_H
