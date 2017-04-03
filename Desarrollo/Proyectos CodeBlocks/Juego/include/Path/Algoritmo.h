#ifndef ALGORITMO
#define ALGORITMO

#include <irrlicht.h>
#include "Enemy.h"
#include "Enemies/Path/Heuristic_Euclid.h"
#include "Enemies/Path/SparseGraph.h"
#include "Enemies/Path/Edge.h"
#include "Enemies/Path/PathEdge.h"
#include "Enemies/Path/PriorityQueue.h"
#include <stdio.h>

//template< class graph_type, class heuristic>
class Algoritmo
{
    private:
        const SparseGraph& Grafo;
        //Contiene el coste "real" acumulativo hasta el nodo
        std::vector<double> costReal;
         //Contiene el coste de anyadir costReal[n] a el coste heuristico de n al nodo objetivo
        std::vector<double> Fcost;
        std::vector<const Edge*> PathMasCorto;
        std::vector<const Edge*> BuscarFrontera;
        int desde;
        int hasta;
        //the A* search algorithm
        void Search();
    public:
        Algoritmo(SparseGraph& graph,int source,int target)
                            :Grafo(graph),
                            PathMasCorto(graph.numNodes()),
                            BuscarFrontera(graph.numNodes()),
                            costReal(graph.numNodes(), 0.0),
                            Fcost(graph.numNodes(), 0.0),
                            desde(source),
                            hasta(target)
        {
        Search();
        }
        std::vector<const Edge*> GetSPT()const{return PathMasCorto;}
        std::list<int> GetPathToTarget()const;
        double GetCostToTarget()const{return costReal[hasta];}
        std::list<PathEdge> GetPathAsPathEdges()const;

    protected:


};

#endif // ALGORITMO
