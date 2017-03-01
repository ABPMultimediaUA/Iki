#ifndef PATHPLANNER
#define PATHPLANNER

#include <irrlicht.h>
#include "SparseGraph.h"
#include "Algoritmo.h"
#include "Enemigo.h"


class PathPlanner
{
    public:
        PathPlanner(Enemigo* owner,SparseGraph* graf);
        virtual ~PathPlanner();
        bool crearPath(vector3df destino, std::list<PathEdge>& path);

        void SmoothPathEdgesQuick(std::list<PathEdge>& path);
        void SmoothPathEdgesPrecise(std::list<PathEdge>& path);
        void ConvertIndicesToVectors(std::list<int> PathOfNodeIndices, std::list<vector3df> &path);
    protected:

    private:
        Enemigo* enemigo; //Puntero al propietario de esta clase
        SparseGraph* grafo;
        //const SparseGraph& grafo;//const NavGraph& grafo;//Una referencia local al navgraph
        irr::core::vector3df posicionDestino;
        int getNodoMasCercano(irr::core::vector3df pos);
};

#endif // PATHPLANNER
