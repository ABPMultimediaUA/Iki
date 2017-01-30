#include "PathPlanner.h"

PathPlanner::PathPlanner(Enemigo* owner)
{
    enemigo=owner;
    //ctor
}

PathPlanner::~PathPlanner()
{
    //dtor
}

bool PathPlanner::crearPath(irr::core::vector3df destino, list<vector3df>& path){
    posicionDestino=destino;
    //Comprobamos si el bot puede moverse directamente al objetivo con
    //un metodo que tomo como comienxo la posicion dedestino y un radio de
    //la entidad y depermina si el bot es capaz de moverse entre las dos posiciones
    ///if(!enemigo()->getWorld()->isPathObstructured(enemigo->getPosicion(),posicionDestino,enemigo->getTamanyo())){
            path.push_back(posicionDestino);
            return true;
    ///}acaba el if
    //encontar el nodo mas cercano a la posicion del bot, getclosesnode es un metodo
    //que consulta el grafo de navegacion de nodos para determinar el mas cercano no obstruido
    int NodoMasCercano=getNodoMasCercano(enemigo->getPosicion());
    //Si ningun nodo visible se encuentra, devolvemos false, esto ocurrira si
    //el grafo esta mal diseñado o si el bot esta bugeado o algo
    if(NodoMasCercano == -1){
        return false;
    }
     //Buscamos el nodo mas cercano a la posicion de destino
     int NodoMasCercanoToTarget=getNodoMasCercano(posicionDestino);
     //devolvemos false si hay un problema al localizar el nodo visible
     if(NodoMasCercanoToTarget==-1){
        return false;
     }
     //creamos una instancia de la clase de busqueda A* para buscar una ruta entre el nodo mas cercano al bot
     //y el nodo mas cercano a la posicion de destino. Esta A utilizara la heuristica lineal euclidiana
     ///typedef Graph_SearchAStar <Mapa::Grafo, Heuristic_Euclid> AStar;
     ///AStar search(Grafo,NodoMasCercano,NodoMasCercanoToTarget);
     //cogemos el path
     ///list<int> PathOfNodeIndices = search.GetPathToTarget();
     //Si la busqueda es exitosa convertimos los indices de los vectores a posiciones
     ///if(!PathOfNodeIndices.empty())
     ///ConvertIndicesToVectors(PathOfNodeIndices, path)
     //ponemos la posicion de destino al final del path
     path.push_back(posicionDestino);
     return true;
     ///acaba el if
     ///else{
      return false;
     ///}acaba el else
}

int PathPlanner::getNodoMasCercano(irr::core::vector3df){
}
