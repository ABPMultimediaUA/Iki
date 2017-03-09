#ifndef TNODO_H
#define TNODO_H

#include <iostream>
#include "TEntidad.h"
#include <vector>

using namespace std;

class TNodo
{
    public:
        TNodo(string nom);
        virtual ~TNodo();

        int addHijo(TNodo* nodo);
        int remHijo(TNodo* nodo);
        bool setEntidad(TEntidad* ent);
        TEntidad *getEntidad();
        TNodo *getPadre();

        void draw();

    protected:

    private:
        //ponerlos en el constructor
        TEntidad *entidad;
        vector<TNodo*> hijos;
        TNodo *padre;
        string nombre;
};

#endif // TNODO_H
