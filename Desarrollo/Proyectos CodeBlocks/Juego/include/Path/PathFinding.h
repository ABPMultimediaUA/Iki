#ifndef PATHFINDING
#define PATHFINDING

#include <Structs.h>
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
        PathFinding(SparseGraph* graf, Player* play);
        virtual ~PathFinding();
        Structs::TPosicion getPunto();
        bool crearPath(Structs::TPosicion partida,Structs::TPosicion destino, std::list<int>& path);
        int nodoMasCercano(Structs::TPosicion);

    protected:

    private:
        irr::core::vector3df punto;
        Player* player; //Puntero al propietario de esta clase
        SparseGraph* grafo;//const NavGraph& grafo;//Una referencia local al navgraph?
        irr::core::vector3df posicionDestino;
        Algoritmo* algo;
};

#endif // PATHFINDING
