#ifndef TTEXTURACACHE_H
#define TTEXTURACACHE_H

#include<map>

#include "TTextura.h"

class TTexturaCache
{
    public:
        TTexturaCache();
        virtual ~TTexturaCache();
        TTextura* getRecursoTextura(const std::string& fileName);

    protected:
    private:
        std::map<std::string, TTextura*> m_MapaTextura;
};

#endif // TTEXTURACACHE_H
