#pragma once
#include <stdio.h>
#include "tinyxml2.h"
#include "MapComponent.h"



using namespace tinyxml2;
using namespace std;

class Map
{
public:

    Map();
    void loadMap(scene::ISceneManager*);
    void update();
    void render(float interpolation);
    vector<MapComponent*> * muros;
    vector<MapComponent*> * puertas;
    vector<MapComponent*> * objetos;
    vector<MapComponent*> * palancas;
    vector<MapComponent*> * apisonadoras;
    vector<MapComponent*> * patrullas;



private:

    tinyxml2::XMLDocument* docFile;
    tinyxml2::XMLElement* mapElement;
    tinyxml2::XMLElement* objectGroup;
    tinyxml2::XMLElement* object;
    int _width;
    int _tileWidth;
    int _height;
    int _tileHeigth;



};

