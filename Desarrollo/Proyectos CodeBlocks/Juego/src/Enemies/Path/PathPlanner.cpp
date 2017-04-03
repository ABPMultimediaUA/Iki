#include "Enemies/Path/PathPlanner.h"

bool PathPlanner::crearPath(Structs::TPosicion destino, std::list<PathEdge>& path){

    posicionDestino=destino;
    //Si no hay muros entre el punto de partida y el punto de destino, devuelvo el path directamente con el punto de partida y destino
    //Comprobamos si el bot puede moverse directamente al objetivo con
    //un metodo que tomo como comienzo la posicion dedestino y un radio de
    //la entidad y depermina si el bot es capaz de moverse entre las dos posiciones
    if(!propietario->isPathObstructured(posicionDestino)){
            path.push_back(PathEdge(propietario->getPosition(), posicionDestino,1));
            return true;
    }
    //encontar el nodo mas cercano a la posicion del bot, getclosesnode es un metodo
    //que consulta el grafo de navegacion de nodos para determinar el mas cercano no obstruido
    int NodoMasCercano=grafo->nodeMoreClose(propietario->getPosition());
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
     path = alg.GetPathAsPathEdges();
     if(!path.empty()){
         path.push_front(PathEdge(propietario->getPosition(), path.front().getSource(),1));
         path.push_back(PathEdge(path.back().getDestination(),posicionDestino,1));
         SmoothPathEdgesQuick(path);
         return true;
     }
     else{
        return false;
     }
}
void PathPlanner::ConvertIndicesToVectors(std::list<int> pNodos, std::list<Structs::TPosicion> &path){

    std::list<int>::iterator it;
    it = pNodos.begin();
    while( it != pNodos.end())
    {
        path.push_back(grafo->getNode(*it).posicion);
        it++;
    }
}

void PathPlanner::SmoothPathEdgesQuick(std::list<PathEdge>& path)
{
    bool entro = false;
    //create a couple of iterators and point them at the front of the path
    std::list<PathEdge>::iterator e1 = path.begin();
    std::list<PathEdge>::iterator e2 = path.begin();
    //increment e2 so it points to the edge following e1.
    ++e2;
    //while e2 is not the last edge in the path, step through the edges, checking
    //to see if the agent can move without obstruction from the source node of
    //e1 to the destination node of e2. If the agent can move between those
    //positions then the two edges are replaced with a single edge.
    while (e2 != path.end())
    {
        //check for obstruction, adjust and remove the edges accordingly
        if ( propietario->canWalkBetween(e1->getSource(), e2->getDestination()) )
        {
            entro=true;
            e1->SetDestination(e2->getDestination());
            e2 = path.erase(e2);
        }
        else
        {
            entro=false;
            e1 = e2;
            ++e2;
        }
    }
}
void PathPlanner::SmoothPathEdgesPrecise(std::list<PathEdge>& path)
{
    //create a couple of iterators
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
            if ( propietario->canWalkBetween(e1->getSource(), e2->getDestination()) )
            {
                e1->SetDestination(e2->getDestination());
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
    }
}



