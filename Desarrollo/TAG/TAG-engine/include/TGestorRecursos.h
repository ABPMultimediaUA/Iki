#ifndef TGESTORRECURSOS_H
#define TGESTORRECURSOS_H

#include <iostream>
#include <vector>
#include "TRecurso.h"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing fla


using namespace std;

class TGestorRecursos
{
    public:
        TGestorRecursos();
        virtual ~TGestorRecursos();
        TRecurso *getRecurso(char* nombre);

    protected:

    private:
        vector<TRecurso*> recursos;
        Assimp::Importer imp;
};

#endif // TGESTORRECURSOS_H
