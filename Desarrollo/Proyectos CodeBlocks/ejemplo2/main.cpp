/** Example 019 Mouse and Joystick

This tutorial builds on example 04.Movement which showed how to
handle keyboard events in Irrlicht.  Here we'll handle mouse events
and joystick events, if you have a joystick connected and a device
that supports joysticks.  These are currently Windows, Linux and SDL
devices.
*/

#ifdef _MSC_VER

// We'll define this to stop MSVC complaining about sprintf().
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "Irrlicht.lib")
#endif

#include <irrlicht.h>
#include <Box2D.h>
#include "driverChoice.h"
#include "include/Enemigo.h"

//#include <../libBox2D/Box2D.h>
//#include <../libBox2D/Common/b2Math.h>

using namespace irr;

using namespace core; //namespace fundamentales;
using namespace scene; //namespace de escena;
using namespace video; //namespace de vídeo;
using namespace io; //namespace io;
using namespace gui; //namespace gui;
/*
we'll store the latest state of the mouse and the first joystick, updating them as we receive events.
*/
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
        bool LeftButtonDown;
        SMouseState() : LeftButtonDown(false) { }
    } MouseState;

    // This is the one method that we have to implement
    virtual bool OnEvent(const SEvent& event)
    {
        // Remember the mouse state
        if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
        {
            switch(event.MouseInput.Event)
            {
            case EMIE_LMOUSE_PRESSED_DOWN:
                MouseState.LeftButtonDown = true;
                break;

            case EMIE_LMOUSE_LEFT_UP:
                MouseState.LeftButtonDown = false;
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

/*
The event receiver for keeping the pressed keys is ready, the actual responses
will be made inside the render loop, right before drawing the scene. So lets
just create an irr::IrrlichtDevice and the scene node we want to move. We also
create some other additional scene nodes, to show that there are also some
different possibilities to move and animate scene nodes.
*/

int main()
{
    // ask user for driver
    video::E_DRIVER_TYPE driverType=driverChoiceConsole();
    if (driverType==video::EDT_COUNT)
        return 1;

    // create device
    MyEventReceiver receiver;

    Enemigo *enemigo1 = new Enemigo;


    IrrlichtDevice* device = createDevice(driverType,core::dimension2d<u32>(1080, 720), 16, false, false, false, &receiver);
    IGUIEnvironment* guienv = device->getGUIEnvironment(); //Cargamos la GUI

    device->setWindowCaption(L"IKI" );
    //guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",rect<s32>(10,10,10,10), true );

    if (device == 0)
        return 1; // could not create selected driver.

    video::IVideoDriver* driver = device->getVideoDriver();
    scene::ISceneManager* smgr = device->getSceneManager();
    scene::IMeshSceneNode *prota = smgr->addCubeSceneNode(5);

    /// MUROS////////////
    scene::IMeshSceneNode *muro1 = smgr->addCubeSceneNode(10);
        muro1->setMaterialFlag(video::EMF_LIGHTING, false);
        muro1->setPosition(core::vector3df(0,0,0));
        muro1->setPosition(core::vector3df(10,0,0));
        smgr->getMeshManipulator()->setVertexColors(muro1->getMesh(),irr::video::SColor(0, 0, 0, 0));


    /// ////////////////

    //IBillboardSceneNode *node1 = scenedriver->addBillboardSceneNode ( 0, core::dimension2d< f32 >(100.0f, 100.0f) );
    //node1->setMaterialFlag(EMF_LIGHTING, false);

    //node1->setMaterialTexture( 0, videodriver->getTexture("texturas/opengl.png") );
    //node1->setMaterialType( video::EMT_SOLID );

    bool protaColliding = false;

    if(prota)
    {
        prota->setMaterialFlag(video::EMF_LIGHTING, false);
        prota->setPosition(core::vector3df(0,0,0));
    }
    if(enemigo1)
    {
        enemigo1->inicialiazar(0, smgr);
    }
    core::vector3df posicionInicial (35,0,35);
    //enemigo1.setPunto((prota->getPosition())-(enemigo->getPosition()));

    scene::ICameraSceneNode * camera = smgr->addCameraSceneNode(0,core::vector3df(0,90,-40),core::vector3df(0,0,0));

    //we'll use framerate independent movement.
    u32 then = device->getTimer()->getTime();
    const f32 MOVEMENT_SPEED = 25.f;
    const f32 MOVEMENT_SPEED_ENEMY = 15.f;
    core::line3df ray;
    core::vector3df mousePosition;

    //cambio de color de mallas
    smgr->getMeshManipulator()->setVertexColors(enemigo1->getModelo()->getMesh(),irr::video::SColor(255, 255, 0, 0));

    while(device->run())
    {

        // Work out a frame delta time.
        const u32 now = device->getTimer()->getTime();
        const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
        then = now;

        core::vector3df cameraPos = camera->getPosition();
        core::vector3df cameraTar = camera->getTarget();

        core::vector3df cuboProta = prota->getPosition();
        //core::vector3df cuboEnemigo = enemy->getPosition();
        core::vector3df direccionProta (cuboProta-enemigo1->getCuboEnemigo());

        core::plane3df plane(cuboProta, core::vector3df(0, -1, 0));

        core::vector3df direccionProta2 (cuboProta-cameraPos);


        /// COLISIONES ///
        if(prota->getTransformedBoundingBox().intersectsWithBox(muro1->getTransformedBoundingBox())){
            //std::cout<< "si" <<std::endl;
            protaColliding = true;
        }
        else{
            //std::cout<< "no" <<std::endl;
            protaColliding = false;
        }


        /// ////////////////////

        const f32 availableMovement = MOVEMENT_SPEED * frameDeltaTime;

        if(receiver.isKeyDown(KEY_ESCAPE))
        {
            device->closeDevice();
            return 0;
        }
        else if(receiver.isKeyDown(KEY_RIGHT))
        {
            cameraPos.X+=0.1;
            cameraTar.X+=0.1;
        }
        else if (receiver.isKeyDown(KEY_LEFT))
        {
            cameraPos.X-=0.1;
            cameraTar.X-=0.1;
        }
        else if(receiver.isKeyDown(KEY_UP))
        {
            cameraPos.Z+=0.1;
            cameraTar.Z+=0.1;
        }
        else if (receiver.isKeyDown(KEY_DOWN))
        {
            cameraPos.Z-=0.1;
            cameraTar.Z-=0.1;
        }
        if(receiver.GetMouseState().LeftButtonDown)
        {
            ray = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(
                      receiver.GetMouseState().Position, camera);

        }
        if(plane.getIntersectionWithLine(ray.start, ray.getVector(), mousePosition))
        {
            // We now have a mouse position in 3d space; move towards it.
            core::vector3df toMousePosition(mousePosition - cuboProta);
            const f32 availableMovement = MOVEMENT_SPEED * frameDeltaTime;

            int protaX = mousePosition.X;
            int protaZ = mousePosition.Z;


            if (!protaColliding){
            /// SI NO COLISIONA SE MOVERA EN LINEA RECTA HASTA QUE COLISIONE

                if(toMousePosition.getLength() <= availableMovement){
                    cuboProta = mousePosition; // Jump to the final position
                }else{
                    cuboProta += toMousePosition.normalize() * availableMovement; // Move towards i
                    //Para que la camara siga al prota
                    //cameraPos += toMousePosition.normalize() *availableMovement;
                    //cameraTar += toMousePosition.normalize() *availableMovement;

                }
            }else{
            /// COLISIONA Y PRIORIZA UNA DIRECCION

                core::vector3df redireccion;
                int pX =1, pZ = 1;

                if (protaX < 0){ protaX*=-1; pX = -1; }
                if (protaZ < 0){ protaZ*=-1; pZ = -1; }

                if (protaX > protaZ)
                    redireccion.set(0,0,pZ);
                else
                    redireccion.set(pX,0,0);

                cuboProta += redireccion * availableMovement;

            }

        //std::cout<< "Prota X = " << protaX << "__ Prota Z = " << protaZ <<std::endl;

        }

        enemigo1->update(direccionProta, cuboProta, frameDeltaTime);

        prota->setPosition(cuboProta);
        enemigo1->getModelo()->setPosition(enemigo1->getCuboEnemigo());
        camera->setPosition(cameraPos);
        camera->setTarget(cameraTar);

        driver->beginScene(true, true, video::SColor(255,113,113,133));
        smgr->drawAll(); // draw the 3d scene
        driver->endScene();
    }

    /*
    In the end, delete the Irrlicht device.
    */
    device->drop();

    return 0;
}

/*
**/
