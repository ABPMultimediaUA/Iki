#include "Enemies/Path/SparseGraph.h"


const Nodo& SparseGraph::getNode(int idx)const{
    //Nos aseguramos que el indice esta dentro del vector nodos
    assert((idx < (int)nodos.size()) &&(idx >=0));
    return nodos[idx];
}
Nodo& SparseGraph::getNode(int idx){
    assert((idx < (int)nodos.size()) &&(idx >=0));
    return nodos[idx];
}
const Edge& SparseGraph::getEdge(int from, int to)const{
    assert( (from < nodos.size()) && (from >=0) && nodos[from].Index() != -1);
    //&&"<SparseGraph::GetEdge>: invalid 'from' index");
    assert( (to < nodos.size()) && (to >=0) && nodos[to].Index() != -1 );

   for (EdgeList::const_iterator curEdge = aristas[from].begin();curEdge != aristas[from].end();++curEdge)
      {
        if (curEdge->To() == to)
            return *curEdge;
      }

  assert (0 && "<SparseGraph::GetEdge>: edge does not exist");

}
Edge& SparseGraph::getEdge(int from, int to){
    it=aristas[from].begin();
    while ((*it).To() != to && it != aristas[from].end())
        it++;

    return (*it);
}
int SparseGraph::getNextNodeIndex() const{
    return nextNodeIndex;
}

int SparseGraph::addNode(Nodo node){
  if (node.Index() < (int)nodos.size())
  {
    //Nos aseguramos que no se esta intentando anyadir un nodo con un index que tiene ahora mismo otro nodo
    assert (nodos[node.Index()].Index() == -1 && "<SparseGraph::AddNode>: Attempting to add a node with a duplicate ID");
    nodos[node.Index()] = node;

    return nextNodeIndex;
  }

  else
  {
    //Nos aseguramos que el nodo se ha indexado correctamente
    assert (node.Index() == nextNodeIndex && "<SparseGraph::AddNode>:invalid index");
    nodos.push_back(node);

    aristas.push_back(EdgeList());

    return nextNodeIndex++;
  }
}
void SparseGraph::removeNode(int node){
  assert(node < (int)nodos.size() && "<SparseGraph::RemoveNode>: invalid node index");

  nodos[node].setIndex(-1);
  if (!bDiagraph)
  {
    for (EdgeList::iterator curEdge = aristas[node].begin();
         curEdge != aristas[node].end();
         ++curEdge)
    {
      for (EdgeList::iterator curE = aristas[curEdge->To()].begin();
           curE != aristas[curEdge->To()].end();
           ++curE)
      {
         if (curE->To() == node)
         {
           curE = aristas[curEdge->To()].erase(curE);

           break;
         }
      }
    }
    aristas[node].clear();
  }

  else
  {
    CullInvalidEdges();
  }
}
void SparseGraph::addEdge(Edge edge){
  assert( (edge.From() < nextNodeIndex) && (edge.To() < nextNodeIndex) &&
          "<SparseGraph::AddEdge>: invalid node index");

  if ( (nodos[edge.To()].Index() != -1) && (nodos[edge.From()].Index() != -1))
  {
    if (UniqueEdge(edge.From(), edge.To()))
    {
      aristas[edge.From()].push_back(edge);
    }
    if (!bDiagraph)
    {
      if (UniqueEdge(edge.To(), edge.From()))
      {
        Edge NewEdge = edge;

        NewEdge.setTo(edge.From());
        NewEdge.setFrom(edge.To());

        aristas[edge.To()].push_back(NewEdge);
      }
    }
  }
}
void SparseGraph::removeEdge(int from,int to){
    assert ( (from < (int)nodos.size()) && (to < (int)nodos.size()) &&
        "<SparseGraph::RemoveEdge>:invalid node index");

    EdgeList::iterator curEdge;

    if (!bDiagraph)
    {
        for (curEdge = aristas[to].begin();curEdge != aristas[to].end();++curEdge)
        {
          if (curEdge->To() == from)
                curEdge = aristas[to].erase(curEdge);break;
        }
    }

    for (curEdge = aristas[from].begin();curEdge != aristas[from].end();++curEdge)
    {
        if (curEdge->To() == to)
                curEdge = aristas[from].erase(curEdge);break;

    }
}

int SparseGraph::numNodes()const{
    return nodos.size();
}
int SparseGraph::numActiveNodes()const{
    int count = 0;
    for (unsigned int n=0; n<nodos.size(); ++n)
        if (nodos[n].Index() != -1)
            ++count;

    return count;
}
int SparseGraph::numEdges()const{
    int count = 0;
    for (EdgeListVector::const_iterator cit = aristas.begin();
         cit != aristas.end();
         ++cit)
    {
      count += cit->size();
    }
    return count;
}
bool SparseGraph::isDigraph()const{
    return bDiagraph;
}
bool SparseGraph::isEmpty()const{
    return nodos.empty();
}
bool SparseGraph::isNodePresent(int idx)const{
    if ((idx >= (int)nodos.size() || (nodos[idx].Index() == -1)))
    {
      return false;
    }
    else return true;
}
bool SparseGraph::isEdgePresent(int from, int to)const{
    if (isNodePresent(from) && isNodePresent(from))
    {
       for (EdgeList::const_iterator curEdge = aristas[from].begin();
            curEdge != aristas[from].end();
            ++curEdge)
        {
          if (curEdge->To() == to) return true;
        }

        return false;
    }
    else return false;
}


bool SparseGraph::UniqueEdge(int from, int to)const
{
  for (EdgeList::const_iterator curEdge = aristas[from].begin();
       curEdge != aristas[from].end();
       ++curEdge)
  {
    if (curEdge->To() == to)
    {
      return false;
    }
  }

  return true;
}
void SparseGraph::CullInvalidEdges()
{
  for (EdgeListVector::iterator curEdgeList = aristas.begin(); curEdgeList != aristas.end(); ++curEdgeList)
  {
    for (EdgeList::iterator curEdge = (*curEdgeList).begin(); curEdge != (*curEdgeList).end(); ++curEdge)
    {
      if (nodos[curEdge->To()].Index() == -1 || nodos[curEdge->From()].Index() == -1)
      {
        curEdge = (*curEdgeList).erase(curEdge);
      }
    }
  }
}
void SparseGraph::setEdgeCost(int from, int to, double NewCost)
{
  assert( (from < (int)nodos.size()) && (to < (int)nodos.size()) &&
        "<SparseGraph::SetEdgeCost>: invalid index");

  for (EdgeList::iterator curEdge = aristas[from].begin(); curEdge != aristas[from].end();++curEdge)
  {
    if (curEdge->To() == to)
    {
      curEdge->setCost(NewCost);
      break;
    }
  }
}
int SparseGraph::nodeMoreClose(Structs::TPosicion p){
    for(int i=0;i<nodos.size();i++){
        ///COMPROBAR SI EL NODO MAS CERCANO ESTA DETRAS DE UN OBSTACULO
        if(nodos[i].posicion.Distance(p)< menorDistancia){
            menorDistancia=nodos[i].posicion.Distance(p);
            indice=nodos[i].Index();
        }
    }
    menorDistancia=5000;
    return indice;
}



