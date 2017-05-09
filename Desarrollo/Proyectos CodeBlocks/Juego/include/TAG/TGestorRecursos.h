#ifndef TGESTORRECURSOS_H
#define TGESTORRECURSOS_H

#include "TTexturaCache.h"
#include "TMallaCache.h"



class TGestorRecursos
{
    public:
        TGestorRecursos();
        virtual ~TGestorRecursos();

        TRecursoMalla* getRecursoMalla(const std::string& fileName);
		TTextura* getRecursoTextura(const std::string& fileName);
    protected:

    private:
        TMallaCache m_MallaCache;
		TTexturaCache m_TexturaCache;
};

#endif // TGESTORRECURSOS_H

