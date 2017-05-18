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
    inicial = nullptr;
    enemigo = 0;
}


void PatrolRoute::setInicial(PatrolPoint* p)
{
    inicial = p;
}
