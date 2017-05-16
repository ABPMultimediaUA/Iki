#include "Fachada/MeshSceneNode.h"
#include "Fachada/GraphicsFacade.h"

MeshSceneNode::MeshSceneNode(Structs::TMedida medida, Structs::TPosicion posicion, Structs::TColor color)
{
    mesh = GraphicsFacade::getInstance().smgr->getGeometryCreator()->createCubeMesh(vector3df(medida.ancho, medida.alto, medida.profundo));
    node = GraphicsFacade::getInstance().smgr->addMeshSceneNode(mesh);

    node->setPosition(core::vector3df(posicion.X, posicion.Y, posicion.Z));
    GraphicsFacade::getInstance().smgr->getMeshManipulator()->setVertexColors(node->getMesh(),irr::video::SColor(color.opacity, color.r, color.g, color.b));
    node->setMaterialFlag(video::EMF_LIGHTING, false);
}

MeshSceneNode::MeshSceneNode(const char* file)
{
    mesh = GraphicsFacade::getInstance().smgr->getMesh(file);
    node = GraphicsFacade::getInstance().smgr->addMeshSceneNode(mesh);
    //node->setPosition(vector3df(168.5, 0, 56.5));

    GraphicsFacade::getInstance().smgr->getMeshManipulator()->setVertexColors(node->getMesh(),irr::video::SColor(0,255,255,255));
    node->setMaterialFlag(video::EMF_LIGHTING, false);
}

MeshSceneNode::~MeshSceneNode()
{
    //dtor
}

void MeshSceneNode::setPosition(Structs::TPosicion pos){
    node->setPosition(vector3df(pos.X, pos.Y, pos.Z));
}

void MeshSceneNode::setRotation(float rot){
    node->setRotation(vector3df(0, rot, 0));
}

void MeshSceneNode::setScale(Structs::TMedida scale){
    node->setScale(vector3df(scale.ancho, scale.alto, scale.profundo));
}

void MeshSceneNode::setVisible(bool visible){
    node->setVisible(visible);
}

void MeshSceneNode::setTexture(const char* file){
    node->setMaterialTexture( 0, GraphicsFacade::getInstance().driver->getTexture(file) );
    node->setMaterialType( video::EMT_SOLID );
}

void MeshSceneNode::cambiarColor(Structs::TColor color){
    //std::cout << "Opacidad: " << color.opacity << std::endl;
    GraphicsFacade::getInstance().smgr->getMeshManipulator()->setVertexColors(node->getMesh(), SColor(color.opacity, color.r, color.g, color.b));
}
