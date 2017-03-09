#ifndef HEURISTIC_EUCLID
#define HEURISTIC_EUCLID

#include <Path/SparseGraph.h>
#include <Path/Nodo.h>

class Heuristic_Euclid
{
public:
Heuristic_Euclid(){}
//calculate the straight-line distance from node nd1 to node nd2
//template <class graph_type>
static double Calculate(const SparseGraph& G, int nd1, int nd2)
{
    return G.getNode(nd1).posicion.Distance(G.getNode(nd2).posicion);
}
};
#endif // HEURISTIC_EUCLID
