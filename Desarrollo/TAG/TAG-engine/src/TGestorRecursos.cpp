#include "TGestorRecursos.h"

TGestorRecursos::TGestorRecursos()
{
    //ctor
}

TGestorRecursos::~TGestorRecursos()
{
    //dtor
}

TRecurso *TGestorRecursos::getRecurso(char* nombre)
{
    vector<TRecurso*>::iterator it = recursos.begin();

    /*while(it != hijos.end())
    {
        if(*it->getNombre() == nombre)
        {
            return *it;
        }
        ++it;
    }*/
/*
    TRecurso* rec= new TRecurso();
    rec->//parse
    recursos->.push_back(rec);
    return rec;*/
}
