#include "Fachada/MeshSceneNode.h"
#include "Fachada/GraphicsFacade.h"

MeshSceneNode::MeshSceneNode(Structs::TMedida medida, Structs::TPosicion posicion, Structs::TColor color)
{
    //mesh = GraphicsFacade::getInstance().smgr->getGeometryCreator()->createCubeMesh(vector3df(medida.ancho, medida.alto, medida.profundo));
    /*node = GraphicsFacade::getInstance().smgr->addMeshSceneNode(mesh);

    node->setPosition(core::vector3df(posicion.X, posicion.Y, posicion.Z));
    GraphicsFacade::getInstance().smgr->getMeshManipulator()->setVertexColors(node->getMesh(),irr::video::SColor(color.opacity, color.r, color.g, color.b));
    node->setMaterialFlag(video::EMF_LIGHTING, false);*/
}

MeshSceneNode::MeshSceneNode(const std::string &file){
    node = GraphicsFacade::getInstance().motor->crearMalla(file);

    /*GraphicsFacade::getInstance().smgr->getMeshManipulator()->setVertexColors(node->getMesh(),irr::video::SColor(color.opacity, color.r, color.g, color.b));
    node->setMaterialFlag(video::EMF_LIGHTING, false);*/
}

MeshSceneNode::~MeshSceneNode()
{
    //dtor
}

void MeshSceneNode::setPosition(Structs::TPosicion pos){
    node->Trasladar(TVector(pos.X,pos.Y,pos.Z));
}

void MeshSceneNode::setRotation(float rot){
    node->Rotar(rot);
}

void MeshSceneNode::setScale(Structs::TMedida scale){
    node->EscalarRel(TVector(scale.alto,scale.ancho,scale.profundo));
}

void MeshSceneNode::setVisible(bool visible){
    //node->setVisible(visible);
}
