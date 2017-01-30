#ifndef PATROLPOINT_H
#define PATROLPOINT_H

#include <irrlicht.h>

class PatrolPoint
{
    public:
        PatrolPoint(irr::core::vector3df v);
        virtual ~PatrolPoint();

        irr::core::vector3df getPunto();
        //void setPunto(irr::core::vector3df v);
        void setNext(PatrolPoint* point);
        void setPrev(PatrolPoint* point);
        PatrolPoint* getNext();
        PatrolPoint* getPrev();

    protected:

    private:
        irr::core::vector3df punto;
        class PatrolPoint* next;
        class PatrolPoint* prev;


};

#endif // PATROLPOINT_H
