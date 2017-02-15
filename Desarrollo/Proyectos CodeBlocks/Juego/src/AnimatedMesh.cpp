#include "AnimatedMesh.h"
#include "GraphicsFacade.h"

AnimatedMesh::AnimatedMesh(const char* file, Structs::TColor color, Structs::TPosicion posicion, float rotacion)
{
    mesh = GraphicsFacade::getInstance().smgr->getMesh(file);
    modelo = GraphicsFacade::getInstance().smgr->addAnimatedMeshSceneNode(mesh);
    GraphicsFacade::getInstance().smgr->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(color.opacity, color.r, color.g, color.b));

    modelo->setPosition(vector3df(posicion.X, posicion.Y, posicion.Z));
    modelo->setRotation(vector3df(0, rotacion, 0));
    modelo->setMaterialFlag(video::EMF_LIGHTING, false);
}

AnimatedMesh::~AnimatedMesh()
{
    //dtor
}
