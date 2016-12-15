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
#include "driverChoice.h"
#include "include/Enemigo.h"
#include "include/Player.h"
#include "irrKlang/conio.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"


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
    /// BOX 2D

    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);

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


    IrrlichtDevice* device = createDevice(driverType,core::dimension2d<u32>(1080, 720), 16, false, false, false, &receiver);
    IGUIEnvironment* guienv = device->getGUIEnvironment(); //Cargamos la GUI

    device->setWindowCaption(L"IKI" );
    //guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",rect<s32>(10,10,10,10), true );

    if (device == 0)
        return 1; // could not create selected driver.

    video::IVideoDriver* driver = device->getVideoDriver();
    scene::ISceneManager* smgr = device->getSceneManager();
    //scene::IMeshSceneNode *prota = smgr->addCubeSceneNode(5);

    /// MUROS////////////
        scene::IMesh *mura1 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 50.f));
        scene::IMeshSceneNode *muro1 = smgr->addMeshSceneNode(mura1);
        muro1->setPosition(core::vector3df(60,0,0));

        scene::IMesh *mura2 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 10.f));
        scene::IMeshSceneNode *muro2 = smgr->addMeshSceneNode(mura2);
        muro2->setPosition(core::vector3df(40,0,-20));


        scene::IMesh *mura3 = smgr->getGeometryCreator()->createCubeMesh(vector3df(80.f, 10.f, 10.f));
        scene::IMeshSceneNode *muro3 = smgr->addMeshSceneNode(mura3);
        muro3->setPosition(core::vector3df(25,0,30));


        scene::IMesh *mura4 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 25.f));
        scene::IMeshSceneNode *muro4 = smgr->addMeshSceneNode(mura4);
        muro4->setPosition(core::vector3df(25,0,-5));

        scene::IMesh *mura5 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 300.f));
        scene::IMeshSceneNode *muro5 = smgr->addMeshSceneNode(mura5);
        muro5->setPosition(core::vector3df(-40,0,0));



        scene::IMesh *mura6 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 10.f));
        scene::IMeshSceneNode *muro6 = smgr->addMeshSceneNode(mura6);
        muro6->setPosition(core::vector3df(10,0,5));


        scene::IMesh *mura7 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 100.f));
        scene::IMeshSceneNode *muro7 = smgr->addMeshSceneNode(mura7);
        muro7->setPosition(core::vector3df(-10,0,-40));


        scene::IMesh *mura8 = smgr->getGeometryCreator()->createCubeMesh(vector3df(30.f, 10.f, 10.f));
        scene::IMeshSceneNode *muro8 = smgr->addMeshSceneNode(mura8);
        muro8->setPosition(core::vector3df(-20,0,-90));


        scene::IMesh *mura9 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 40.f));
        scene::IMeshSceneNode *muro9 = smgr->addMeshSceneNode(mura9);
        muro9->setPosition(core::vector3df(50,0,140));


        scene::IMesh *mura10 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 60.f));
        scene::IMeshSceneNode *muro10 = smgr->addMeshSceneNode(mura10);
        muro10->setPosition(core::vector3df(80,0,60));


        scene::IMesh *mura11 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 40.f));
        scene::IMeshSceneNode *muro11 = smgr->addMeshSceneNode(mura11);
        muro11->setPosition(core::vector3df(10,0,80));


        scene::IMesh *mura12 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 40.f));
        scene::IMeshSceneNode *muro12 = smgr->addMeshSceneNode(mura12);
        muro12->setPosition(core::vector3df(70,0,160));


        scene::IMesh *mura13 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 40.f));
        scene::IMeshSceneNode *muro13 = smgr->addMeshSceneNode(mura13);
        muro13->setPosition(core::vector3df(90,0,180));


        scene::IMesh *mura14 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 40.f));
        scene::IMeshSceneNode *muro14 = smgr->addMeshSceneNode(mura14);
        muro14->setPosition(core::vector3df(110,0,200));


        scene::IMesh *mura15 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 40.f));
        scene::IMeshSceneNode *muro15 = smgr->addMeshSceneNode(mura15);
        muro15->setPosition(core::vector3df(130,0,220));


        scene::IMesh *mura16 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 250.f));
        scene::IMeshSceneNode *muro16 = smgr->addMeshSceneNode(mura16);
        muro16->setPosition(core::vector3df(40,0,230));
        muro16->setRotation(core::vector3df(0,45,0));

        scene::IMesh *mura17 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 70.f));
        scene::IMeshSceneNode *muro17 = smgr->addMeshSceneNode(mura17);
        muro17->setPosition(core::vector3df(150,0,300));
        muro17->setRotation(core::vector3df(0,-45,0));

        scene::IMesh *mura18 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 70.f));
        scene::IMeshSceneNode *muro18 = smgr->addMeshSceneNode(mura18);
        muro18->setPosition(core::vector3df(230,0,220));
        muro18->setRotation(core::vector3df(0,-45,0));

        scene::IMesh *mura19 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 150.f));
        scene::IMeshSceneNode *muro19 = smgr->addMeshSceneNode(mura19);
        muro19->setPosition(core::vector3df(255,0,125));

        scene::IMesh *mura20 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 150.f));
        scene::IMeshSceneNode *muro20 = smgr->addMeshSceneNode(mura20);
        muro20->setPosition(core::vector3df(300,0,125));

        scene::IMesh *mura21 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 80.f));
        scene::IMeshSceneNode *muro21 = smgr->addMeshSceneNode(mura21);
        muro21->setPosition(core::vector3df(160,0,70));

        scene::IMesh *mura22 = smgr->getGeometryCreator()->createCubeMesh(vector3df(60.f, 10.f, 10.f));
        scene::IMeshSceneNode *muro22 = smgr->addMeshSceneNode(mura22);
        muro22->setPosition(core::vector3df(120,0,40));

        scene::IMesh *mura23 = smgr->getGeometryCreator()->createCubeMesh(vector3df(15.f, 10.f, 10.f));
        scene::IMeshSceneNode *muro23 = smgr->addMeshSceneNode(mura23);
        muro23->setPosition(core::vector3df(135,0,100));

        scene::IMesh *mura24 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 100.f));
        scene::IMeshSceneNode *muro24 = smgr->addMeshSceneNode(mura24);
        muro24->setPosition(core::vector3df(210,0,20));
        muro24->setRotation(core::vector3df(0,-60,0));

        scene::IMesh *mura25 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 90.f));
        scene::IMeshSceneNode *muro25 = smgr->addMeshSceneNode(mura25);
        muro25->setPosition(core::vector3df(280,0,30));
        muro25->setRotation(core::vector3df(0,45,0));

        scene::IMesh *mura26 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 25.f));
        scene::IMeshSceneNode *muro26 = smgr->addMeshSceneNode(mura26);
        muro26->setPosition(core::vector3df(255,0,20));
        muro26->setRotation(core::vector3df(0,-60,0));








    if(prota)
    {
        prota->inicializar(smgr,driver);
        /*prota->setMaterialFlag(video::EMF_LIGHTING, false);
        prota->setPosition(core::vector3df(0,0,0));*/
    }
    if(enemigo1)
        enemigo1->inicialiazar(0, smgr, core::vector3df(35,0,35));
    if(enemigo2)
        enemigo2->inicialiazar(1, smgr, core::vector3df(-35,0,35));

    //core::vector3df posicionInicial (35,0,35);
    //enemigo1.setPunto((prota->getPosition())-(enemigo->getPosition()));

    scene::ICameraSceneNode * camera = smgr->addCameraSceneNode(0,core::vector3df(0,90,-40),core::vector3df(0,0,0));

    //we'll use framerate independent movement.
    u32 then = device->getTimer()->getTime();
    f32 MOVEMENT_SPEED = 25.f;
    const f32 MOVEMENT_SPEED_ENEMY = 15.f;
    core::plane3df plane(prota->getCuboProta(), core::vector3df(0, -1, 0));
    core::vector3df mousePosition = core::vector3df(40,0,0);
    core::line3df ray(mousePosition, prota->getCuboProta());

    //cambio de color de mallas
    smgr->getMeshManipulator()->setVertexColors(enemigo1->getModelo()->getMesh(),irr::video::SColor(255, 255, 0, 0));
    smgr->getMeshManipulator()->setVertexColors(enemigo2->getModelo()->getMesh(),irr::video::SColor(0, 255, 255, 0));

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


        /// COLISIONES ///
        if(prota->getModelo()->getTransformedBoundingBox().intersectsWithBox(muro1->getTransformedBoundingBox())){
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

        float angulo = atan2((mousePosition.Z-prota->getModelo()->getPosition().Z) ,(mousePosition.X-prota->getModelo()->getPosition().X)) * 180.f / irr::core::PI;
        prota->getModelo()->setRotation(core::vector3df(0,angulo,0));

           // prota->getModelo()->setRotation(core::vector3df(0,atan2(receiver.GetMouseState().Position.Y-prota->getModelo()->getPosition().Z, receiver.GetMouseState().Position.X-prota->getModelo()->getPosition().X) * 180.f / irr::core::PI,0));

        }
        if(plane.getIntersectionWithLine(ray.start, ray.getVector(), mousePosition))
        {
            // We now have a mouse position in 3d space; move towards it.
            core::vector3df toMousePosition(mousePosition - prota->getCuboProta());
            const f32 availableMovement = MOVEMENT_SPEED * frameDeltaTime;

            int protaX = mousePosition.X;
            int protaZ = mousePosition.Z;


            if (!protaColliding){
            /// SI NO COLISIONA SE MOVERA EN LINEA RECTA HASTA QUE COLISIONE


                if(toMousePosition.getLength() <= availableMovement){
                    prota->setCuboProta(mousePosition);
                    if(pasosP==true || pasos2P==true){
                        s1->stop();
                        pasosP = false;
                        pasos2P = false;
					}
                    //cuboProta = mousePosition; // Jump to the final position
                }else{
                    prota->setCuboProta(prota->getCuboProta() + toMousePosition.normalize() * availableMovement);
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
                    cameraPos += toMousePosition.normalize() *availableMovement;
                    cameraTar += toMousePosition.normalize() *availableMovement;

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

                prota->setCuboProta(prota->getCuboProta() + redireccion * availableMovement);
                //cuboProta += redireccion * availableMovement;

            }

        //std::cout<< "Prota X = " << protaX << "__ Prota Z = " << protaZ <<std::endl;

        }

        enemigo1->update(direccionProta, prota->getCuboProta(), frameDeltaTime);
        enemigo2->update(direccionProta, prota->getCuboProta(), frameDeltaTime);
        prota->getModelo()->setPosition(prota->getCuboProta());
        //prota->getModelo()->setRotation(core::vector3df(0,atan((mousePosition.Z-prota->getModelo()->getPosition().Z) / -(mousePosition.X-prota->getModelo()->getPosition().X)) * 180.f / irr::core::PI,0));

        std::cout << atan((mousePosition.Z-prota->getModelo()->getPosition().Z) / -(mousePosition.X-prota->getModelo()->getPosition().X)) * 180.f / irr::core::PI << std::endl;

        enemigo1->getModelo()->setPosition(enemigo1->getCuboEnemigo());
        if(cambiao == false)
            enemigo2->getModelo()->setPosition(enemigo2->getCuboEnemigo());
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
    engine->drop();

    return 0;
}

/*
**/
