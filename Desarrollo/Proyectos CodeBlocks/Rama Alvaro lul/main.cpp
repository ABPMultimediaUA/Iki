#include <irrlicht.h>
#include <Box2D/Box2D.h>
#include "include/Enemigo.h"
#include "include/Objeto.h"
#include <irrKlang.h>
#include "irrKlang/conio.h"
#include <iostream>
#include "include/Map.h"

#include "include/PatrolRoute.h"

#define SCREENWIDTH 1280
#define SCREENHEIGHT 720


using namespace irr;    //Espacio de nombres principal
using namespace irrklang; //Para los sonidos creo

using namespace core;   //Proposito general
using namespace scene;  //Escena 3D
using namespace video;  //Driver y rendering
using namespace io;     //Ficheros
using namespace gui;    //Interfaz de usuario



class MyEventReceiver : public IEventReceiver
{
private:
    bool KeyDown[KEY_KEY_CODES_COUNT];
public:

    MyEventReceiver()
    {
        for(int i=0; i<KEY_KEY_CODES_COUNT; i++)
        {
            KeyDown[i] = false;
        }
    }

    struct SMouseState
    {
        core::position2di Position;
        bool RightButtonDown, LeftButtonDown= false;
        SMouseState() : RightButtonDown(false) { }
    } MouseState;

    // This is the one method that we have to implement
    virtual bool OnEvent(const SEvent& event)
    {
        // Remember the mouse state
        if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
        {
            switch(event.MouseInput.Event)
            {
            case EMIE_RMOUSE_PRESSED_DOWN:
                MouseState.RightButtonDown = true;
                break;

            case EMIE_LMOUSE_PRESSED_DOWN:
                MouseState.LeftButtonDown= true;
                break;

            case EMIE_RMOUSE_LEFT_UP:
                MouseState.RightButtonDown = false;
                break;

            case EMIE_LMOUSE_LEFT_UP:
                MouseState.LeftButtonDown= false;
                break;

            case EMIE_MOUSE_MOVED:
                MouseState.Position.X = event.MouseInput.X;
                MouseState.Position.Y = event.MouseInput.Y;
                break;

            default:
                // We won't use the wheel
                break;
            }
        }
        else if (event.EventType == irr::EET_KEY_INPUT_EVENT)
        {
            KeyDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
        }

    }

    virtual bool isKeyDown(EKEY_CODE keyCode) const
    {
        return KeyDown[keyCode];
    }

    virtual bool isKeyUp(EKEY_CODE keyCode) const
    {
        return !KeyDown[keyCode];
    }
    const SMouseState & GetMouseState(void) const
    {
        return MouseState;
    }


};




int main(){


    MyEventReceiver receiver;
    float posx, posy, posz;
    vector3df posmuro;

    video::E_DRIVER_TYPE driverType=driverChoiceConsole();
    if (driverType==video::EDT_COUNT)
        return 1;

    //Objeto principal que nos permite interactuar con el motor
    IrrlichtDevice* device = createDevice(driverType,core::dimension2d<u32>(1080, 720), 16, false, false, false, &receiver);
    device->setWindowCaption(L"IKI" );
    ITimer* timer = device->getTimer();
    f32 TimeStamp = timer->getTime();
    f32 DeltaTime = timer->getTime() - TimeStamp;

    ISceneManager* smgr= device->getSceneManager();         //Gestion de la escena
    IVideoDriver* driver= device->getVideoDriver();         //Ciclo del juego
    IGUIEnvironment* guienv= device->getGUIEnvironment();   //Interfaz de usuario



    ///CAMARA
    ICameraSceneNode * camera = smgr->addCameraSceneNode(0,core::vector3df(0, 40, -20),core::vector3df(0,0,0));

    vector3df cameraPos = camera->getPosition();
    vector3df cameraTar = camera->getTarget();


    ///BOX2D
    //class World* world; no se por que puse class
    World* world;
    world = World::Instance();

    if(!device){
        //std::cout << "no existe\n";
        return 1;
    }


    ///PLAYER
    Player *prota= new Player;
    if(prota){
        prota->inicializar(smgr,driver);

    }








    Map *Mapa= new Map;
    if(Mapa){
        Mapa->loadMap(smgr);

    }




    ///RATON
    core::plane3df plane(prota->getCuboProta(), core::vector3df(0, -1, 0));
    core::vector3df mousePosition= core::vector3df(0,0,0);
    core::line3df ray(mousePosition, prota->getCuboProta());
    core::line3df ray2(mousePosition, prota->getCuboProta());
    core::line3df ray3(mousePosition, prota->getCuboProta());





    ///CICLO DEL JUEGO

    while(device->run()){
       driver->beginScene(true, true, SColor(255, 100, 101, 140));





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
