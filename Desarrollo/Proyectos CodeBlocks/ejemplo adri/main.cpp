#include <irrlicht.h>
#include <Box2D/Box2D.h>
#include "include/Enemigo.h"
#include "include/Player.h"
#include "include/World.h"
#include <iostream>

#define SCREENWIDTH 1280
#define SCREENHEIGHT 720
#define frameDeltaTime 1.0f / 250.0f

using namespace irr;    //Espacio de nombres principal
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
        bool RightButtonDown;
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

            case EMIE_RMOUSE_LEFT_UP:
                MouseState.RightButtonDown = false;
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
    Enemigo *enemi= new Enemigo;
    if(enemi){
        enemi->inicializar(smgr,driver);

    }

    Player *prota= new Player;
    if(prota){
        prota->inicializar(smgr,driver);

    }
    f32 MOVEMENT_SPEED = 25.f;
    core::vector3df mousePosition = core::vector3df(40,0,0);
    core::line3df ray(mousePosition, prota->getCuboProta());
    MyEventReceiver receiver;

    smgr->addCameraSceneNode(0, vector3df(0, 30, -40), vector3df(0, 5, 0)); //Camara

    //Ciclo del juego
    while(device->run()){
        driver->beginScene(true, true, SColor(255, 100, 101, 140));
        if(receiver.isKeyDown(KEY_LSHIFT))
            MOVEMENT_SPEED = 15.f;
        else
            MOVEMENT_SPEED = 25.f;

        const f32 availableMovement = MOVEMENT_SPEED * frameDeltaTime;
        core::vector3df toMousePosition(mousePosition - prota->getCuboProta());

        int protaX = mousePosition.X;
        int protaZ = mousePosition.Z;

        prota->setCuboProta(prota->getCuboProta() + toMousePosition.normalize() * availableMovement);


        //Dibujar contenido
        guienv->addStaticText(L"Hola mundo", rect<s32>(10, 10, 260, 22));

        prota->getModelo()->setPosition(prota->getCuboProta());
        //importante para cambiar posicion de body
        prota->setPosition(vector3df(prota->getBody()->GetPosition().x, 0, prota->getBody()->GetPosition().y));
        prota->setPosicionBody(0);


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
