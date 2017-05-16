#include "Fachada/AnimatedMesh.h"
#include "Fachada/GraphicsFacade.h"

AnimatedMesh::AnimatedMesh(const char* file, Structs::TColor color, Structs::TPosicion p, float r)
{
    mesh = GraphicsFacade::getInstance().smgr->getMesh(file);
    modelo = GraphicsFacade::getInstance().smgr->addAnimatedMeshSceneNode(mesh);
    GraphicsFacade::getInstance().smgr->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(color.opacity, color.r, color.g, color.b));
    posicion = p;
    rotacion = r;
    modelo->setPosition(vector3df(posicion.X, posicion.Y, posicion.Z));
    modelo->setRotation(vector3df(0, rotacion, 0));
    modelo->setMaterialFlag(video::EMF_LIGHTING, false);
}

AnimatedMesh::~AnimatedMesh()
{
    //dtor
}

void AnimatedMesh::setVisible(bool visible){
    modelo->setVisible(visible);
}
void AnimatedMesh::setPosition(Structs::TPosicion pos){
    modelo->setPosition(vector3df(pos.X, pos.Y, pos.Z));
}

void AnimatedMesh::setRotation(float rot){
    modelo->setRotation(vector3df(0, rot, 0));
}
void AnimatedMesh::setRotationXYZ(float x, float y,float z){
    modelo->setRotation(vector3df(x,y,z));
}

void AnimatedMesh::setScale(Structs::TMedida scale){
    modelo->setScale(vector3df(scale.ancho, scale.alto, scale.profundo));
}
void AnimatedMesh::setScale(float scale){
    modelo->setScale(vector3df(scale, scale, scale));
}
void AnimatedMesh::cambiarColor(Structs::TColor color){
    //std::cout << "Opacidad: " << color.opacity << std::endl;
    GraphicsFacade::getInstance().smgr->getMeshManipulator()->setVertexColors(modelo->getMesh(), SColor(color.opacity, color.r, color.g, color.b));
}
void AnimatedMesh::setTexture(const char* file){
    modelo->setMaterialTexture( 0, GraphicsFacade::getInstance().driver->getTexture(file) );
    modelo->setMaterialType( video::EMT_SOLID );
}
