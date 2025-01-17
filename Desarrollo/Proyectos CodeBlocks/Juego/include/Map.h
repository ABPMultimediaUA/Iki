#ifndef MAP_H
#define MAP_H

#pragma once
#include <vector>
#include "tinyxml2.h"

#include "Structs.h"
#include "PatrolPoint.h"
#include "Fachada/MeshSceneNode.h"
#include "Enemies/Path/SparseGraph.h"
#include "Enemies/Path/Edge.h"
#include "Enemies/Path/Nodo.h"
#include "Muros.h"

#include "Fachada/AnimatedMesh.h"

using namespace tinyxml2;
using namespace std;

class Nodo;

class Map
{
    public:
        Map();
        ~Map();
        void crearComponente();
        void inicializar_mapa(int);
        void inicializar_muros();
        void cleanMap();

        vector<Muros*>       getMuros()        { return muros; }
        vector<PatrolPoint*> getPatrullas()    { return patrullas; }
        vector<int>          getTiposEnemigos(){ return tipos; }
        SparseGraph*         getGrafo()        { return Grafo; }


    protected:

    private:

        MeshSceneNode* primera_sala;
        MeshSceneNode* segunda_sala;
        MeshSceneNode* tercera_sala;
        MeshSceneNode* suelo;

        vector<MapComponent*> nodo_muro;
        vector<Muros*> muros;
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

        Nodo node;
        Edge edge;
        SparseGraph* Grafo;
        std::vector<int> fila;
        std::vector<std::vector<int>> conectaCon;
        float coste;
        int indice;


};

#endif // MAP_H
