#ifndef PRECALCULATED_H
#define PRECALCULATED_H

#include "Enemy.h"
#include "Enemies/Path/Algoritmo.h"

class SparseGraph;
std::vector<std::vector<int> > CreateAllPairsTable(const SparseGraph& G)
{
    enum {no_path = -1};
    //create a 2D table of elements all set to the enumerated value no_path
    std::vector<int> row(G.numNodes(), no_path); //fila
    std::vector<std::vector<int> > shortest_paths(G.numNodes(), row);
    for (int source=0; source<G.numNodes(); ++source)
    {
        //calculate the SPT for this node
        ///TIENE QUE SER SPT DI
        Algoritmo search(G, source);
        std::vector<const PathEdge*> spt = search.GetSPT();
        //now that we have the SPT it's easy to work backward through it to find
        //the shortest paths from each node to this source node
        for (int target = 0; target<G.numNodes(); ++target)
        {
            if (source == target)
            {
                shortest_paths[source][target] = target;
            }
            else
            {
                int nd = target;
                while ((nd != source) && (spt[nd] != 0))
                {
                    shortest_paths[spt[nd]->()][target]= nd;
                    nd = spt[nd]->getSource();
                }
            }
        }//next target node
    }//next source node
    return shortest_paths;
}

#endif // PRECALCULATED_H
