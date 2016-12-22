#include <irrlicht.h>
#include <Box2D/Box2D.h>
#include "include/Enemigo.h"
#include "include/Player.h"
#include "include/Objeto.h"
#include "include/World.h"
#include "include/Time.h"
#include <irrKlang.h>
#include "irrKlang/conio.h"
#include "Muros.h"
#include <iostream>

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
    ICameraSceneNode * camera = smgr->addCameraSceneNode(0,core::vector3df(0, 20,-20),core::vector3df(0,0,0));

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
/*
    ///ENEMIGOS
    Enemigo  *enemigos[5];
    for(int i=0;i<5;i++){
        enemigos[i]= new Enemigo;
    }
    if(enemigos[0])
        enemigos[0]->inicialiazar(0,0, smgr, core::vector3df(40,0,-10));
    if(enemigos[1])
        enemigos[1]->inicialiazar(1,1, smgr, core::vector3df(-35,0,35));
    if(enemigos[2])
        enemigos[2]->inicialiazar(2,2,smgr,core::vector3df(-35,0,-35));

    //cambio de color de mallas
    smgr->getMeshManipulator()->setVertexColors(enemigos[1]->getModelo()->getMesh(),irr::video::SColor(0, 255, 255, 0));
    smgr->getMeshManipulator()->setVertexColors(enemigos[0]->getModelo()->getMesh(),irr::video::SColor(255, 255, 0, 0));
*/
    ///OBJETO
    Objeto *objeto= new Objeto;
    if(objeto){
        objeto->inicializar(smgr,driver);

    }

    ///PLAYER
    Player *prota= new Player;
    if(prota){
        prota->inicializar(smgr,driver);

    }
    /*
    ///MUROS
    Muros *muro1= new Muros;
    if(muro1){
        muro1->inicializar(smgr, driver);
    }*/
    ///RATON
    core::plane3df plane(prota->getPosicionProta(), core::vector3df(0, -1, 0));
    core::vector3df mousePosition= core::vector3df(0,0,0);
    core::line3df ray(mousePosition, prota->getPosicionProta());

    ///SONIDOS

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

	if (pasos1 == 0 || pasos2 == 0)
        	fprintf(stderr,"Can't load sounds!");

    pasos1->setDefaultVolume(2.0f);
    pasos2->setDefaultVolume(1.0f);

    ///SUELO

/*
    IMesh *mesh = smgr->getGeometryCreator()->createCubeMesh(vector3df(600.f, -5.f, 600.f));
     scene::IMeshSceneNode *suelo = smgr->addMeshSceneNode(mesh);

    if(suelo){
       suelo->setPosition(core::vector3df(100.0f, 0.0f, 50.0f));
       suelo->setRotation(core::vector3df(0,0,0));
       suelo->setMaterialFlag(EMF_LIGHTING, false);
       suelo->setMaterialTexture( 0, driver->getTexture("texturas/suelo.png") );
       //suelo->getMaterial(0).getTextureMatrix(0).setTextureTranslate(1,1);
       //suelo->getMaterial(0).getTextureMatrix(0).setTextureScale(1,1);
    }
*/
	///BOOLEANS

	bool pasosP = false;
	bool pasos2P = false;
	bool cambiao = false;
    bool aparcao = false;

    int lastFPS = -1;
    u32 myClock;
    int frame = 0;
    Time tiempo;
    tiempo.set(device);

    ///CICLO DEL JUEGO

    while(device->run()){
       driver->beginScene(true, true, SColor(255, 100, 101, 140));
        ///raton
        if(receiver.GetMouseState().RightButtonDown)
        {
            ray = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(
                        receiver.GetMouseState().Position, camera);
            float angulo = atan2f((mousePosition.Z - prota->getPosicionProta().Z) ,
                        -(mousePosition.X-prota->getPosicionProta().X)) * 180.f / irr::core::PI;
            prota->getBody()->SetTransform(prota->getBody()->GetPosition(), angulo);
           prota->setRotarProta(core::vector3df(0,prota->getBody()->GetAngle(),0));
        }
        if(plane.getIntersectionWithLine(ray.start, ray.getVector(), mousePosition))
        {
            // We now have a mouse position in 3d space; move towards it.
            core::vector3df toMousePosition(mousePosition - prota->getPosicionProta());
            if(toMousePosition.getLength() <= 1){
                prota->moverBody(vector3df(0,0,0));
                if(pasosP==true || pasos2P==true){
                        s1->stop();
                        pasosP = false;
                        pasos2P = false;
					}
            }
            else{
                prota->moverBody(toMousePosition);
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
            }
        }

        //importante para cambiar posicion de body
        //prota->moverBody(mousePosition);
        prota->setPosition(vector3df(prota->getBody()->GetPosition().x, 0, prota->getBody()->GetPosition().y));
        objeto->setPosition(vector3df(objeto->getBody()->GetPosition().x, 0, objeto->getBody()->GetPosition().y));
        //enemi->setPosition(vector3df(enemi->getBody()->GetPosition().x, 0, enemi->getBody()->GetPosition().y));
        //prota->setPosicionBody(0);

        ///CAMARA
         if(receiver.isKeyDown(KEY_ESCAPE))
        {
            device->closeDevice();
            return 0;
        }
        else if(receiver.isKeyDown(KEY_KEY_D))
        {
            cameraPos.X+=0.1;
            cameraTar.X+=0.1;
        }
        else if (receiver.isKeyDown(KEY_KEY_A))
        {
            cameraPos.X-=0.1;
            cameraTar.X-=0.1;
        }
        else if(receiver.isKeyDown(KEY_KEY_W))
        {
            cameraPos.Z+=0.1;
            cameraTar.Z+=0.1;
        }
        else if (receiver.isKeyDown(KEY_KEY_S))
        {
            cameraPos.Z-=0.1;
            cameraTar.Z-=0.1;
        }
        /* NO BORRAR
        if(enemigos[1]->getEstado() == 3){
            if(cambiao == false){
                smgr->getMeshManipulator()->setVertexColors(enemigos[1]->getModelo()->getMesh(),irr::video::SColor(255, 0, 255, 0));
                s2 = engine->play3D(alarma,posicion,false,false,true);
                cambiao = true;
            }
            else if(s2->isFinished()){
                aparcao = true;
                vector3df posicion= enemigos[1]->getPosicion()+vector3df(5,0,5);
                vector3df posicion2= enemigos[1]->getPosicion()+vector3df(-5,0,-5);
                enemigos[3]->inicialiazar(4,0,smgr,posicion);
                enemigos[4]->inicialiazar(5,0,smgr,posicion2);
                enemigos[3]->setEstado(8);
                enemigos[4]->setEstado(8);
                enemigos[1]->setEstado(10);
                    //eliminar enemigo
                enemigos[1]->getModelo()->setPosition(core::vector3df(-1000,0,0));

            }
        }*/

        DeltaTime = timer->getTime() - TimeStamp;
        TimeStamp = timer->getTime();
        tiempo.update();

        camera->setPosition(cameraPos);
        camera->setTarget(cameraTar);

        //Guardia
//        enemigos[0]->update(prota->getCuboProta(), tiempo, enemigos);
        /*//Alarma
        enemigos[1]->update(prota->getCuboProta(), tiempo, enemigos);
        //Medico
        enemigos[2]->update(prota->getCuboProta(), tiempo, enemigos);
        if(aparcao){
        enemigos[3]->update(prota->getCuboProta(), tiempo, enemigos);
        enemigos[4]->update(prota->getCuboProta(), tiempo, enemigos);
        }*/
   //     enemigos[0]->getModelo()->setPosition(enemigos[0]->getCuboEnemigo());
        /*//Si el dron no se ha convertido en alarma
        if(cambiao == false)
            enemigos[1]->getModelo()->setPosition(enemigos[1]->getCuboEnemigo());
        if(aparcao){
            enemigos[3]->getModelo()->setPosition(enemigos[3]->getCuboEnemigo());
            enemigos[4]->getModelo()->setPosition(enemigos[4]->getCuboEnemigo());
        }
        enemigos[2]->getModelo()->setPosition(enemigos[2]->getCuboEnemigo());*/


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
    engine->drop();

    return 0;
}
