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
        //creo un typedef typename?
        //typedef typename graph_type::EdgeType Edge;
        const SparseGraph& Grafo;
        //indexed into by node. Contiene el coste "real" acumulativo hasta el nodo
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
        //returns the vector of edges that the algorithm has examined
        std::vector<const Edge*> GetSPT()const{return PathMasCorto;}
        //returns a vector of node indexes that comprise the shortest path
        //from the source to the target
        std::list<int> GetPathToTarget()const;
        //returns the total cost to the target
        double GetCostToTarget()const{return costReal[hasta];}

        std::list<PathEdge> GetPathAsPathEdges()const;

    protected:


};

#endif // ALGORITMO
