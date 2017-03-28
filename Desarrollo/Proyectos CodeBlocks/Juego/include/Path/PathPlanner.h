#ifndef PATHPLANNER
#define PATHPLANNER

#include "SparseGraph.h"
#include "GameEntity.h"
#include "Path/Algoritmo.h"



class PathPlanner
{
    private:
        GameEntity* propietario; //Puntero al propietario de esta clase
        SparseGraph* grafo;
        //const SparseGraph& grafo;
        Structs::TPosicion posicionDestino;
        int getNodoMasCercano(Structs::TPosicion pos);

    public:
        PathPlanner(SparseGraph* graf, GameEntity* owner):propietario(owner),grafo(graf){};
        virtual ~PathPlanner(){};

        bool crearPath(Structs::TPosicion destino, std::list<PathEdge>& path);
        void ConvertIndicesToVectors(std::list<int> pNodos, std::list<Structs::TPosicion> &path);
        void SmoothPathEdgesQuick(std::list<PathEdge>& path);
        void SmoothPathEdgesPrecise(std::list<PathEdge>& path);


    protected:



};

#endif // PATHPLANNER
