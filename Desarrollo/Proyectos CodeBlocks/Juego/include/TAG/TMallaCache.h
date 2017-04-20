#ifndef TMALLACACHE_H
#define TMALLACACHE_H


#include<map>
#include "TRecursoMalla.h"

class TMallaCache
{
    public:
        TMallaCache();
        virtual ~TMallaCache();
        TRecursoMalla* getRecursoMalla(const std::string& fileName);
    protected:
    private:
        std::map<std::string, TRecursoMalla*> m_MapaMalla;
};

#endif // TMALLACACHE_H
