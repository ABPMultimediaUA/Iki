#include "Map.h"
#include "MapComponent.h"

Map::Map()
{
//    muros = new vector<MapComponent*>();
//    puertas = new vector<MapComponent*>();
//    palancas = new vector<MapComponent*>();
//    objetos = new vector<MapComponent*>();
//    apisonadoras = new vector<MapComponent*>();
//    patrullas = new vector<MapComponent*>();
    Grafo = new SparseGraph(true);
}

Map::~Map()
{

}

void Map::crearComponente(){

    int name;
    float x, z, r = 0;
    Structs::TPosicion pos;
    if (objectGroup->FirstChildElement("object")){

        object = objectGroup->FirstChildElement("object");

        while (object){
            object->QueryAttribute("name", &name);
            object->QueryFloatAttribute("x", &z);
            object->QueryFloatAttribute("y", &x);
            pos = {x,0,z};
            //object->QueryFloatAttribute("rotation", &r);
            if(object->FirstChildElement("properties")){
                property = object->FirstChildElement("properties")->FirstChildElement("property");
                if(property->Attribute("name", "Fin"))
                    r = atoi(property->Attribute("value"));
            }

            nodo_muro.push_back(new MapComponent(pos, name, r));
            object = object->NextSiblingElement("object");
        }
    }
}

void Map::inicializar_muros(){
    for(size_t i = 0; i < nodo_muro.size(); i++){
        if(nodo_muro[i]->getConecta() != 0){
            muros.push_back(new Muros(nodo_muro[i], nodo_muro[i+1]));
        }
    }
}

void Map::inicializar_mapa(){

    Structs::TMedida med = {600,-5,600};
    Structs::TPosicion pos(0,0,0);
    Structs::TColor col = {0,255,255,255};
    int cont = 0;

    primera_sala = new MeshSceneNode("resources/Modelos/salita1.obj");
    primera_sala->setTexture("resources/Texturas/sala1.png");
    segunda_sala = new MeshSceneNode("resources/Modelos/salita2.obj");
    segunda_sala->setTexture("resources/Texturas/sala2.png");
    tercera_sala = new MeshSceneNode("resources/Modelos/mapabueno.obj");
    tercera_sala->setTexture("resources/Texturas/mapa.png");

    //suelo = new MeshSceneNode(med, pos, col);

    docFile = new XMLDocument; //Se crea el objeto del documento

    docFile->LoadFile("resources/Mapas/Mapa3.tmx"); //Se carga el archivo xml

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
        const char * value;
        int name;

        //Paredes
        if      (objectGroup->Attribute("name", "Pared"))      crearComponente();

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
        else if (objectGroup->Attribute("name", "WayPoints"))
        {
           if (objectGroup->FirstChildElement("object"))
            {

                object = objectGroup->FirstChildElement("object");


                while (object)
                {
                    object->QueryAttribute("name", &name);
                    object->QueryFloatAttribute("x", &z);
                    object->QueryFloatAttribute("y", &x);
                    if(object->FirstChildElement("properties")->FirstChildElement("property")){
                    property = object->FirstChildElement("properties")->FirstChildElement("property");
                    value = property->Attribute("value");
                    //std::cout<<"nombre: "<<name<<std::endl;
                    }
                    node.setIndex((int)name);
                    //std::cout<<"index del nodo: "<<node.Index()<<std::endl;
                    node.posicion= Structs::TPosicion(x,0,z);
                    //std::cout<<"X: "<<node.posicion.X<<" Z: "<<node.posicion.Z<<std::endl;
                    Grafo->addNode(node);

                    char * str = (char*)value; //cambio un const char a char
                    char * pch;
                    pch = strtok (str,",");   // Separar por la coma
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
                 cout<<"Numero de Nodos Totales "<<Grafo->numNodes()<<endl;

                for (int i=0; i < conectaCon.size();i++){
                    for(int j=0; j < conectaCon[i].size();j++){
                        if(i!=conectaCon[i][j]){
                            //cout<<"Este: "<<i<<" conecta con este: "<<conectaCon[i][j]<<endl;
                            coste=Grafo->getNode(i).calcularCoste(Grafo->getNode(conectaCon[i][j]));
                            edge.setFrom(i);
                            edge.setTo(conectaCon[i][j]);
                            edge.setCost(coste);
                            Grafo->addEdge(edge);
                        }
                    }
                }
            }
        }

        objectGroup = objectGroup->NextSiblingElement("objectgroup");
    }
    inicializar_muros();

}
