#include "SceneNode.h"
#include "GraphicsFacade.h"
#include "World.h"

SceneNode::SceneNode(float tam, Structs::TPosicion posicionInicial)
{
    node = GraphicsFacade::getInstance().smgr->addCubeSceneNode(tam);
    node->setPosition(vector3df(posicionInicial.X, posicionInicial.Y, posicionInicial.Z));
    position = posicionInicial;
}

SceneNode::~SceneNode()
{
    //dtor
}

Structs::TPosicion SceneNode::getPosition(){
    return position;
}

void SceneNode::setPosition(Structs::TPosicion posicionNueva){
    node->setPosition(vector3df(posicionNueva.X, posicionNueva.Y, posicionNueva.Z));
    position = posicionNueva;
}

void SceneNode::setRotation(float angulo){
    node->setRotation(vector3df(0,angulo,0));
}

void SceneNode::cambiarColor(Structs::TColor color){
    std::cout << "Opacidad: " << color.opacity << std::endl;
    node->setMaterialFlag(video::EMF_LIGHTING, false);
    GraphicsFacade::getInstance().smgr->getMeshManipulator()->setVertexColors(node->getMesh(), SColor(color.opacity, color.r, color.g, color.b));
}
