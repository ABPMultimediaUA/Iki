#ifndef NODO
#define NODO

#include <irrlicht.h>
#include <enemigo.h>


class Nodo
{
    public:
        Nodo():index(-1){}//invalido
        Nodo(int idx):index(idx){}
        virtual ~Nodo();
        int Index()const;
        void setIndex(int NewIndex);


    protected:
        int index;

    private:
        irr::core::vector3df posicion;
        //extra_info extra_info; si queremos que el nodo represente un pickup como armadura, vida, etc y luego poder buscarlo en el grafo
};

#endif // NODO
