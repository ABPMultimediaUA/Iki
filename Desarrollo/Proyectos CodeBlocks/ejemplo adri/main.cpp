#include <irrlicht.h>
#include <Box2D/Box2D.h>

#define SCREENWIDTH 1280
#define SCREENHEIGHT 720

using namespace irr;    //Espacio de nombres principal
using namespace core;   //Proposito general
using namespace scene;  //Escena 3D
using namespace video;  //Driver y rendering
using namespace io;     //Ficheros
using namespace gui;    //Interfaz de usuario


struct cubo{
    cubo(ISceneManager* smgr, int tam, vector3df pos){
        cubeNode = smgr->addCubeSceneNode(tam);
        cubeNode->setPosition(pos);
        smgr->getMeshManipulator()->setVertexColors(cubeNode->getMesh(), SColor(255, rand()%255, rand()%255, rand()%255));
    }
    IMeshSceneNode* cubeNode;
    b2Body *body;
};

//Creamos el mundo y la gravedad de este
b2Vect2 gravity;
gravity.Set(0, -10);
b2World *world= new b2World(gravity);



















int main(){
    //Objeto principal que nos permite interactuar con el motor
    IrrlichtDevice *device= createDevice(video::EDT_SOFTWARE, dimension2d<u32>(SCREENWIDTH, SCREENHEIGHT), 16, false, false, false, 0);

    if(!device){
        return 1;
    }

    ISceneManager* smgr= device->getSceneManager();         //Gestion de la escena
    IVideoDriver* driver= device->getVideoDriver();         //Ciclo del juego
    IGUIEnvironment* guienv= device->getGUIEnvironment();   //Interfaz de usuario


    smgr->addCameraSceneNode(0, vector3df(0, 30, -40), vector3df(0, 5, 0)); //Camara

    if(cubo){
    }

    //Ciclo del juego
    while(device->run()){
        driver->beginScene(true, true, SColor(255, 100, 101, 140));

        //Dibujar contenido
        guienv->addStaticText(L"Hola mundo", rect<s32>(10, 10, 260, 22));

        smgr->drawAll();
        guienv->drawAll();

        driver->endScene();
    }

    device->drop();

    return 0;
}
