#ifndef MAP_H
#define MAP_H

#pragma once
#include <vector>
#include "tinyxml2.h"

#include "Structs.h"
#include "PatrolPoint.h"
#include "Fachada/MeshSceneNode.h"

using namespace tinyxml2;
using namespace std;

class MapComponent;

class Map
{
    public:
        Map();
        ~Map();
        void crearComponente(int tipo);
        void inicializar_mapa();

        vector<PatrolPoint*> getPatrullas() { return patrullas; }
        vector<int>          getTipos()     { return tipos;     }

    protected:

    private:

        MeshSceneNode *suelo;

        vector<MapComponent*> muros;
        vector<PatrolPoint*>  patrullas;
        vector<int>           tipos;

        tinyxml2::XMLDocument* docFile;
        tinyxml2::XMLElement* mapElement;
        tinyxml2::XMLElement* objectGroup;
        tinyxml2::XMLElement* object;
        tinyxml2::XMLElement* property;

        int _width;
        int _tileWidth;
        int _height;
        int _tileHeigth;

};

#endif // MAP_H
