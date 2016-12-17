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
#include <irrKlang.h>
#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>
#include <iostream>
#include "driverChoice.h"
#include "include/Enemigo.h"
#include "include/Player.h"
#include "include/Muros.h"
#include "irrKlang/conio.h"
#include "include/World.h"


using namespace irr;
using namespace irrklang;

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

/*
The event receiver for keeping the pressed keys is ready, the actual responses
will be made inside the render loop, right before drawing the scene. So lets
just create an irr::IrrlichtDevice and the scene node we want to move. We also
create some other additional scene nodes, to show that there are also some
different possibilities to move and animate scene nodes.
*/

int main()
{

    ///BOX2D
    //class World* world; no se por que puse class
    World* world;
    world = World::Instance();


    /// IRR KLANG

    ISoundEngine* engine = createIrrKlangDevice();


	if (!engine)
		return 0; // error starting up the engine

	/*printf("Driver: %s\n",engine->getDriverName());
	printf("Volume: %f\n",engine->getSoundVolume());*/

	ISoundSource* pasos1 = engine->addSoundSourceFromFile("sonidos/pasosnormales.wav");
	ISoundSource* pasos2 = engine->addSoundSourceFromFile("sonidos/pasossigilosos.wav");
	ISoundSource* alarma = engine->addSoundSourceFromFile("sonidos/alarma_sintetizada2.wav");
	vec3df posicion(0,0,0);
	ISound* s1;
	ISound* s2;


	bool pasosP = false;
	bool pasos2P = false;
	bool cambiao = false;
    bool protaColliding = false;

	if (pasos1 == 0 || pasos2 == 0)
        	fprintf(stderr,"Can't load sounds!");

    pasos1->setDefaultVolume(2.0f);
    pasos2->setDefaultVolume(1.0f);


    // ask user for driver
    video::E_DRIVER_TYPE driverType=driverChoiceConsole();
    if (driverType==video::EDT_COUNT)
        return 1;

    // create device
    MyEventReceiver receiver;

    Enemigo *enemigo1 = new Enemigo;
    Enemigo *enemigo2 = new Enemigo;
    Player  *prota    = new Player;
    Muros *muros = new Muros;


    IrrlichtDevice* device = createDevice(driverType,core::dimension2d<u32>(1280, 720), 16, false, false, false, &receiver);
    IGUIEnvironment* guienv = device->getGUIEnvironment(); //Cargamos la GUI

    device->setWindowCaption(L"IKI & BOX2D" );
    //guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",rect<s32>(10,10,10,10), true );

    if (device == 0)
        return 1; // could not create selected driver.

    video::IVideoDriver* driver = device->getVideoDriver();
    scene::ISceneManager* smgr = device->getSceneManager();
    //scene::IMeshSceneNode *prota = smgr->addCubeSceneNode(5);

    /// MUROS////////////
    /*  scene::IMeshSceneNode *muro1 = smgr->addCubeSceneNode(30);
        muro1->setMaterialFlag(video::EMF_LIGHTING, false);
        muro1->setPosition(core::vector3df(0,0,0));
        smgr->getMeshManipulator()->setVertexColors(muro1->getMesh(),irr::video::SColor(0, 0, 0, 0));
    b2BodyDef bodyMur;
        bodyMur.type= b2_staticBody;

        bodyMur *body= world->CreateBody(&bodyMur);

        b2PolygonShape bodyShape2;
        bodyShape2.SetAsBox(30/2, 30/2);

        body->CreateFixture(&bodyShape2, 1.0f);
*/
        //IMesh *mesh = smgr->getGeometryCreator()->createCubeMesh(vector3df(300.f, -5.f, 300.f));
         //scene::IMeshSceneNode *suelo = smgr->addMeshSceneNode(mesh);

    /// SUELO ////
    /*
    if(suelo){
       suelo->setPosition(core::vector3df(0.0f, 0.0f, 0.0f));
       suelo->setRotation(core::vector3df(0,0,0));
       suelo->setMaterialFlag(EMF_LIGHTING, false);
       suelo->setMaterialTexture( 0, driver->getTexture("texturas/suelo.png") );
       //suelo->getMaterial(0).getTextureMatrix(0).setTextureTranslate(1,1);
       //suelo->getMaterial(0).getTextureMatrix(0).setTextureScale(1,1);
    }
*/
    if(prota)
    {
        prota->inicializar(smgr,driver);
        /*prota->setMaterialFlag(video::EMF_LIGHTING, false);
        prota->setPosition(core::vector3df(0,0,0));*/
    }
    if(muros){
        muros->inicializar(smgr, driver);
    }
    if(enemigo1)
        enemigo1->inicialiazar(0, smgr, core::vector3df(35,0,0));
    if(enemigo2)
        enemigo2->inicialiazar(1, smgr, core::vector3df(-35,0,0));

    //core::vector3df posicionInicial (35,0,35);
    //enemigo1.setPunto((prota->getPosition())-(enemigo->getPosition()));

    scene::ICameraSceneNode * camera = smgr->addCameraSceneNode(0,core::vector3df(0,90,-40),core::vector3df(0,0,0));

    //we'll use framerate independent movement.
    u32 then = device->getTimer()->getTime();
    f32 MOVEMENT_SPEED = 25.f;
    const f32 MOVEMENT_SPEED_ENEMY = 15.f;
    core::plane3df plane(prota->getCuboProta(), core::vector3df(0, -1, 0));
    core::vector3df mousePosition = core::vector3df(0,0,0);
    core::line3df ray(mousePosition, prota->getCuboProta());

    //cambio de color de mallas
    smgr->getMeshManipulator()->setVertexColors(enemigo1->getModelo()->getMesh(),irr::video::SColor(255, 255, 0, 0));
    smgr->getMeshManipulator()->setVertexColors(enemigo2->getModelo()->getMesh(),irr::video::SColor(0, 255, 255, 0));




    ///BOX2D
        ITimer* timer = device->getTimer();
        f32 TimeStamp = timer->getTime();
        f32 DeltaTime = timer->getTime() - TimeStamp;




    while(device->run())
    {


        if(receiver.isKeyDown(KEY_LSHIFT))
            MOVEMENT_SPEED = 15.f;
        else
            MOVEMENT_SPEED = 25.f;


        // Work out a frame delta time.
        const u32 now = device->getTimer()->getTime();
        const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
        then = now;

        core::vector3df cameraPos = camera->getPosition();
        core::vector3df cameraTar = camera->getTarget();

        //core::vector3df cuboProta = prota->getPosition();
        //core::vector3df cuboEnemigo = enemy->getPosition();
        core::vector3df direccionProta (prota->getCuboProta() - enemigo1->getCuboEnemigo());



        //core::vector3df direccionProta2 (cuboProta-cameraPos);


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
        if(enemigo2->getEstado() == 2){
            if(cambiao == false){
                smgr->getMeshManipulator()->setVertexColors(enemigo2->getModelo()->getMesh(),irr::video::SColor(255, 0, 255, 0));
                s2 = engine->play3D(alarma,posicion,false,false,true);
                cambiao = true;
            }
            else if(s2->isFinished()){
                enemigo2->getModelo()->setPosition(core::vector3df(-1000,0,0));
            }
        }


        if(receiver.GetMouseState().RightButtonDown)
        {
            ray = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(
                      receiver.GetMouseState().Position, camera);

        }
        if(plane.getIntersectionWithLine(ray.start, ray.getVector(), mousePosition))
        {
            // We now have a mouse position in 3d space; move towards it.
            core::vector3df toMousePosition(mousePosition - prota->getCuboProta());
            const f32 availableMovement = MOVEMENT_SPEED * frameDeltaTime;

            int protaX = mousePosition.X;
            int protaZ = mousePosition.Z;


            /// SI NO COLISIONA SE MOVERA EN LINEA RECTA HASTA QUE COLISIONE


                if(toMousePosition.getLength() <= availableMovement){
                    ///mov
                    //prota->setPosicionBody(mousePosition, 0);
                    //prota->setCuboProta(mousePosition);
                    if(pasosP==true || pasos2P==true){
                        s1->stop();
                        pasosP = false;
                        pasos2P = false;
					}
                    //cuboProta = mousePosition; // Jump to the final position
                }else{
                    ///mov
                    //prota->setPosicionBody(mousePosition, 0);
                    //prota->setCuboProta(prota->getCuboProta() + toMousePosition.normalize() * availableMovement);
                    if(pasosP==false && !receiver.isKeyDown(KEY_LSHIFT)){
                        if(engine->isCurrentlyPlaying(pasos2))
                            s1->stop();

                            s1 = engine->play3D(pasos1,posicion,true,false,true);

                        pasosP = true;
                        pasos2P = false;

                    }else if (pasos2P==false && receiver.isKeyDown(KEY_LSHIFT)){
                        if(engine->isCurrentlyPlaying(pasos1))
                            s1->stop();

                            s1 = engine->play3D(pasos2,posicion,true,false,true);
                        pasos2P = true;
                        pasosP = false;

                    }
                    //cuboProta += toMousePosition.normalize() * availableMovement; // Move towards i
                    //Para que la camara siga al prota
                    //cameraPos += toMousePosition.normalize() *availableMovement;
                    //cameraTar += toMousePosition.normalize() *availableMovement;
            }

        //std::cout<< "Prota X = " << protaX << "__ Prota Z = " << protaZ <<std::endl;

        }

        enemigo1->update(direccionProta, prota->getCuboProta(), frameDeltaTime);
        enemigo2->update(direccionProta, prota->getCuboProta(), frameDeltaTime);
        ///mov3
        prota->moverBody(mousePosition);
        prota->setPosicionModelo(b2Vec2(prota->getBody()->GetPosition().x, prota->getBody()->GetPosition().y));


        //prota->setPosicionBody(0);
        //prota->setPosicionModelo(prota->getBody()->GetPosition());
        //prota->getModelo()->setPosition(prota->getCuboProta());
        //importante para cambiar posicion de body



        enemigo1->getModelo()->setPosition(enemigo1->getCuboEnemigo());
        if(cambiao == false)
            enemigo2->getModelo()->setPosition(enemigo2->getCuboEnemigo());
        camera->setPosition(cameraPos);
        camera->setTarget(cameraTar);

        ///BOX2D
        DeltaTime = timer->getTime() - TimeStamp;
        TimeStamp = timer->getTime();

        world->Step(DeltaTime);
        world->getWorld()->ClearForces();
/*
        float32 timeStep = 1/20.0;      //the length of time passed to simulate (seconds)
        int32 velocityIterations = 8;   //how strongly to correct velocity
        int32 positionIterations = 3;   //how strongly to correct position

        world->Step( timeStep, velocityIterations, positionIterations);

        //world->Step(DeltaTime*timeStep, 6, 6);
        world->ClearForces();
*/


        driver->beginScene(true, true, video::SColor(255,113,113,133));
        guienv->drawAll();  ///BOX2D
        smgr->drawAll(); // draw the 3d scene
        driver->endScene();
    }

    /*
    In the end, delete the Irrlicht device.
    */
    device->drop();
    engine->drop();

    return 0;
}

/*
**/
