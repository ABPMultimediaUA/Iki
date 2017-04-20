#include "TAG/TGestorRecursos.h"

TGestorRecursos::TGestorRecursos()
{
    //ctor
}

TGestorRecursos::~TGestorRecursos()
{
    //dtor
}

TMallaCache TGestorRecursos::m_MallaCache;
TTexturaCache TGestorRecursos::m_TexturaCache;

TRecursoMalla* TGestorRecursos::getRecursoMalla(const std::string& fileName)
{
    return m_MallaCache.getRecursoMalla(fileName);
}

TTextura* TGestorRecursos::getRecursoTextura(const std::string& fileName)
{
    return m_TexturaCache.getRecursoTextura(fileName);
}


