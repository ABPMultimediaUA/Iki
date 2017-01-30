#ifndef ALGORITMO
#define ALGORITMO

#include <irrlicht.h>
#include <enemigo.h>
#include <Heuristic_Euclid.h>

template< class graph_type, class heuristic>
class Algoritmo
{
    private:
        //creo un typedef?
        typedef typename graph_type::EdgeType Edge;
        const graph_type& Grafo;
        //indexed into by node. Contiene el coste "real" acumulativo hasta el nodo
        std::vector<double> costReal;
         //Contiene el coste de anyadir costReal [n] a el costre heuristico de n al nodo objetivo
        std::vector<double> Fcost;
        std::vector<const Edge*> PathMasCorto;
        std::vector<const Edge*> BuscarFrontera;
        int desde;
        int hasta;
        //the A* search algorithm
        void Search();
    public:
        Algoritmo(graph_type& graph,
                            int source,
                            int target):Grafo(graph),
                            PathMasCorto(graph.NumNodes()),
                            BuscarFrontera(graph.NumNodes()),
                            costReal(graph.NumNodes(), 0.0),
                            Fcost(graph.NumNodes(), 0.0),
                            desde(source),
                            hasta(target)
        {
        Search();
        }
        //returns the vector of edges that the algorithm has examined
        std::vector<const Edge*> GetSPT()const;
        //returns a vector of node indexes that comprise the shortest path
        //from the source to the target
        list<int> GetPathToTarget()const;
        //returns the total cost to the target
        double GetCostToTarget()const;
    protected:


};

#endif // ALGORITMO
