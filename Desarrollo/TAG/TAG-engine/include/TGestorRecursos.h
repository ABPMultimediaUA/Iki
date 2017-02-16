#ifndef TGESTORRECURSOS_H
#define TGESTORRECURSOS_H

#include <iostream>
#include <vector>
#include "TRecurso.h"


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
};

#endif // TGESTORRECURSOS_H
