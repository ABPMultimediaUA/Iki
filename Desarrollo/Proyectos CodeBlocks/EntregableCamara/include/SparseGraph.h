#ifndef SPARSEGRAPH
#define SPARSEGRAPH

#include <irrlicht.h>
#include <enemigo.h>
#include <Nodo.h>
#include <Edge.h>


template<class node_type, class edge_type>
class SparseGraph
{
    public:
        //permite el facil acceso dek cliente a los tipos de edges y nodos utilizados en el grafo
        typedef edge_type EdgeType;
        typedef node_type NodeType;
        //mas typedefs utiles
        typedef std::vector<node_type> NodeVector;
        typedef list<edge_type> EdgeList;
        typedef std::vector<EdgeList> EdgeListVector;

        SparseGraph(bool diagraph):nextNodeIndex(0),bDiagraph(diagraph){}

        //Metodos con const y sin el?
        const NodeType& getNode(int idx)const;
        NodeType& getNode(int idx);
        const EdgeType& getEdge(int form, int to)const;
        EdgeType& getEdge(int form, int to);

        int getNextNodeIndex()const;
        int addNode(NodeType node);
        void removeNode(int node);
        void addEdge(EdgeType edge);
        void removeEdge(int form,int to);
        int numNodes()const;
        int numActiveNodes()const;
        int numEdges()const;
        bool isDigraph()const;
        bool isEmpty()const;
        bool isPresent(int idx)const;//devuelve true su el nodo que nos dan esta presente en el grafo

        //Metodos para cargar y guardar un grafo desde una archivo o desde un nombre de archivo
        bool save(const char* FileName)const;
        bool save(std::ofstream& stream)const;
        bool load(const char** FileName);
        bool Load(std::ifstream& stream);

        void clear();
            //iteradores clientes pueden utilizar para tener acceso a nodos y bordes
        class ConstEdgeIterator;
        class EdgeIterator;
        class NodeIterator;
        class ConstNodeIterator;





    protected:

    private:
        NodeVector nodos;//Los nodos que componen el grafo
        EdgeListVector aristas;//Un vector con la lista de aristas de proximidad ( cada nodo tiene un indice en la lista de aristas asociadas con ese nodo )
        bool bDiagraph;//Si es un grafo directo
        int nextNodeIndex;//el indice del siguiente nodo en ser anyadido
};

#endif // SPARSEGRAPH
