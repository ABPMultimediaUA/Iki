#include "MeshSceneNode.h"
#include "GraphicsFacade.h"

MeshSceneNode::MeshSceneNode(Structs::TMedida medida, Structs::TPosicion posicion, Structs::TColor color)
{
    mesh = GraphicsFacade::getInstance().smgr->getGeometryCreator()->createCubeMesh(vector3df(medida.ancho, medida.alto, medida.profundo));
    node = GraphicsFacade::getInstance().smgr->addMeshSceneNode(mesh);

    node->setPosition(core::vector3df(posicion.X, posicion.Y, posicion.Z));
    GraphicsFacade::getInstance().smgr->getMeshManipulator()->setVertexColors(node->getMesh(),irr::video::SColor(color.opacity, color.r, color.g, color.b));
    node->setMaterialFlag(video::EMF_LIGHTING, false);
}

MeshSceneNode::~MeshSceneNode()
{
    //dtor
}
