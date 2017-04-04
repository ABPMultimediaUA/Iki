#include "Enemies/Path/PathFinding.h"

PathFinding::PathFinding(SparseGraph* graf, Player* play)
{
    grafo = graf;
    player=play;
}

PathFinding::~PathFinding()
{
    //dtor
}
bool PathFinding::crearPath(Structs::TPosicion partida,Structs::TPosicion destino, std::list<int>& path){
    //Buscar nodos cercanos a partida y a destino
    int desde = grafo->nodeMoreClose(partida);
    //std::cout<<"NodoPartida: "<<desde<<std::endl;
    int hasta = grafo->nodeMoreClose(destino);
    //std::cout<<"NodoDestino: "<<hasta<<std::endl;
    //std::cout<<"Posicion Partida: "<<partida.X<<","<<partida.Z<<std::endl;
    //std::cout<<"Posicion Destino: "<<destino.X<<","<<destino.Z<<std::endl;
    //std::cout<<"Devuelve: "<<player->isPathObstructured(destino)<<std::endl;
    if(!player->isPathObstructured(destino)){
            return true;
    }
    algo= new Algoritmo(*grafo,desde,hasta);
    path=algo->GetPathToTarget();
    if(!path.empty())
        return true;
    else
        return false;
}

