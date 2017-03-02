#include "Map.h"
#include "MapComponent.h"

Map::Map()
{
//    muros = new vector<MapComponent*>();
//    puertas = new vector<MapComponent*>();
//    palancas = new vector<MapComponent*>();
//    objetos = new vector<MapComponent*>();
//    apisonadoras = new vector<MapComponent*>();
    //patrullas = new vector<MapComponent*>();
}

Map::~Map()
{

}

void Map::crearComponente(int tipo){

    float x, z, r;
    Structs::TPosicion pos;
    if (objectGroup->FirstChildElement("object")){

        object = objectGroup->FirstChildElement("object");

        while (object){
            object->QueryFloatAttribute("x", &z);
            object->QueryFloatAttribute("y", &x);
            pos = {x,0,z};
            object->QueryFloatAttribute("rotation", &r);
            muros.push_back(new MapComponent(r, pos, tipo));
            object = object->NextSiblingElement("object");
        }
    }
}

void Map::inicializar_mapa(){

    Structs::TMedida med = {600,-5,600};
    Structs::TPosicion pos = {0,0,0};
    Structs::TColor col = {0,255,255,255};
    int cont = 0;

    suelo = new MeshSceneNode(med, pos, col);

    docFile = new XMLDocument; //Se crea el objeto del documento

    docFile->LoadFile("Mapas/Mapa.tmx"); //Se carga el archivo xml

    mapElement = docFile->FirstChildElement("map"); //Se enlaza el elemento mapa

    //Se leen sus atributos y se almacenan
    mapElement->QueryIntAttribute("width", &_width);
    mapElement->QueryIntAttribute("height", &_height);
    mapElement->QueryIntAttribute("tilewidth", &_tileWidth);
    mapElement->QueryIntAttribute("tileheight", &_tileHeigth);

    //Pasamos a leer los ObjectGroups
    objectGroup = mapElement->FirstChildElement("objectgroup");

    while (objectGroup){

        float x, z;
        int c = 0, c2 = 0, n = 0;

        //Paredes
        if      (objectGroup->Attribute("name", "Pared"))      crearComponente(1);
        //else if (objectGroup->Attribute("name", "Puertas"))    crearComponente(2);
        //else if (objectGroup->Attribute("name", "Palancas"))   crearComponente(3);
        //else if (objectGroup->Attribute("name", "Objetos"))    crearComponente(4);
        //else if (objectGroup->Attribute("name", "Apisonadora"))crearComponente(5);

        else if (objectGroup->Attribute("name", "Patrol"))
        {
            if (objectGroup->FirstChildElement("object"))
            {
                object = objectGroup->FirstChildElement("object");


                while (object)
                {

                    object->QueryFloatAttribute("x", &z);
                    object->QueryFloatAttribute("y", &x);
                    pos.X = x;
                    pos.Z = z;
                    property = object->FirstChildElement("properties")->FirstChildElement("property");
                    while (property){
                        if(property->Attribute("name", "Enemigo"))
                            c = atoi(property->Attribute("value"));
                        if(property->Attribute("name", "Next"))
                            n = atoi(property->Attribute("value"));
                        if(property->Attribute("name", "Tipo"))
                            tipos.push_back(atoi(property->Attribute("value")));
                        property = property->NextSiblingElement("property");
                    }
                    if(c == c2)
                        cont++;
                    else{
                        cont = 1;
                        c2 = c;
                    }

                    patrullas.push_back(new PatrolPoint(c,cont,n,pos));

                    object = object->NextSiblingElement("object");
                }



            }
        }

        objectGroup = objectGroup->NextSiblingElement("objectgroup");
    }

}
