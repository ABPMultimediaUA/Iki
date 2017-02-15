#pragma once
#include <stdio.h>
#include "tinyxml2.h"
#include "MapComponent.h"
#include "Nodo.h"
#include "Edge.h"
#include "SparseGraph.h"


using namespace tinyxml2;
using namespace std;

class Map
{
public:

    Map();
    void loadMap(scene::ISceneManager*);
    void update();
    void render(float interpolation);
    std::vector<MapComponent*> * muros;
    std::vector<MapComponent*> * puertas;
    std::vector<MapComponent*> * objetos;
    std::vector<MapComponent*> * palancas;
    std::vector<MapComponent*> * apisonadoras;
    std::vector<MapComponent*> * patrullas;
    //std::vector<Nodo> nodos;
    std::vector<int> fila;
    std::vector<std::vector<int>> conectaCon;
    SparseGraph* getNavGraph(){return NavGraph;}


private:

    tinyxml2::XMLDocument* docFile;
    tinyxml2::XMLElement* mapElement;
    tinyxml2::XMLElement* objectGroup;
    tinyxml2::XMLElement* object;
    tinyxml2::XMLElement* property;
    int _width;
    int _tileWidth;
    int _height;
    int _tileHeigth;
    float coste;
    int indice;
    Nodo node;
    Edge edge;
    SparseGraph * NavGraph;



};

