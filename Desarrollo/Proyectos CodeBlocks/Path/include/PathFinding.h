#ifndef PATHFINDING
#define PATHFINDING

#include <irrlicht.h>
#include <vector>
#include <fstream>
#include <string>
#include <list>

#include "Player.h"
#include "SparseGraph.h"
#include "Map.h"
#include "Algoritmo.h"

class PathFinding
{
    public:
        PathFinding(SparseGraph* graf);
        virtual ~PathFinding();
        irr::core::vector3df getPunto();
        bool crearPath(irr::core::vector3df partida,irr::core::vector3df destino, std::list<int>& path);
        int nodoMasCercano(irr::core::vector3df);

    protected:

    private:
        irr::core::vector3df punto;
        Player* player; //Puntero al propietario de esta clase
        SparseGraph* grafo;//const NavGraph& grafo;//Una referencia local al navgraph?
        irr::core::vector3df posicionDestino;
        Algoritmo* algo;
};

#endif // PATHFINDING
