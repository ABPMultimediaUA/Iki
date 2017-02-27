#include "PathPlanner.h"

PathPlanner::PathPlanner(Enemigo* owner, SparseGraph* graf):enemigo(owner)
    //,grafo(enemigo->GetWorld()->GetMap()->GetNavGraph())
{
    grafo=graf;
}

PathPlanner::~PathPlanner()
{
    //dtor
}

bool PathPlanner::crearPath(irr::core::vector3df destino, std::list<PathEdge>& path){

    posicionDestino=destino;
    //Si no hay muros entre el punto de partida y el punto de destino, devuelvo el path directamente con el punto de partida y destino
    //Comprobamos si el bot puede moverse directamente al objetivo con
    //un metodo que tomo como comienzo la posicion dedestino y un radio de
    //la entidad y depermina si el bot es capaz de moverse entre las dos posiciones
    if(enemigo->isPathObstructured(posicionDestino)){
            //create an edge connecting the bot's current position and the
            //target position and push it on the path list (flagged to use the
            //"normal" behavior = 1)
            path.push_back(PathEdge(enemigo->getPosicion(), posicionDestino,1));
            return true;
    }
    //encontar el nodo mas cercano a la posicion del bot, getclosesnode es un metodo
    //que consulta el grafo de navegacion de nodos para determinar el mas cercano no obstruido
    int NodoMasCercano=grafo->nodeMoreClose(enemigo->getPosicion());
    //Si ningun nodo visible se encuentra, devolvemos false, esto ocurrira si
    //el grafo esta mal diseñado o si el bot esta bugeado o algo
    if(NodoMasCercano == -1){
        return false;
    }
     //Buscamos el nodo mas cercano a la posicion de destino
     int NodoMasCercanoToTarget=grafo->nodeMoreClose(posicionDestino);
     //devolvemos false si hay un problema al localizar el nodo visible
     if(NodoMasCercanoToTarget == -1){
        return false;
     }
     Algoritmo alg(*grafo,NodoMasCercano,NodoMasCercanoToTarget);
     //cogemos el path
     //grab the path as a list of PathEdges
     path = alg.GetPathAsPathEdges();
     if(!path.empty()){
     path.push_front(PathEdge(enemigo->getPosicion(), path.front().getSource(),1));
     path.push_back(PathEdge(path.back().getDestination(),posicionDestino,1));
     return true;
     }
     else{
        //no path found by the search
        return false;
     }
}
 void PathPlanner::ConvertIndicesToVectors(std::list<int> pNodos, std::list<vector3df> &path){

    std::list<int>::iterator it;
    it = pNodos.begin();
    while( it != pNodos.end())
    {
        path.push_back(grafo->getNode(*it).posicion);
        it++;
    }
 }
///ASI FUNCIONA
/*
1. Grab the source position of E1.
2. Grab the destination position of E2.
3. If the agent can move between these two positions unobstructed by
the world geometry, assign the destination of E1 to that of E2 and
remove E2 from the path. Reassign E2 to the new edge following E1.
(Note that this is not a simple line-of-sight test as an entity’s size must
be taken into consideration— it must be able to move between the
two positions without bumping into any walls.)
4. If the agent cannot move unobstructed between the two positions,
assign E2 to E1 and advance E2.
5. Repeat steps until the destination of E2 is equal to the destination of
the path.
*/
void PathPlanner::SmoothPathEdgesQuick(std::list<PathEdge>& path)
{
    //creo una pareja de iteradores y apunto al incio del path
    std::list<PathEdge>::iterator e1(path.begin()), e2(path.begin());
    //increment e2 so it points to the edge following e1.
    ++e2;
    //while e2 is not the last edge in the path, step through the edges, checking
    //to see if the agent can move without obstruction from the source node of
    //e1 to the destination node of e2. If the agent can move between those
    //positions then the two edges are replaced with a single edge.
    while (e2 != path.end())
    {
        //check for obstruction, adjust and remove the edges accordingly
        if ( enemigo->canWalkBetween(e1->getSource(), e2->getDestination()) )
        {
            e1->SetDestination(e2->getDestination());
            e2 = path.erase(e2);
        }
        else
        {
            e1 = e2;
            ++e2;
        }
    }
}
void PathPlanner::SmoothPathEdgesPrecise(std::list<PathEdge>& path)
{
   /* //create a couple of iterators
    std::list<PathEdge>::iterator e1, e2;
    //point e1 to the beginning of the path
    e1 = path.begin();
    while (e1 != path.end())
    {
        //point e2 at the edge immediately following e1
        e2 = e1;
        ++e2;
        //while e2 is not the last edge in the path, step through the edges,
        //checking to see if the agent can move without obstruction from the
        //source node of e1 to the destination node of e2. If the agent can move
        //between those positions then any edges between e1 and e2 are
        //replaced with a single edge.
        while (e2 != path.end())
        {
            //check for obstruction, adjust and remove the edges accordingly
            if ( m_pOwner->canWalkBetween(e1->Source(), e2->Destination()) )
            {
                e1->SetDestination(e2->Destination());
                e2 = path.erase(++e1, ++e2);
                e1 = e2;
                --e1;
            }
            else
            {
                ++e2;
            }
        }
        ++e1;
    }*/
}
