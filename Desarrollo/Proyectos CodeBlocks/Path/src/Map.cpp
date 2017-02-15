#include "Map.h"


Map::Map()
{

    muros = new vector<MapComponent*>();
    puertas = new vector<MapComponent*>();
    palancas = new vector<MapComponent*>();
    objetos = new vector<MapComponent*>();
    apisonadoras = new vector<MapComponent*>();
    patrullas = new vector<MapComponent*>();
    NavGraph = new SparseGraph(true);
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
    //std::string c;
    const char * c;
    int n;
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

        else if (objectGroup->Attribute("name", "Apisonadora"))
        {
            if (objectGroup->FirstChildElement("object"))
            {
                object = objectGroup->FirstChildElement("object");


                while (object)
                {
                    object->QueryFloatAttribute("x", &z);
                    object->QueryFloatAttribute("y", &x);
                    object->QueryFloatAttribute("rotation", &r);
                    apisonadoras->push_back(new MapComponent(r, core::vector3df(x, 0, z), smgr, 5));
                    object = object->NextSiblingElement("object");
                }



            }
        }

        else if (objectGroup->Attribute("name", "Patrol"))
        {
            if (objectGroup->FirstChildElement("object"))
            {
                object = objectGroup->FirstChildElement("object");


                while (object)
                {
                    object->QueryFloatAttribute("x", &z);
                    object->QueryFloatAttribute("y", &x);
                    object->QueryFloatAttribute("rotation", &r);
                    patrullas->push_back(new MapComponent(r, core::vector3df(x, 0, z), smgr, 6));
                    object = object->NextSiblingElement("object");
                }

            }
        }
       else if (objectGroup->Attribute("name", "WayPoints"))
        {
           if (objectGroup->FirstChildElement("object"))
            {

                object = objectGroup->FirstChildElement("object");


                while (object)
                {


                    object->QueryAttribute("name", &n);
                    object->QueryFloatAttribute("x", &z);
                    object->QueryFloatAttribute("y", &x);
                    if(object->FirstChildElement("properties")->FirstChildElement("property")){
                    property = object->FirstChildElement("properties")->FirstChildElement("property");
                    c = property->Attribute("value");
                    // std::cout<<"nombre"<<n<<std::endl;
                    }
                    node.setIndex((int)n);
                    node.posicion= irr::core::vector3df(x,0,z);
                    char * str = (char*)c; //cambio un const char a char
                    char * pch;
                    pch = strtok (str,",");   // Separar por la coma
                    NavGraph->addNode(node);
                    fila.clear();
                    while (pch != NULL)
                    {
                        int num = atoi(pch);
                        fila.push_back(num);
                        //cout<<"Este: "<<n<<"conecta con este: "<<fila.back()<<endl;
                        pch = strtok (NULL,",");
                    }
                    conectaCon.push_back(fila);
                    object = object->NextSiblingElement("object");
                }
                 cout<<"Numero de Nodos Totales "<<NavGraph->numNodes()<<endl;

                for (int i=0; i < conectaCon.size();i++){
                    for(int j=0; j < conectaCon[i].size();j++){
                        if(i!=conectaCon[i][j]){
                            //cout<<"Este: "<<i<<" conecta con este: "<<conectaCon[i][j]<<endl;
                            coste=NavGraph->getNode(i).calcularCoste(NavGraph->getNode(conectaCon[i][j]));
                            edge.setFrom(i);
                            edge.setTo(conectaCon[i][j]);
                            edge.setCost(coste);
                            NavGraph->addEdge(edge);
                        }
                    }
                }
            }
        }

        objectGroup = objectGroup->NextSiblingElement("objectgroup");

    }



}


