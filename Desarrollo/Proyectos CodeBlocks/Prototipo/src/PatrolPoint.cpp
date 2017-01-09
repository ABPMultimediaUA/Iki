#include "PatrolPoint.h"

PatrolPoint::PatrolPoint(irr::core::vector3df v)
{
    //ctor
    punto = v;
    next = nullptr;
    prev = nullptr;
}

PatrolPoint::~PatrolPoint()
{
    //dtor
}

irr::core::vector3df PatrolPoint::getPunto()
{
    return punto;
}

/*
void PatrolPoint::setPunto(irr::core::vector3df v)
{
    punto = v;
}
*/
void PatrolPoint::setNext(PatrolPoint* point)
{
    next = point;
}

void PatrolPoint::setPrev(PatrolPoint* point)
{
    prev = point;
}

PatrolPoint* PatrolPoint::getNext()
{
    return next;
}

PatrolPoint* PatrolPoint::getPrev()
{
    return prev;
}
