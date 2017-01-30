#ifndef NAVGRAPH
#define NAVGRAPH

#include <irrlicht.h>
#include <enemigo.h>

class NavGraph
{
    public:
        NavGraph();
        virtual ~NavGraph();


    protected:

    private:
        irr::core::vector3df nodo;
};

#endif // NAVGRAPH
