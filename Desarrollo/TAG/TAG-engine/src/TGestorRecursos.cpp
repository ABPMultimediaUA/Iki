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
     for(int i=0; i < recursos.size(); i++)
    {
        if(recursos[i]->getNombre() == nombre)
        {
            return recursos[i];
        }
    }

    /*
    vector<TRecurso*>::iterator it = recursos.begin();
    *it->
    while(it != recursos.end())
    {
        if(*it->getNombre() == nombre)
        {
            return *it;
        }
        ++it;
    }
    */

    Assimp::Importer imp;
    TRecurso* rec;
    const aiScene* scene = imp.ReadFile(nombre, aiProcess_Triangulate);
   //rec->//parse
    recursos.push_back(rec);
    return rec;
}
