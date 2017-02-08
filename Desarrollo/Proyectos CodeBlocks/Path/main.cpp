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
    IrrlichtDevice* device = createDevice(driverType,core::dimension2d<u32>(1360, 768), 16, false, false, false, &receiver);
    device->setWindowCaption(L"IKI" );
    ITimer* timer = device->getTimer();
    f32 TimeStamp = timer->getTime();
    f32 DeltaTime = timer->getTime() - TimeStamp;

    ISceneManager* smgr= device->getSceneManager();         //Gestion de la escena
    IVideoDriver* driver= device->getVideoDriver();         //Ciclo del juego
    IGUIEnvironment* guienv= device->getGUIEnvironment();   //Interfaz de usuario



    ///CAMARA
    ICameraSceneNode * camera = smgr->addCameraSceneNode(0,core::vector3df(190, 40, 40),core::vector3df(170,0,40));

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



    Map *Mapa= new Map;
    if(Mapa){
        Mapa->loadMap(smgr);

    }




    ///PLAYER
    Player *prota= new Player;
    if(prota){
        prota->inicializar(smgr,driver);

    }



    ///OBJETO
    Objeto *objetos[2];
    for(int m= 0; m < 2; m++){
        objetos[m]= new Objeto;
    }

    if(objetos[0]){
        objetos[0]->inicializar(smgr, driver, core::vector3df(300,0,300));
    }
    if(objetos[1]){
        objetos[1]->inicializar(smgr, driver, core::vector3df(300,0,300));
    }

    ///RATON
    core::plane3df plane(prota->getCuboProta(), core::vector3df(0, -1, 0));
    core::vector3df mousePosition= core::vector3df(0,0,0);
    vector3df toMousePositionObj;
    vector3df toMousePosition;
    core::line3df ray(mousePosition, prota->getCuboProta());
    core::line3df ray2(mousePosition, prota->getCuboProta());
    core::line3df ray3(mousePosition, prota->getCuboProta());

    ///SONIDOS

    ISoundEngine* engine = createIrrKlangDevice();

	if (!engine)
		return 0; // error starting up the engine

	/*printf("Driver: %s\n",engine->getDriverName());
	printf("Volume: %f\n",engine->getSoundVolume());*/

	ISoundSource* pasos1 = engine->addSoundSourceFromFile("sonidos/pasosnormales.wav");
	ISoundSource* pasos2 = engine->addSoundSourceFromFile("sonidos/pasossigilosos.wav");
	ISoundSource* alarma = engine->addSoundSourceFromFile("sonidos/alarma_sintetizada2.wav");
	ISoundSource* escaneo = engine->addSoundSourceFromFile("sonidos/escaneobueno.wav");
	ISoundSource* combate = engine->addSoundSourceFromFile("sonidos/protocolo_combate.wav");
	ISoundSource* investigar = engine->addSoundSourceFromFile("sonidos/investigando.wav");
	ISoundSource* patrullar = engine->addSoundSourceFromFile("sonidos/area_despejada_fin.wav");
	ISoundSource* escaneomedico = engine->addSoundSourceFromFile("sonidos/escaneando_medico.wav");
	ISoundSource* huir = engine->addSoundSourceFromFile("sonidos/intruso_detectado_medico.wav");
	ISoundSource* defensa = engine->addSoundSourceFromFile("sonidos/protocolo_defensa_medico.wav");
	ISoundSource* investigarmedico = engine->addSoundSourceFromFile("sonidos/investigando_medico.wav");
	ISoundSource* patrullarmedico = engine->addSoundSourceFromFile("sonidos/area_despejada_medico.wav");
	ISoundSource* escaneodron = engine->addSoundSourceFromFile("sonidos/beepveralgo.wav");
	ISoundSource* investigardron = engine->addSoundSourceFromFile("sonidos/beepinvestigar.wav");
	ISoundSource* patrullardron = engine->addSoundSourceFromFile("sonidos/beepaliviado.wav");
	ISoundSource* lasertorreta = engine->addSoundSourceFromFile("sonidos/lasertorreta.wav");
	ISoundSource* aviso = engine->addSoundSourceFromFile("sonidos/beepvigilar.wav");
	ISoundSource* rayopara = engine->addSoundSourceFromFile("sonidos/rayoprota.wav");
	ISoundSource* hack = engine->addSoundSourceFromFile("sonidos/elhack.wav");
	vec3df posicion(0,0,0);
	ISound* s1;
	ISound* s2;
	ISound* s3;
	ISound* s4;
	ISound* s5;
	ISound* s6;
	ISound* s7;
	ISound* s8;
	ISound* s9;
	ISound* s10;
	ISound* s11;


    pasos1->setDefaultVolume(2.0f);
    pasos2->setDefaultVolume(1.0f);



    ///SUELO


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

    ///VIDA PROTA
    ITexture *image;
    image = driver->getTexture("texturas/tuerca.png");
    driver->makeColorKeyTexture(image, position2d<s32>(0,0));
    driver->getMaterial2D().TextureLayer[0].BilinearFilter=true;
    driver->getMaterial2D().AntiAliasing=EAAM_FULL_BASIC;

	///BOOLEANS Y DECLARACIONES RANDOM

    bool congelado1 = false;
    bool congelado2 = false;
    bool congelado3 = false;
    bool congelado4 = false;
    bool congelado5 = false;
    bool congelado6 = false;
	bool pasosP = false;
	bool pasos2P = false;
	bool escaneando = false;
	bool combatiendo = false;
	bool investigando = false;
	bool patrullando = true;
	bool escaneandog2 = false;
	bool combatiendog2 = false;
	bool investigandog2 = false;
	bool patrullandog2 = true;
	bool escaneandog3 = false;
	bool combatiendog3 = false;
	bool investigandog3 = false;
	bool patrullandog3 = true;
	bool escaneando2 = false;
	bool combatiendo2 = false;
	bool investigando2 = false;
	bool patrullando2 = true;
	bool escaneando3 = false;
	bool investigando3 = false;
	bool patrullando3 = true;
	bool huyendo = false;
	bool cambiao = false;
    bool aparcao = false;
    bool hayobj= false, hayobj2= false;
    bool centinela= false;
    bool tocado= false;
    bool stop= true;
    bool kiko= false;
    bool kiko2= false;
    bool rayolaser = false;
    bool rayolaser1 = false;

    //PERCEPCION SENSONRIAL

    b2RayCastInput input;
    input.maxFraction	=	1.0f;
    b2RayCastOutput	output;
    float angulo2 = 0;
    float distancia = 0;
    scene::IMesh *rayo = smgr->getGeometryCreator()->createCubeMesh(core::vector3df(10.f, 1.f, 1.f));
    scene::IMeshSceneNode *modelo = smgr->addMeshSceneNode(rayo);
    modelo->setVisible(false);

    //RAYO PARALIZADOR

    float angulo3 = 0;
    float distancia3 = 0;
    scene::IMesh *rayo2 = smgr->getGeometryCreator()->createCubeMesh(core::vector3df(10.f, 1.f, 1.f));
    scene::IMeshSceneNode *modelo2 = smgr->addMeshSceneNode(rayo2);
    modelo2->setVisible(false);

    int lastFPS = -1;
    u32 myClock;
    int frame = 0;
    Time tiempo;
    tiempo.set(device);
    float vidaProta;
    int n, balamenos= 0;
    float objvida= 0.0f;
    int objlaser= 0;
    bool vez= false, vez2= false;

    ///CICLO DEL JUEGO
    while(device->run()){
       driver->beginScene(true, true, SColor(255, 100, 101, 140));



        ///raton
        if(receiver.GetMouseState().RightButtonDown)
        {
            stop= false;
            centinela= false;
            ray = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(
                        receiver.GetMouseState().Position, camera);
            float angulo = atan2f((mousePosition.Z-prota->getModelo()->getPosition().Z) ,
                        -(mousePosition.X-prota->getModelo()->getPosition().X)) * 180.f / irr::core::PI;
            prota->getBody()->SetTransform(prota->getBody()->GetPosition(), angulo);
            prota->getModelo()->setRotation(core::vector3df(0,prota->getBody()->GetAngle(),0));
            prota->getEsfera()->setRotation(core::vector3df(0,prota->getBody()->GetAngle(),0));
        }
        ///clic izq

        if(receiver.GetMouseState().LeftButtonDown){

            ray = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(
                    receiver.GetMouseState().Position, camera);
            float angulo = atan2f((mousePosition.Z - prota->getPosicionProta().Z) ,
                    -(mousePosition.X-prota->getPosicionProta().X)) * 180.f / irr::core::PI;
            prota->getBody()->SetTransform(prota->getBody()->GetPosition(), angulo);
            //prota->setRotarProta(core::vector3df(0,prota->getBody()->GetAngle(),0));
        }


        if(plane.getIntersectionWithLine(ray.start, ray.getVector(), mousePosition))
        {
            // We now have a mouse position in 3d space; move towards it.
            toMousePosition = mousePosition - prota->getCuboProta();
            hayobj= objetos[0]->comprobarPunto(b2Vec2(mousePosition.X, mousePosition.Z));
            hayobj2= objetos[1]->comprobarPunto(b2Vec2(mousePosition.X, mousePosition.Z));
            if(hayobj){
                vez= true;
                toMousePosition = mousePosition - prota->getCuboProta();
            }else if(hayobj2){
                vez2= true;
                toMousePosition = mousePosition - prota->getCuboProta();
                //centinela = false;
            }else if(centinela){
                toMousePosition = vector3df(0,0,0);
                //centinela = false;
            }



            if(hayobj || hayobj2){
               tocado = prota->cogerObjeto(toMousePosition, smgr);
               centinela = false;
            }
            else{
                if(toMousePosition.getLength() <= 1){
                    prota->moverBody(vector3df(0,0,0));
                    if(pasosP==true || pasos2P==true){
                            s1->stop();
                            pasosP = false;
                            pasos2P = false;
                    }
                    centinela == false;
                    stop= true;
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
                    stop= true;
                }
            }
        }

        ///VIDA PROTA


        if(prota->getVida() >= 200){
            driver->draw2DImage(image, position2d<s32>(10, 10), rect<s32>(0, 0, 47, 47), 0, SColor(255, 255, 255, 255), true);
            driver->draw2DImage(image, position2d<s32>(60, 10), rect<s32>(0, 0, 47, 47), 0, SColor(255, 255, 255, 255), true);
            driver->draw2DImage(image, position2d<s32>(110, 10), rect<s32>(0, 0, 47, 47), 0, SColor(255, 255, 255, 255), true);
        }
        else if(prota->getVida() >= 100){
            driver->draw2DImage(image, position2d<s32>(10, 10), rect<s32>(0, 0, 47, 47), 0, SColor(255, 255, 255, 255), true);
            driver->draw2DImage(image, position2d<s32>(60, 10), rect<s32>(0, 0, 47, 47), 0, SColor(255, 255, 255, 255), true);
        }
        else if(prota->getVida() > 0){
           driver->draw2DImage(image, position2d<s32>(10, 10), rect<s32>(0, 0, 47, 47), 0, SColor(255, 255, 255, 255), true);
        }


        prota->setPosition(vector3df(prota->getBody()->GetPosition().x, 0, prota->getBody()->GetPosition().y));
        if(tocado == true){
            if(vez){
                objvida= prota->getVida() + 50.0f;
                std::cout <<"vida: "<<objvida<<" \n";
                prota->setVida(objvida);
                prota->setNoMuerto();
                smgr->getMeshManipulator()->setVertexColors(prota->getModelo()->getMesh(),video::SColor(255,255,255, 255));
                vez= false;
                objetos[0]->setPosition(vector3df(5000, 0, 5000));
            }
            else if(vez2){
                objlaser= prota->getLaser() + 5;
                std::cout <<"balas: "<<objlaser<<" \n";
                prota->setLaser(objlaser);
                vez2= false;
                objetos[1]->setPosition(vector3df(5000, 0, 5000));
            }

            tocado = false;
        }
        else{
            objetos[0]->setPosition(vector3df(objetos[0]->getBody()->GetPosition().x, 0, objetos[0]->getBody()->GetPosition().y));
            objetos[1]->setPosition(vector3df(objetos[1]->getBody()->GetPosition().x, 0, objetos[1]->getBody()->GetPosition().y));
        }
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
            cameraPos.Z+=0.3*DeltaTime;
            cameraTar.Z+=0.3*DeltaTime;
        }
        else if (receiver.isKeyDown(KEY_KEY_A))
        {
            cameraPos.Z-=0.3*DeltaTime;
            cameraTar.Z-=0.3*DeltaTime;
        }
        else if(receiver.isKeyDown(KEY_KEY_W))
        {
            cameraPos.X-=0.3*DeltaTime;
            cameraTar.X-=0.3*DeltaTime;
        }
        else if (receiver.isKeyDown(KEY_KEY_S))
        {
            cameraPos.X+=0.3*DeltaTime;
            cameraTar.X+=0.3*DeltaTime;
        }

        if(receiver.isKeyDown(KEY_LSHIFT))
           prota->velocidad = 4.5f;
        else
           prota->velocidad = 10.0f;





        DeltaTime = timer->getTime() - TimeStamp;
        TimeStamp = timer->getTime();
        tiempo.update();

        camera->setPosition(cameraPos);
        camera->setTarget(cameraTar);

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
