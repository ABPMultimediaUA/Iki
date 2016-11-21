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
    enum estados {patrulla, sospechar, ataca, nsnc};
    struct SEnemy
    {
        core::vector3df posicion;
        estados estado;
        float sospecha;
        core::vector3df puntoInteres;

    } enemy;

    void inicialiazar()
    {
        enemy.posicion=core::vector3df(35,0,35);
        enemy.estado=patrulla;
        enemy.sospecha=0.0;
        enemy.puntoInteres=vector3df(0,0,0);
    }
    char getEstado()
    {
        return enemy.estado;
    }
    core::vector3df getPosicion()
    {
        return enemy.posicion;
    }
    core::vector3df getPunto()
    {
        return enemy.puntoInteres;
    }
    void setPosicion(core::vector3df este)
    {
        enemy.posicion=este;
    }
    void setPunto(core::vector3df este)
    {
        enemy.puntoInteres=este;
    }
    float getSospecha(){
        return enemy.sospecha;
    }
    void patrullar()
    {

    }
    void sospecha(core::vector3df posicionProta)
    {

    }
    void atacar(core::vector3df posicionProta)
    {

    }
    int maquinaEstados(core::vector3df posicionProta)
    {
        switch (enemy.estado)
        {
        case patrulla:
            //patrullar();
            if(enemy.posicion.getDistanceFrom(posicionProta)<30){
                enemy.sospecha++;
            }
            if(enemy.sospecha>=100.0)
            {
                //acciones de la transicion 1-2
                //...
                enemy.estado =sospechar;
            }
            break;
        case sospechar:
            //sospechar(posicionProta);
           if(enemy.posicion.getDistanceFrom(enemy.puntoInteres)==0){
                if(enemy.posicion.getDistanceFrom(posicionProta)<40){
                    enemy.sospecha++;
                }
                else if(enemy.posicion.getDistanceFrom(posicionProta)>30){
                    enemy.sospecha--;
                }
           }
            if(enemy.sospecha<50.0)
            {
                //acciones de la transicion2-1
                //...
                enemy.estado = patrulla;
                enemy.sospecha=0.0;
            }
            else if(enemy.sospecha>=200.0)
            {
                //acciones de la transicion2-3
                //...
                enemy.estado =ataca;
            }
            break;
        case ataca:
            //atacar(posicionProta);
            break;
        default:
            enemy.estado=nsnc;
            break;

        }
        return enemy.estado;
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

    Enemigo enemigo1;


    IrrlichtDevice* device = createDevice(driverType,core::dimension2d<u32>(1080, 720), 16, false, false, false, &receiver);
    IGUIEnvironment* guienv = device->getGUIEnvironment(); //Cargamos la GUI

    device->setWindowCaption(L"IKI-113! - Irrlicht Engine Demo" );
    //guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",rect<s32>(10,10,10,10), true );

    int estado;
    enum direccion {arriba, derecha, abajo, izquierda};
    direccion palla;
    palla=arriba;

    if (device == 0)
        return 1; // could not create selected driver.

    video::IVideoDriver* driver = device->getVideoDriver();
    scene::ISceneManager* smgr = device->getSceneManager();
    scene::IMeshSceneNode *prota = smgr->addCubeSceneNode(5);
    scene::IMeshSceneNode *enemigo = smgr->addCubeSceneNode(5);



    if(prota)
    {
        prota->setMaterialFlag(video::EMF_LIGHTING, false);
        prota->setPosition(core::vector3df(0,0,0));
    }
    if(enemigo)
    {
        enemigo1.inicialiazar();
        enemigo->setMaterialFlag(video::EMF_LIGHTING, false);
        enemigo->setPosition(enemigo1.getPosicion());
    }
    core::vector3df posicionInicial (35,0,35);
    //enemigo1.setPunto((prota->getPosition())-(enemigo->getPosition()));

    scene::ICameraSceneNode * camera = smgr->addCameraSceneNode(0,core::vector3df(0,50,0),core::vector3df(0,0,0));

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


        core::vector3df cuboProta = prota->getPosition();
        core::vector3df cuboEnemigo = enemigo->getPosition();
        core::vector3df direccionProta (cuboProta-cuboEnemigo);



        // Create a ray through the mouse cursor.
        if(receiver.GetMouseState().LeftButtonDown)
        {
            core::line3df ray = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(
                                    receiver.GetMouseState().Position, camera);

            // And intersect the ray with a plane around the node facing towards the camera.
            core::plane3df plane(cuboProta, core::vector3df(0, -1, 0));
            core::vector3df mousePosition;

            if(plane.getIntersectionWithLine(ray.start, ray.getVector(), mousePosition))
            {
                // We now have a mouse position in 3d space; move towards it.
                core::vector3df toMousePosition(mousePosition - cuboProta);
                const f32 availableMovement = MOVEMENT_SPEED * frameDeltaTime;

                if(toMousePosition.getLength() <= availableMovement)
                    cuboProta = mousePosition; // Jump to the final position
                else
                    cuboProta += toMousePosition.normalize() * availableMovement; // Move towards it
            }
        }
        if(enemigo)
        {
            const f32 availableMovement = MOVEMENT_SPEED_ENEMY * frameDeltaTime;
            estado = enemigo1.maquinaEstados(cuboProta);
            printf("estado %d\n",estado);

            if(estado==0)
            {
                printf("sospecha: %f \n",enemigo1.getSospecha());
                //printf("distancia: %f \n",cuboEnemigo.getDistanceFrom(posicionInicial));
                //printf("direccion: %d \n",palla);
                switch(palla)
                {
                case arriba:
                    if(cuboEnemigo.getDistanceFrom(posicionInicial)<=20)
                    {
                        cuboEnemigo.X-=availableMovement;
                        //printf("x: %f \n",cuboEnemigo.X);
                        //printf("y: %f \n",cuboEnemigo.Y);
                        //printf("z: %f \n",cuboEnemigo.Z);
                    }
                    else
                    {
                        palla=derecha;
                        posicionInicial=cuboEnemigo;
                    }
                    break;
                case derecha:
                    if(cuboEnemigo.getDistanceFrom(posicionInicial)<=20)
                    {
                        cuboEnemigo.Z+=availableMovement;
                    }
                    else
                    {
                        palla=abajo;
                        posicionInicial=cuboEnemigo;
                    }
                    break;
                case abajo:
                    if(cuboEnemigo.getDistanceFrom(posicionInicial)<=20)
                    {
                        cuboEnemigo.X+=availableMovement;
                    }
                    else
                    {
                        palla=izquierda;
                        posicionInicial=cuboEnemigo;
                    }
                    break;
                case izquierda:
                    if(cuboEnemigo.getDistanceFrom(posicionInicial)<=20)
                    {
                        cuboEnemigo.Z-=availableMovement;
                    }
                    else
                    {
                        palla=arriba;
                        posicionInicial=cuboEnemigo;
                    }
                    break;
                }
                enemigo1.setPosicion(cuboEnemigo);
            }
            else if(estado==1)
            {
                if(cuboEnemigo.getDistanceFrom(enemigo1.getPunto())!=0)
                {
                    cuboEnemigo += ((enemigo1.getPunto())- (cuboEnemigo)).normalize()*availableMovement;
                    enemigo1.setPosicion(cuboEnemigo);
                }
                if(cuboEnemigo.getDistanceFrom(enemigo1.getPunto())<=0.1){
                    cuboEnemigo=enemigo1.getPunto();
                    enemigo1.setPosicion(cuboEnemigo);
                }
            }
            else if(estado==2)
            {
                cuboEnemigo += direccionProta.normalize()*availableMovement;
                enemigo1.setPosicion(cuboEnemigo);
            }
        }

        prota->setPosition(cuboProta);
        enemigo->setPosition(cuboEnemigo);


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
