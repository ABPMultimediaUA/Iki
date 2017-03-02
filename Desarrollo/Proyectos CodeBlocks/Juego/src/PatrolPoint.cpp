#include "PatrolPoint.h"

PatrolPoint::PatrolPoint(int enem, int cont, int n, Structs::TPosicion v)
{
    //ctor
    enemigo = enem;
    id = cont;
    next0 = n;
    punto = v;
    next = 0;
    prev = 0;
}

PatrolPoint::~PatrolPoint()
{
    //dtor
}

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
