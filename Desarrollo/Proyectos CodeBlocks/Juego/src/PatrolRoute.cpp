#include "PatrolRoute.h"
#include "PatrolPoint.h"

PatrolRoute::PatrolRoute(PatrolPoint* inicio)
{
    //ctor
    inicial = inicio;
    enemigo = inicial->getEnemigo();

}

PatrolRoute::~PatrolRoute()
{
    //dtor
}


void PatrolRoute::setInicial(PatrolPoint* p)
{
    inicial = p;
}
