#ifndef NODO
#define NODO

#include <irrlicht.h>
#include <list>
#include <cstdlib>
#include <iostream>



class Nodo
{
    public:
        Nodo():index(-1){}//invalido
        Nodo(int idx):index(idx){}
        virtual ~Nodo(){}
        int Index()const;
        void setIndex(int NewIndex);
        float calcularCoste(Nodo b);
        irr::core::vector3df posicion;

    protected:
        int index;
//        vector3df posicion;

    private:

        //extra_info extra_info; si queremos que el nodo represente un pickup como armadura, vida, etc y luego poder buscarlo en el grafo
};

#endif // NODO
