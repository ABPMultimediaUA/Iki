#include "PatrolRoute.h"

PatrolRoute::PatrolRoute()
{
    //ctor
    ocupada = false;
    inicial = nullptr;
    final   = nullptr;

}

PatrolRoute::~PatrolRoute()
{
    //dtor
}


void PatrolRoute::setInicial(PatrolPoint* p)
{
    inicial = p;
}

void PatrolRoute::setFinal(PatrolPoint* p)
{
    final = p;
}

PatrolPoint* PatrolRoute::getInicial()
{
    return inicial;
}

PatrolPoint* PatrolRoute::getFinal()
{
    return final;
}

void PatrolRoute::changeOcupada()
{
    if (ocupada)
        ocupada = false;
    else
        ocupada = true;
}

bool PatrolRoute::isOcupada()
{
    return ocupada;
}
