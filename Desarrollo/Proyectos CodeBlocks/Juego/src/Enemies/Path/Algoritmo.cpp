#include "Enemies/Path/Algoritmo.h"

/*Asi funciona el algoritmo A*:
- Si el nodo inicial es igual al nodo final, se retorna el nodo inicial como solucion
- Si no, se adiciona el nodo inicial a la lista abierta
- Mientras la lista abierta no este vacia, se recorre cada nodo que haya en la lista abierta y se toma el que tenga el costo total mas bajo
- Si el nodo obtenido es igual al nodo final, se retornan todos los nodos sucesores al nodo encontrado
- Si no , se toma el nodo y se elimina de la lista abierta para guardarse en la lista cerrada y se buscan todos los nodos adyacentes
al nodo obtenido y se adicionan a la lista abierta a menos que el nodo se encuentre en la lista cerrada o que el nodo sea solido
- Si el nodo adyacente ya se encuentra en la lista abierta se verifica que el costo sea menor, si es menor se cambian los valores de costo,
sino se ignora
- Se vuelve al paso 3 y se repite hasta que el punto 4 sea verdadero o que la lista abierta quede vacía

*/

void Algoritmo::Search()
{

//Creo una lista que prioriza los nodos con coste menor
    IndexedPriorityQLow<double> pq(Fcost, Grafo.numNodes());
    //std::cout<<"Numero de Nodos"<<Grafo.numNodes()<<std::endl;
//pongo el nodo de inicio en la lista
    pq.insert(desde);
//mientras la lista no este vacia
    while(!pq.empty())
    {
//cojo el nodo con menos coste en la lista snc = SIGUIENTENODOMASCERCANO
        int snc = pq.Pop();
//muevo el nodo desde un vector a otro
        PathMasCorto[snc] = BuscarFrontera[snc];
//Si el nodo inicial es igual al nodo final, se retorna el nodo inicial como solución
        if (snc == hasta) return;
//comprobamos las aristas con las que esta conectada el nodo
        SparseGraph::ConstEdgeIterator ConstEdgeItr(Grafo, snc);
        for (const Edge* pE=ConstEdgeItr.begin();!ConstEdgeItr.end();pE=ConstEdgeItr.next())
        {

//calculamos el coste heuristico desde el nodo hasta el target
            double HCost = Heuristic_Euclid::Calculate(Grafo, hasta, pE->To());
//calculamos el coste real
            double GCost = costReal[snc] + pE->Cost();

//Si el nodo no ha sido anyadido al vector frontera, lo anyado y actualizo
//the G and F costs
            if (BuscarFrontera[pE->To()] == NULL)
            {
                Fcost[pE->To()] = GCost + HCost;
                costReal[pE->To()] = GCost;
                pq.insert(pE->To());
                BuscarFrontera[pE->To()] = pE;
            }
//Si el nodo ya se encuentra en la forntera pero el coste para coger este camino es mas bajo
//que el que habia encontrado antes, entonces actualizo el coste del nodo y del vector frontera
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

std::list<PathEdge> Algoritmo::GetPathAsPathEdges()const
{
  std::list<PathEdge> path;

  //just return an empty path if no target or no path found
  if (hasta < 0)  return path;

  int nd = hasta;

  while ((nd != desde) && (PathMasCorto[nd] != 0))
  {
    path.push_front(PathEdge(Grafo.getNode(PathMasCorto[nd]->From()).posicion,
                             Grafo.getNode(PathMasCorto[nd]->To()).posicion,
                             1)
                             );

    nd = PathMasCorto[nd]->From();
  }

  return path;
}
