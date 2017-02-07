#ifndef TNODO_H
#define TNODO_H

#include "TEntidad.h"
#include <vector>

using namespace std;

class TNodo
{
    public:
        TNodo();
        virtual ~TNodo();

        int addHijo(TNodo* nodo);
        int remHijo(TNodo* nodo);
        bool setEntidad(TEntidad* ent);
        TEntidad *getEntidad();
        TNodo *getPadre();

        void draw();

    protected:

    private:
        TEntidad *entidad;
        std::vector<TNodo*> hijos;
        TNodo *padre;
};

#endif // TNODO_H
