#ifndef PATHPLANNER
#define PATHPLANNER

#include "SparseGraph.h"
#include "Algoritmo.h"
#include "GameEntity.h"

class PathPlanner
{
    public:
        PathPlanner(GameEntity* owner,SparseGraph* graf);
        virtual ~PathPlanner();
        bool crearPath(Structs::TPosicion destino, std::list<PathEdge>& path);

        void SmoothPathEdgesQuick(std::list<PathEdge>& path);
        void SmoothPathEdgesPrecise(std::list<PathEdge>& path);
        void ConvertIndicesToVectors(std::list<int> PathOfNodeIndices, std::list<Structs::TPosicion> &path);
    protected:

    private:
        GameEntity* entidad; //Puntero al propietario de esta clase
        SparseGraph* grafo;
        //const SparseGraph& grafo;//const NavGraph& grafo;//Una referencia local al navgraph
        Structs::TPosicion posicionDestino;
        int getNodoMasCercano(Structs::TPosicion pos);
};

#endif // PATHPLANNER
