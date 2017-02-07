#pragma once
#include <stdio.h>
#include "tinyxml2.h"
#include "MapComponent.h"


using namespace tinyxml2;

class Map
{
public:

	Map();
	void loadMap(scene::ISceneManager*);
	void update();
	void render(float interpolation);

private:

	tinyxml2::XMLDocument* docFile;
	tinyxml2::XMLElement* mapElement;
	tinyxml2::XMLElement* objectGroup;
	tinyxml2::XMLElement* object;
	int _width;
	int _tileWidth;
	int _height;
	int _tileHeigth;
	irr::core::array<MapComponent*> * walls;
	irr::core::array<MapComponent*> * puertas;



};

