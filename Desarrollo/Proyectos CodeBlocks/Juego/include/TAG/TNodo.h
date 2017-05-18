#ifndef TNODO_H
#define TNODO_H

#include <iostream>
#include "TEntidad.h"
#include "TVector.h"
#include "TTransform.h"
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
        void setPadre(TNodo* padre);
        TNodo *getPadre();
        void Trasladar(TVector vec);
        void Rotar(float ang, TVector vec);
        void EscalarAbs(float num);
        void EscalarRel(TVector vec);
        void draw();

    protected:

    private:
        //ponerlos en el constructor
        TEntidad *entidad;
        vector<TNodo*> hijos;
        TNodo *padre;
};

#endif // TNODO_H
