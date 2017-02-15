#include "SparseGraph.h"


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
    // aristas[from] deberia ser una lista de edges
    it=aristas[from].begin();
    //con el iterador it recorro la lista
    while ((*it).To() != to && it != aristas[from].end())
        it++;

    return (*it);
}
int SparseGraph::getNextNodeIndex() const{
    return nextNodeIndex;
}
//  Given a node this method first checks to see if the node has been added
//  previously but is now innactive. If it is, it is reactivated.
//
//  If the node has not been added previously, it is checked to make sure its
//  index matches the next node index before being added to the graph
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
    //std::cout<<" anyade el nodo al grafo"<<std::endl;
    nodos.push_back(node);

    aristas.push_back(EdgeList());

    return nextNodeIndex++;
  }
}
//removes a node by setting its index to invalid_node_index
void SparseGraph::removeNode(int node){
  assert(node < (int)nodos.size() && "<SparseGraph::RemoveNode>: invalid node index");

  //set this node's index to invalid_node_index
  nodos[node].setIndex(-1);

  //if the graph is not directed remove all edges leading to this node and then
  //clear the edges leading from the node
  if (!bDiagraph)
  {
    //visit each neighbour and erase any edges leading to this node
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

    //finally, clear this node's edges
    aristas[node].clear();
  }

  //if a digraph remove the edges the slow way
  else
  {
    CullInvalidEdges();
  }
}
void SparseGraph::addEdge(Edge edge){
    //first make sure the from and to nodes exist within the graph
  assert( (edge.From() < nextNodeIndex) && (edge.To() < nextNodeIndex) &&
          "<SparseGraph::AddEdge>: invalid node index");
  //make sure both nodes are active before adding the edge

  if ( (nodos[edge.To()].Index() != -1) && (nodos[edge.From()].Index() != -1))
  {
    //add the edge, first making sure it is unique
    if (UniqueEdge(edge.From(), edge.To()))
    {
      aristas[edge.From()].push_back(edge);
    }
    //if the graph is undirected we must add another connection in the opposite
    //direction
    if (!bDiagraph)
    {
      //check to make sure the edge is unique before adding
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
    //std::cout<<"CuantosNodos"<<nodos.size()<<std::endl;
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

  //-------------------------------- UniqueEdge ----------------------------
//
//  returns true if the edge is not present in the graph. Used when adding
//  edges to prevent duplication
//------------------------------------------------------------------------

bool SparseGraph::UniqueEdge(int from, int to)const
{
  for (EdgeList::const_iterator curEdge = aristas[from].begin();
       curEdge != aristas[from].end();
       ++curEdge)
  {
      //std::cout<<curEdge->From()<<"UniqueEdge: "<<curEdge->To()<<std::endl;
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
  //make sure the nodes given are valid
  assert( (from < (int)nodos.size()) && (to < (int)nodos.size()) &&
        "<SparseGraph::SetEdgeCost>: invalid index");

  //visit each neighbour and erase any edges leading to this node
  for (EdgeList::iterator curEdge = aristas[from].begin(); curEdge != aristas[from].end();++curEdge)
  {
    if (curEdge->To() == to)
    {
      curEdge->setCost(NewCost);
      break;
    }
  }
}
int SparseGraph::nodeMoreClose(irr::core::vector3df p){
    for(int i=0;i<nodos.size();i++){
        //std::cout<<"Posicion partida: "<<p.X<<","<<p.Z<<std::endl;
        //std::cout<<"Entraa: "<<nodos[i].posicion.getDistanceFrom(p)<<std::endl;
        if(nodos[i].posicion.getDistanceFrom(p)< menorDistancia){
            menorDistancia=nodos[i].posicion.getDistanceFrom(p);
            indice=nodos[i].Index();
        }
    }
    menorDistancia=5000;
    return indice;
}

///SAVES Y LOADS
//-------------------------------- Save ---------------------------------------

/*bool SparseGraph::save(const char* FileName)const
{
  //open the file and make sure it's valid
  std::ofstream out(FileName);

  if (!out)
  {
    throw std::runtime_error("Cannot open file: " + std::string(FileName));
    return false;
  }

  return save(out);
}

//-------------------------------- Save ---------------------------------------
bool SparseGraph::save(std::ofstream& stream)const
{
  //save the number of nodes
  stream << nodos.size() << std::endl;

  //iterate through the graph nodes and save them
  NodeVector::const_iterator curNode = nodos.begin();
  for (curNode; curNode!=nodos.end(); ++curNode)
  {
    stream << *curNode;
  }

  //save the number of edges
  stream << NumEdges() << std::endl;


  //iterate through the edges and save them
  for (unsigned int nodeIdx = 0; nodeIdx < nodos.size(); ++nodeIdx)
  {
    for (EdgeList::const_iterator curEdge = aristas[nodeIdx].begin();
         curEdge!=aristas[nodeIdx].end(); ++curEdge)
    {
      stream << *curEdge;
    }
  }

  return true;
}
//------------------------------- Load ----------------------------------------
//----------------------------------------------------------------------------
bool SparseGraph::load(const char* FileName)
{
  //open file and make sure it's valid
  std::ifstream in(FileName);

  if (!in)
  {
    throw std::runtime_error("Cannot open file: " + std::string(FileName));
    return false;
  }

  return load(in);
}

//------------------------------- Load ----------------------------------------
//-----------------------------------------------------------------------------
bool SparseGraph::load(std::ifstream& stream)
{
  clear();

  //get the number of nodes and read them in
  int NumNodes, NumEdges;

  stream >> NumNodes;

  for (int n=0; n<NumNodes; ++n)
  {
    Nodo newNode(stream);

    //when editing graphs it's possible to end up with a situation where some
    //of the nodes have been invalidated (their id's set to invalid_node_index). Therefore
    //when a node of index invalid_node_index is encountered, it must still be added.
    if (NewNode.Index() != -1)
    {
      addNode(NewNode);
    }
    else
    {
      nodos.push_back(NewNode);

      //make sure an edgelist is added for each node
      aristas.push_back(EdgeList());

      ++nextNodeIndex;
    }
  }

  //now add the edges
  stream >> NumEdges;
  for (int e=0; e<NumEdges; ++e)
  {
    Edge nextEdge(stream);

    addEdge(nextEdge);
  }

  return true;
}
*/
