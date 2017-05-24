#include "Fachada/Animaciones.h"
#include "Fachada/GraphicsFacade.h"
#include <string>
#include <sstream>


Animaciones::Animaciones(std::string file, Structs::TColor color, Structs::TPosicion p, float r,float frames,float inicio,const char* t, float scale)
{
    for(int i =inicio; i< inicio+frames; i++){


        std::string s;          // string which will contain the result
        std::ostringstream convert;   // stream used for the conversion
        convert << i;      // insert the textual representation of 'Number' in the characters in the stream
        s = convert.str();

        std::string str = file + s + ".obj";
        std::cout << str <<std::endl;
        mesh = GraphicsFacade::getInstance().smgr->getMesh(str.c_str());
        modelo = GraphicsFacade::getInstance().smgr->addAnimatedMeshSceneNode(mesh);
        //GraphicsFacade::getInstance().smgr->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(color.opacity, color.r, color.g, color.b));
        posicion = p;
        rotacion = r;

        modelo->setPosition(vector3df(posicion.X+5, 10, posicion.Z));

        modelo->setRotation(vector3df(0, r, 0));
        modelo->setMaterialFlag(video::EMF_LIGHTING, false);

        modelo->setMaterialTexture( 0, GraphicsFacade::getInstance().getDriver()->getTexture(t) );
        modelo->setMaterialType( video::EMT_SOLID );

        modelo->setScale(vector3df(scale, scale, scale));
        modelo->setVisible(false);

        modelos.push_back(modelo);
    }
    actual=modelos[0];
    actual->setVisible(true);
}

Animaciones::~Animaciones()
{
    Clear();
}

void Animaciones::setVisible(bool visible){
    modelo->setVisible(visible);
}
void Animaciones::setPosition(Structs::TPosicion pos){
    posicion = pos;
    actual->setPosition(vector3df(pos.X+5, 10, pos.Z));
}

void Animaciones::setRotation(float rot){
    rotacion = 90+rot;
    actual->setRotation(vector3df(0, 90+rot, 0));
}
void Animaciones::setRotationXYZ(float x, float y,float z){
    actual->setRotation(vector3df(x,y,z));
}

void Animaciones::setScale(Structs::TMedida scale){
    modelo->setScale(vector3df(scale.ancho, scale.alto, scale.profundo));
}
void Animaciones::setScale(float scale){
    modelo->setScale(vector3df(scale, scale, scale));
}
void Animaciones::cambiarColor(Structs::TColor color){
    //std::cout << "Opacidad: " << color.opacity << std::endl;
    GraphicsFacade::getInstance().smgr->getMeshManipulator()->setVertexColors(modelo->getMesh(), SColor(color.opacity, color.r, color.g, color.b));
}
void Animaciones::setTexture(const char* file){
    modelo->setMaterialTexture( 0, GraphicsFacade::getInstance().getDriver()->getTexture(file) );
    modelo->setMaterialType( video::EMT_SOLID );
}
void Animaciones::Clear(){
    std::vector<IAnimatedMeshSceneNode*>::iterator curTrg;
    for (curTrg = modelos.begin(); curTrg != modelos.end(); ++curTrg)
    {
        *curTrg = nullptr;;
    }

    modelos.clear();
    mesh = nullptr;
    modelo = nullptr;
    actual = nullptr;
}

