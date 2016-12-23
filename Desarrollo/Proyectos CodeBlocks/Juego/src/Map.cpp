#include "Map.h"

Map::Map()
{

}

Map::~Map()
{

}

void Map::inicializar_mapa(ISceneManager* smgr){

    mesh = smgr->getGeometryCreator()->createCubeMesh(vector3df(150.f, -5.f, 150.f));
    suelo = smgr->addMeshSceneNode(mesh);

    suelo->setPosition(core::vector3df(0.0f, 0.0f, 0.0f));
    smgr->getMeshManipulator()->setVertexColors(suelo->getMesh(),irr::video::SColor(0, 0, 0, 0));
}
