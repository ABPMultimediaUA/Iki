#include <irrlicht.h>
#include <Box2D/Box2D.h>
#include "include/Enemigo.h"
#include "include/Player.h"
#include "include/World.h"
#include "Muros.h"
#include <iostream>

#define SCREENWIDTH 1280
#define SCREENHEIGHT 720


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
    MyEventReceiver receiver;
    float posx, posy, posz;
    vector3df posmuro;

    //Objeto principal que nos permite interactuar con el motor
    IrrlichtDevice *device= createDevice(video::EDT_SOFTWARE, dimension2d<u32>(SCREENWIDTH, SCREENHEIGHT), 16, false, false, false, &receiver);

    ITimer* timer = device->getTimer();
    f32 TimeStamp = timer->getTime();
    f32 DeltaTime = timer->getTime() - TimeStamp;

    ISceneManager* smgr= device->getSceneManager();         //Gestion de la escena
    IVideoDriver* driver= device->getVideoDriver();         //Ciclo del juego
    IGUIEnvironment* guienv= device->getGUIEnvironment();   //Interfaz de usuario



    ///CAMARA
    ICameraSceneNode * camera = smgr->addCameraSceneNode(0,core::vector3df(0, 300,-90),core::vector3df(0,0,0));

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


    //std::cout << "1\n";

    ///PLAYER
    Player *prota= new Player;
    if(prota){
        prota->inicializar(smgr,driver);

    }
    ///MUROS
    Muros *muro1= new Muros;
    if(muro1){
        muro1->inicializar(smgr, driver);
    }
    ///raton
    core::plane3df plane(prota->getCuboProta(), core::vector3df(0, -1, 0));
    core::vector3df mousePosition= core::vector3df(0,0,0);
    core::line3df ray(mousePosition, prota->getCuboProta());



    //Ciclo del juego
    while(device->run()){
       driver->beginScene(true, true, SColor(255, 100, 101, 140));

        ///raton
        if(receiver.GetMouseState().RightButtonDown)
        {
            ray = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(
                      receiver.GetMouseState().Position, camera);
            float angulo = atan2f((mousePosition.Z-prota->getModelo()->getPosition().Z) ,
                        -(mousePosition.X-prota->getModelo()->getPosition().X)) * 180.f / irr::core::PI;
            prota->getBody()->SetTransform(prota->getBody()->GetPosition(), angulo);
            prota->getModelo()->setRotation(core::vector3df(0,prota->getBody()->GetAngle(),0));
        }
        if(plane.getIntersectionWithLine(ray.start, ray.getVector(), mousePosition))
        {
            // We now have a mouse position in 3d space; move towards it.
            core::vector3df toMousePosition(mousePosition - prota->getCuboProta());
            if(toMousePosition.getLength() <= 1)
                prota->moverBody(vector3df(0,0,0));
            else
                prota->moverBody(toMousePosition);
        }

        //importante para cambiar posicion de body
//prota->moverBody(mousePosition);
        prota->setPosition(vector3df(prota->getBody()->GetPosition().x, 0, prota->getBody()->GetPosition().y));
        //enemi->setPosition(vector3df(enemi->getBody()->GetPosition().x, 0, enemi->getBody()->GetPosition().y));
        //prota->setPosicionBody(0);

        ///CAMARA
         if(receiver.isKeyDown(KEY_ESCAPE))
        {
            device->closeDevice();
            return 0;
        }
        else if(receiver.isKeyDown(KEY_RIGHT))
        {
            cameraPos.X+=0.4;
            cameraTar.X+=0.4;
        }
        else if (receiver.isKeyDown(KEY_LEFT))
        {
            cameraPos.X-=0.4;
            cameraTar.X-=0.4;
        }
        else if(receiver.isKeyDown(KEY_UP))
        {
            cameraPos.Z+=0.4;
            cameraTar.Z+=0.4;
        }
        else if (receiver.isKeyDown(KEY_DOWN))
        {
            cameraPos.Z-=0.4;
            cameraTar.Z-=0.4;
        }

        camera->setPosition(cameraPos);
        camera->setTarget(cameraTar);

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
