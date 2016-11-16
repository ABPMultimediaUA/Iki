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
#include "driverChoice.h"

using namespace irr;

/*
we'll store the latest state of the mouse and the first joystick, updating them as we receive events.
*/
class MyEventReceiver : public IEventReceiver
{
public:
    // We'll create a struct to record info on the mouse state
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

    }

    const SMouseState & GetMouseState(void) const
    {
        return MouseState;
    }


    MyEventReceiver()
    {
    }

};

/*
The event receiver for keeping the pressed keys is ready, the actual responses
will be made inside the render loop, right before drawing the scene. So lets
just create an irr::IrrlichtDevice and the scene node we want to move. We also
create some other additional scene nodes, to show that there are also some
different possibilities to move and animate scene nodes.
*/
class Enemigo
{
public:
    // We'll create a struct to NPCs
    struct SEnemy
    {
        core::position2di Position;
        char estado;

    } enemy;
    void inicialiazar()
    {

    }
    void patrullar()
    {

    }
    void sospechar()
    {
    }
    void atacar()
    {
    }
    void maquinaEstados()
    {
        switch (enemy.estado)
        {
        case 'p':
            patrullar();
            /*if(condicion de la transicion 1-2){
            //acciones de la transicion 1-2
            //...
            estado = "estado2";
            }
            */
            break;
        case 's':
            sospechar();
            /*
            if(condicion de la transicion2-1){
                //acciones de la transicion2-1
                //...
                this.estado = "estado1";
            }else if(condicion de la transicion2-fin) {
                //acciones de la transicion2-1
                //...
                estado = null;
                this.onEnterFrame = null;
            }
            */
            break;
        case 'a':
            atacar();
            break;

        }
    }

};

int main()
{
    // ask user for driver
    video::E_DRIVER_TYPE driverType=driverChoiceConsole();
    if (driverType==video::EDT_COUNT)
        return 1;

    // create device
    MyEventReceiver receiver;

    IrrlichtDevice* device = createDevice(driverType,core::dimension2d<u32>(640, 480), 16, false, false, false, &receiver);

    if (device == 0)
        return 1; // could not create selected driver.

    video::IVideoDriver* driver = device->getVideoDriver();
    scene::ISceneManager* smgr = device->getSceneManager();
    scene::IMeshSceneNode *prota = smgr->addCubeSceneNode(10);
    scene::IMeshSceneNode *enemigo = smgr->addCubeSceneNode(10);

    if(prota)
    {
        prota->setMaterialFlag(video::EMF_LIGHTING, false);
        prota->setPosition(core::vector3df(5,15,5));
    }
    if(enemigo)
    {
        enemigo->setMaterialFlag(video::EMF_LIGHTING, false);
        enemigo->setPosition(core::vector3df(35,15,35));
    }

    scene::ICameraSceneNode * camera = smgr->addCameraSceneNode(0,core::vector3df(0,90,0),core::vector3df(0,0,0));

    //we'll use framerate independent movement.
    u32 then = device->getTimer()->getTime();
    const f32 MOVEMENT_SPEED = 25.f;
    const f32 MOVEMENT_SPEED_ENEMY = 15.f;

    //cambio de color de mallas
    smgr->getMeshManipulator()->setVertexColors(enemigo->getMesh(),irr::video::SColor(255, 255, 0, 0));

    while(device->run())
    {
        // Work out a frame delta time.
        const u32 now = device->getTimer()->getTime();
        const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
        then = now;


        core::vector3df nodePosition = prota->getPosition();
        core::vector3df nodePosition2 = enemigo->getPosition();
        core::vector3df direccionProta (nodePosition-nodePosition2);


        // Create a ray through the mouse cursor.
        if(receiver.GetMouseState().LeftButtonDown)
        {
            core::line3df ray = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(
                                    receiver.GetMouseState().Position, camera);

            // And intersect the ray with a plane around the node facing towards the camera.
            core::plane3df plane(nodePosition, core::vector3df(0, -1, 0));
            core::vector3df mousePosition;

            if(plane.getIntersectionWithLine(ray.start, ray.getVector(), mousePosition))
            {
                // We now have a mouse position in 3d space; move towards it.
                core::vector3df toMousePosition(mousePosition - nodePosition);
                const f32 availableMovement = MOVEMENT_SPEED * frameDeltaTime;

                if(toMousePosition.getLength() <= availableMovement)
                    nodePosition = mousePosition; // Jump to the final position
                else
                    nodePosition += toMousePosition.normalize() * availableMovement; // Move towards it
            }

        }
        if(enemigo)
        {
            const f32 availableMovement = MOVEMENT_SPEED_ENEMY * frameDeltaTime;
            nodePosition2 += direccionProta.normalize()*availableMovement;
        }

        prota->setPosition(nodePosition);
        enemigo->setPosition(nodePosition2);


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
