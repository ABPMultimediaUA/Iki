#include "Map.h"

Map::Map()
{

}

Map::~Map()
{

}

void Map::inicializar_mapa(){

    Structs::TMedida med = {150,-5,150};
    Structs::TPosicion pos = {0,0,0};
    Structs::TColor col = {0,255,255,255};

    suelo = new MeshSceneNode(med, pos, col);

}
