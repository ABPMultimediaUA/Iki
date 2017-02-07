#include "Algoritmo.h"

/*void Algoritmo::Search(){
Si el nodo inicial es igual al nodo final, se retorna el nodo inicial como solución
Si no, se adiciona el nodo inicial a la lista abierta
Mientras la lista abierta no esté vacía, se recorre cada nodo que haya en la lista abierta y se toma el que tenga el costo total más bajo
Si el nodo obtenido es igual al nodo final, se retornan todos los nodos sucesores al nodo encontrado
Si no , se toma el nodo y se elimina de la lista abierta para guardarse en la lista cerrada y se buscan todos los nodos adyacentes al nodo obtenido y se adicionan a la lista abierta a menos que el nodo se encuentre en la lista cerrada o que el nodo sea sólido
Si el nodo adyacente ya se encuentra en la lista abierta se verifica que el costo sea menor, si es menor se cambian los valores de costo, sino se ignora
Se vuelve al paso 3 y se repite hasta que el punto 4 sea verdadero o que la lista abierta quede vacía

}*/

/*Here is how the PathFinder demo program creates an instance of the A* search using the Euclidean heuristic:
//create a couple of typedefs so the code will sit comfortably on the page
typedef SparseGraph<NavGraphNode<>, GraphEdge> NavGraph;
typedef Graph_SearchAStar<NavGraph, Heuristic_Euclid> AStarSearch;
//create an instance of the A* search using the Euclidean heuristic
AStarSearch AStar(*m_pGraph, m_iSourceCell, m_iTargetCell);*/
void Algoritmo::Search()
{
//create an indexed priority queue of nodes. The queue will give priority
//to nodes with low F costs. (F=G+H)
    IndexedPriorityQLow<double> pq(Fcost, Grafo.numNodes());
//put the source node on the queue
    pq.insert(desde);
//while the queue is not empty
    while(!pq.empty())
    {
//get lowest cost node from the queue
        int SiguienteNodoCercano = pq.Pop();
//move this node from the frontier to the spanning tree
        PathMasCorto[SiguienteNodoCercano] = BuscarFrontera[SiguienteNodoCercano];
//if the target has been found exit
        if (SiguienteNodoCercano == hasta) return;
//now to test all the edges attached to this node
        SparseGraph::ConstEdgeIterator ConstEdgeItr(Grafo, SiguienteNodoCercano);
        for (const Edge* pE=ConstEdgeItr.begin();!ConstEdgeItr.end();pE=ConstEdgeItr.next())
        {
//calculate the heuristic cost from this node to the target (H)
            double HCost = Heuristic_Euclid::Calculate(Grafo, hasta, pE->To());
//calculate the "real" cost to this node from the source (G)
            double GCost = costReal[SiguienteNodoCercano] + pE->Cost();
//if the node has not been added to the frontier, add it and update
//the G and F costs
            if (BuscarFrontera[pE->To()] == NULL)
            {
                Fcost[pE->To()] = GCost + HCost;
                costReal[pE->To()] = GCost;
                pq.insert(pE->To());
                BuscarFrontera[pE->To()] = pE;
            }
//if this node is already on the frontier but the cost to get here this
//way is cheaper than has been found previously, update the node costs
//and frontier accordingly.
            else if ((GCost < costReal[pE->To()]) &&
                     (PathMasCorto[pE->To()]==NULL))
            {
                Fcost[pE->To()] = GCost + HCost;
                costReal[pE->To()] = GCost;
                pq.ChangePriority(pE->To());
                BuscarFrontera[pE->To()] = pE;
            }
        }
    }
}

std::list<int> Algoritmo::GetPathToTarget()const
{
  std::list<int> path;

  //just return an empty path if no target or no path found
  if (hasta < 0)  return path;

  int nd = hasta;

  path.push_front(nd);

  while ((nd != desde) && (PathMasCorto[nd] != 0))
  {
    nd = PathMasCorto[nd]->From();

    path.push_front(nd);
  }

  return path;
}
