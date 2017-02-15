#include "PathFinding.h"

PathFinding::PathFinding(SparseGraph* graf)
{
    grafo = graf;
   // player=owner;
    //ctor
}

PathFinding::~PathFinding()
{
    //dtor
}
bool PathFinding::crearPath(irr::core::vector3df partida,irr::core::vector3df destino, std::list<int>& path){
    //Buscar nodos cercanos a partida y a destino
    //std::cout<<"Posicion PartidaPath: "<<partida.X<<","<<partida.Z<<std::endl;
    int desde = grafo->nodeMoreClose(partida);
    std::cout<<"NodoPartida: "<<desde<<std::endl;
    int hasta = grafo->nodeMoreClose(destino);
    std::cout<<"NodoDestino: "<<hasta<<std::endl;
    algo= new Algoritmo(*grafo,desde,hasta);
    path=algo->GetPathToTarget();
}

