#include <irrlicht.h>
#include <Box2D/Box2D.h>
#include "include/Enemigo.h"
#include "include/Player.h"
#include "include/World.h"
#include <iostream>

#define SCREENWIDTH 1280
#define SCREENHEIGHT 720

using namespace irr;    //Espacio de nombres principal
using namespace core;   //Proposito general
using namespace scene;  //Escena 3D
using namespace video;  //Driver y rendering
using namespace io;     //Ficheros
using namespace gui;    //Interfaz de usuario

int main(){

    ///BOX2D
    //class World* world; no se por que puse class
    World* world;
    world = World::Instance();

    //Objeto principal que nos permite interactuar con el motor
    IrrlichtDevice *device= createDevice(video::EDT_SOFTWARE, dimension2d<u32>(SCREENWIDTH, SCREENHEIGHT), 16, false, false, false, 0);

    ITimer* timer = device->getTimer();
    f32 TimeStamp = timer->getTime();
    f32 DeltaTime = timer->getTime() - TimeStamp;




    if(!device){
        //std::cout << "no existe\n";
        return 1;
    }

    ISceneManager* smgr= device->getSceneManager();         //Gestion de la escena
    IVideoDriver* driver= device->getVideoDriver();         //Ciclo del juego
    IGUIEnvironment* guienv= device->getGUIEnvironment();   //Interfaz de usuario
    //std::cout << "1\n";

    ///PLAYER
    Player *prota= new Player;
    if(prota){
        prota->inicializar(smgr,driver);

    }

    smgr->addCameraSceneNode(0, vector3df(0, 30, -40), vector3df(0, 5, 0)); //Camara

    //Ciclo del juego
    while(device->run()){
        driver->beginScene(true, true, SColor(255, 100, 101, 140));

        //Dibujar contenido
        guienv->addStaticText(L"Hola mundo", rect<s32>(10, 10, 260, 22));

        DeltaTime = timer->getTime() - TimeStamp;
        TimeStamp = timer->getTime();

        //std::cout << "static constructor\n";
        world->Step(DeltaTime);
        world->getWorld()->ClearForces();
        //std::cout << "nigg\n";
        smgr->drawAll();
        guienv->drawAll();
        driver->endScene();
        //std::cout << "yep\n";
    }

    device->drop();

    return 0;
}
