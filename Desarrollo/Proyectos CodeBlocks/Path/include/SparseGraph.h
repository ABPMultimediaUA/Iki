#ifndef SPARSEGRAPH
#define SPARSEGRAPH

#include <irrlicht.h>
#include <Nodo.h>
#include <Edge.h>
#include <list>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cassert>
#include <string>
//#include <iomanip>



//template<class node_type, class edge_type>
class SparseGraph
{
    public:
        //permite el facil acceso dek cliente a los tipos de edges y nodos utilizados en el grafo
        //typedef edge_type EdgeType;
        //typedef node_type NodeType;*
        //mas typedefs utiles
        typedef std::vector<Nodo> NodeVector;
        typedef std::list<Edge> EdgeList;
        typedef std::vector<EdgeList> EdgeListVector;

        //constructor
        SparseGraph(bool diagraph):nextNodeIndex(0),bDiagraph(diagraph){}

        //Metodos con const y sin el?
        const Nodo& getNode(int idx)const;
        Nodo& getNode(int idx);
        const Edge& getEdge(int from, int to)const;
        Edge& getEdge(int from, int to);

        int getNextNodeIndex()const;
        int addNode(Nodo node);
        void removeNode(int node);
        void addEdge(Edge edge);
        void removeEdge(int form,int to);
        int numNodes()const;
        int numActiveNodes()const;
        int numEdges()const;
        bool isDigraph()const;
        bool isEmpty()const;
        bool isNodePresent(int idx)const;//devuelve true su el nodo que nos dan esta presente en el grafo
        bool isEdgePresent(int from, int to)const;
        //-------------------------- SetEdgeCost ---------------------------------
        //
        //  Sets the cost of a specific edge
        //------------------------------------------------------------------------
        void setEdgeCost(int from, int to, double NewCost);

        ///Metodos para cargar y guardar un grafo desde una archivo o desde un nombre de archivo
        bool save(const char* FileName)const;
        bool save(std::ofstream& stream)const;
        bool load(const char* FileName);
        bool load(std::ifstream& stream);

        void clear(){nextNodeIndex = 0; nodos.clear(); aristas.clear();}
        void RemoveEdges()
          {
            for (EdgeListVector::iterator it = aristas.begin(); it != aristas.end(); ++it)
            {
              it->clear();
            }
          }
        //PENDIENTES
        class NodeIterator;
        class ConstNodeIterator;

    protected:

    private:
        std::list<Edge>::iterator it;
        //std::list<const Edge>::iterator const_it;
        EdgeList lista;
        NodeVector nodos;//Los nodos que componen el grafo
        EdgeListVector aristas;//Un vector con la lista de aristas de proximidad ( cada nodo tiene un indice en la lista de aristas asociadas con ese nodo )
        bool bDiagraph;//Si es un grafo directo
        int nextNodeIndex;//el indice del siguiente nodo en ser anyadido

        bool  UniqueEdge(int from, int to)const; // devuelve true si el edge no esta presente en el graph, usado al anyadir para evitar duplicaciones
        //iterates through all the edges in the graph and removes any that point
        //to an invalidated node
        void  CullInvalidEdges();

    public:
                  ///ITERADORES
        //iteradores clientes pueden utilizar para tener acceso a nodos y aristas
        //const class used to iterate through all the edges connected to a specific node.
      class ConstEdgeIterator
      {
      private:

        typename EdgeList::const_iterator        curEdge;

        const SparseGraph& G;

        const int                                NodeIndex;

      public:

        ConstEdgeIterator(const SparseGraph& graph,
                          int                           node): G(graph),
                                                               NodeIndex(node)
        {
          /* we don't need to check for an invalid node index since if the node is
             invalid there will be no associated edges
         */

          curEdge = G.aristas[NodeIndex].begin();
        }

        const Edge*  begin()
        {
          curEdge = G.aristas[NodeIndex].begin();

		  if (end()) return 0;

          return &(*curEdge);
        }

        const Edge*  next()
        {
          ++curEdge;

		  if(end())
		  {
			  return NULL;
		  }
		  else
		  {
			return &(*curEdge);
		  }

        }

        //return true if we are at the end of the edge list
        bool end()
        {
          return (curEdge == G.aristas[NodeIndex].end());
        }
      };

  friend class ConstEdgeIterator;
        //non const class used to iterate through all the edges connected to a specific node.
        class EdgeIterator
        {
        private:

            typename EdgeList::iterator         curEdge;

            SparseGraph&  G;

            const int                           NodeIndex;

        public:

            EdgeIterator(SparseGraph& graph,int node): G(graph),NodeIndex(node)
            {
                /* we don't need to check for an invalid node index since if the node is
                   invalid there will be no associated edges
                */

                curEdge = G.aristas[NodeIndex].begin();
            }

            Edge*  begin()
            {
                curEdge = G.aristas[NodeIndex].begin();

                return &(*curEdge);
            }

            Edge*  next()
            {
                ++curEdge;

                if (end()) return NULL;

                return &(*curEdge);

            }

        //return true if we are at the end of the edge list
            bool end()
            {
                return (curEdge == G.aristas[NodeIndex].end());
            }
        };
        friend class EdgeIterator;
};

#endif // SPARSEGRAPH
