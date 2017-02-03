#include "Map.h"


Map::Map()
{

    muros = new vector<MapComponent*>();
    puertas = new vector<MapComponent*>();
    palancas = new vector<MapComponent*>();
    objetos = new vector<MapComponent*>();

}



void Map::loadMap(scene::ISceneManager* smgr)
{

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

    float x;
    float z;
    float r;
    while (objectGroup)
    {

        //Paredes
        if (objectGroup->Attribute("name", "Pared"))
        {
            if (objectGroup->FirstChildElement("object"))
            {
                object = objectGroup->FirstChildElement("object");


                while (object)
                {
                    object->QueryFloatAttribute("x", &z);
                    object->QueryFloatAttribute("y", &x);
                    object->QueryFloatAttribute("rotation", &r);
                    muros->push_back(new MapComponent(r, core::vector3df(x, 0, z), smgr, 1));
                    object = object->NextSiblingElement("object");
                }



            }
        }

        else if (objectGroup->Attribute("name", "Puertas"))
        {
            if (objectGroup->FirstChildElement("object"))
            {
                object = objectGroup->FirstChildElement("object");


                while (object)
                {
                    object->QueryFloatAttribute("x", &z);
                    object->QueryFloatAttribute("y", &x);
                    object->QueryFloatAttribute("rotation", &r);
                    puertas->push_back(new MapComponent(r, core::vector3df(x, 0, z), smgr, 2));
                    object = object->NextSiblingElement("object");
                }



            }
        }

        else if (objectGroup->Attribute("name", "Palancas"))
        {
            if (objectGroup->FirstChildElement("object"))
            {
                object = objectGroup->FirstChildElement("object");


                while (object)
                {
                    object->QueryFloatAttribute("x", &z);
                    object->QueryFloatAttribute("y", &x);
                    object->QueryFloatAttribute("rotation", &r);
                    palancas->push_back(new MapComponent(r, core::vector3df(x, 0, z), smgr, 3));
                    object = object->NextSiblingElement("object");
                }



            }
        }

        else if (objectGroup->Attribute("name", "Objetos"))
        {
            if (objectGroup->FirstChildElement("object"))
            {
                object = objectGroup->FirstChildElement("object");


                while (object)
                {
                    object->QueryFloatAttribute("x", &z);
                    object->QueryFloatAttribute("y", &x);
                    object->QueryFloatAttribute("rotation", &r);
                    objetos->push_back(new MapComponent(r, core::vector3df(x, 0, z), smgr, 4));
                    object = object->NextSiblingElement("object");
                }



            }
        }








        objectGroup = objectGroup->NextSiblingElement("objectgroup");

    }



}

