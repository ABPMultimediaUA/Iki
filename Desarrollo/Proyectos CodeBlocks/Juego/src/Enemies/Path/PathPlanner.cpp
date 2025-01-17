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
    //el grafo esta mal dise�ado o si el bot esta bugeado o algo
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
    std::list<PathEdge>::iterator e1 = path.begin();
    std::list<PathEdge>::iterator e2 = path.begin();
    ++e2;
    while (e2 != path.end())
    {
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
    std::list<PathEdge>::iterator e1, e2;
    e1 = path.begin();
    while (e1 != path.end())
    {
        e2 = e1;
        ++e2;

        while (e2 != path.end())
        {
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



