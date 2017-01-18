#include "Map.h"





Map::Map()
{

walls = new array<MapComponent*>();

}



void Map::loadMap(scene::ISceneManager* smgr){

	docFile = new XMLDocument; //Se crea el objeto del documento

	docFile->LoadFile("BosquePrueba.tmx"); //Se carga el archivo xml

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
	while (objectGroup) {

		//Paredes
		if (objectGroup->Attribute("name", "Pared")) {
			if (objectGroup->FirstChildElement("object")) {
				object = objectGroup->FirstChildElement("object");


				while (object) {
					object->QueryFloatAttribute("x", &x);
					object->QueryFloatAttribute("y", &z);
					walls->push_back(new MapComponent(core::vector3df(_width, 1, _height), core::vector3df(x, 0, z), smgr));
					object = object->NextSiblingElement("object");
				}



			}
		}







		objectGroup = objectGroup->NextSiblingElement("objectgroup");

	}


}

