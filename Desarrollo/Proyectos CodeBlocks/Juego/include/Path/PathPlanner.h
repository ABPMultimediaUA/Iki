#ifndef PATHPLANNER
#define PATHPLANNER

#include "SparseGraph.h"
#include "Algoritmo.h"
#include "Enemy.h"

class PathPlanner
{
    public:
        PathPlanner(SparseGraph* graf,Enemy* owner);
        virtual ~PathPlanner();
        bool crearPath(Structs::TPosicion destino, std::list<PathEdge>& path);

        void SmoothPathEdgesQuick(std::list<PathEdge>& path);
        void SmoothPathEdgesPrecise(std::list<PathEdge>& path);
        void ConvertIndicesToVectors(std::list<int> PathOfNodeIndices, std::list<Structs::TPosicion> &path);
    protected:

    private:
        Enemy* enemigo; //Puntero al propietario de esta clase
        SparseGraph* grafo;
        //const SparseGraph& grafo;
        Structs::TPosicion posicionDestino;
        int getNodoMasCercano(Structs::TPosicion pos);
};

#endif // PATHPLANNER
