#include <irrlicht.h>
#include <Box2D/Box2D.h>
#include "include/Enemigo.h"
#include "include/Objeto.h"
#include <irrKlang.h>
#include "irrKlang/conio.h"
#include <iostream>

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
    ICameraSceneNode * camera = smgr->addCameraSceneNode(0,core::vector3df(0, 100,-30),core::vector3df(0,0,0));

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

    ///PATRULLAS

    ///3-> Enemigos[3] Guardia2
    PatrolPoint *pp05, *pp06;
    pp05 = new PatrolPoint(irr::core::vector3df(180,0,120));
    pp06 = new PatrolPoint(irr::core::vector3df(100,0,120));

    pp05->setNext(pp06); pp06->setNext(pp05);
    pp05->setPrev(pp06); pp06->setPrev(pp05);

    PatrolRoute pr03;
    pr03.setInicial(pp05); pr03.setFinal(pp05->getPrev());

    ///4 Enemigos[4] Guardia3
    PatrolPoint *pp15, *pp16;
    pp15 = new PatrolPoint(irr::core::vector3df(70,0,250));
    pp16 = new PatrolPoint(irr::core::vector3df(-10,0,150));

    pp15->setNext(pp16); pp16->setNext(pp15);
    pp15->setPrev(pp16); pp16->setPrev(pp15);

    PatrolRoute pr04;
    pr04.setInicial(pp15); pr04.setFinal(pp15->getPrev());
    ///1-> Enemigos[2] Medico
    PatrolPoint *pp01, *pp02, *pp03, *pp04;
    pp01 = new PatrolPoint(irr::core::vector3df(-20,0,50));
    pp02 = new PatrolPoint(irr::core::vector3df(-20,0,115));
    pp03 = new PatrolPoint(irr::core::vector3df(45,0,115));
    pp04 = new PatrolPoint(irr::core::vector3df(45,0, 50));

    pp01->setNext(pp02); pp02->setNext(pp03); pp03->setNext(pp04); pp04->setNext(pp01);
    pp01->setPrev(pp04); pp04->setPrev(pp03); pp03->setPrev(pp02); pp02->setPrev(pp01);

    PatrolRoute pr01;
    pr01.setInicial(pp01); pr01.setFinal(pp01->getPrev());

    ///2-> Enemigos[6] GuardiaNuevo
    PatrolPoint *pp11, *pp12, *pp13, *pp14;
    pp11 = new PatrolPoint(irr::core::vector3df(275,0,130));
    pp12 = new PatrolPoint(irr::core::vector3df(265,0,30));
    pp13 = new PatrolPoint(irr::core::vector3df(190,0,55));
    pp14 = new PatrolPoint(irr::core::vector3df(265,0,30));

    pp11->setNext(pp12); pp12->setNext(pp13); pp13->setNext(pp14); pp14->setNext(pp11);
    pp11->setPrev(pp14); pp14->setPrev(pp13); pp13->setPrev(pp12); pp12->setPrev(pp11);

    PatrolRoute pr02;
    pr02.setInicial(pp11); pr02.setFinal(pp11->getPrev());
   ///5 -> Enemigo[0] Guardia
    PatrolPoint *pp09, *pp10;
    pp09 = new PatrolPoint(irr::core::vector3df(-25,0,30));
    pp10 = new PatrolPoint(irr::core::vector3df(-25,0,-80));

    pp09->setNext(pp10); pp10->setNext(pp09);
    pp09->setPrev(pp10); pp10->setPrev(pp09);

    PatrolRoute pr05;
    pr05.setInicial(pp09); pr05.setFinal(pp10->getPrev());

    ///5 -> Enemigo[1] Dron
    PatrolPoint *pp07, *pp08;
    pp07 = new PatrolPoint(irr::core::vector3df(120,0,100));
    pp08 = new PatrolPoint(irr::core::vector3df(120,0,170));

    pp07->setNext(pp08); pp08->setNext(pp07);
    pp07->setPrev(pp08); pp08->setPrev(pp07);

    PatrolRoute pr06;
    pr06.setInicial(pp07); pr06.setFinal(pp07->getPrev());


    int danio = 0;

    //std::cout << "1\n";

    ///ENEMIGOS
    Enemigo  *enemigos[7];
    for(int i=0;i<7;i++){
        enemigos[i]= new Enemigo;
    }
    if(enemigos[0])
        enemigos[0]->inicialiazar(0,0, smgr,vector3df(-25,0,-80),pr05);
    if(enemigos[1])
        enemigos[1]->inicialiazar(1,1, smgr,vector3df(120,0,170),pr06);
    if(enemigos[2])
        enemigos[2]->inicialiazar(2,2,smgr,vector3df(45,0,50),pr01);
    if(enemigos[5])
        enemigos[5]->inicialiazar2(smgr);
    if(enemigos[6])
        enemigos[6]->inicialiazar(0,6,smgr,vector3df(265,0,25),pr02);

    //cambio de color de mallas
    //smgr->getMeshManipulator()->setVertexColors(enemigos[1]->getModelo()->getMesh(),irr::video::SColor(0, 255, 255, 0));
    smgr->getMeshManipulator()->setVertexColors(enemigos[0]->getModelo()->getMesh(),irr::video::SColor(255, 255, 0, 0));

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
       for(int i=0;i<7;i++){
        enemigos[i]->setMuro(muro1, prota);
    }


    ///OBJETO
    Objeto *objetos[2];
    for(int m= 0; m < 2; m++){
        objetos[m]= new Objeto;
    }

    if(objetos[0]){
        objetos[0]->inicializar(smgr, driver, core::vector3df(120,0,60));
    }
    if(objetos[1]){
        objetos[1]->inicializar(smgr, driver, core::vector3df(40,0,185));
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

        if(!receiver.GetMouseState().LeftButtonDown)
            danio = 0;
        if(receiver.GetMouseState().LeftButtonDown && stop== true){
            centinela= true;
            danio++;
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

            /// ATAQUE PROTA
            if (danio == 1)
            for(n= 0; n <= 6; n++){

                if(enemigos[n]->getCreado()){

                    if(!enemigos[n]->getMuerto() && enemigos[n]->comprobarPunto(b2Vec2(mousePosition.X, mousePosition.Z))){
                        enemigos[n]->setDanyado(prota->atacar(toMousePosition, smgr));
                        if(enemigos[n]->getDanyado()){
                            enemigos[n]->quitarVida();
                        }
                    }
                    else{
                        //smgr->getMeshManipulator()->setVertexColors(prota->getModelo()->getMesh(),video::SColor(0, 0, 0, 0));
                        if(toMousePosition.getLength() <= 1)
                            prota->moverBody(vector3df(0,0,0));
                        else
                            prota->moverBody(toMousePosition);
                    }
                }
            }

            /////

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
            cameraPos.X+=0.3*DeltaTime;
            cameraTar.X+=0.3*DeltaTime;
        }
        else if (receiver.isKeyDown(KEY_KEY_A))
        {
            cameraPos.X-=0.3*DeltaTime;
            cameraTar.X-=0.3*DeltaTime;
        }
        else if(receiver.isKeyDown(KEY_KEY_W))
        {
            cameraPos.Z+=0.3*DeltaTime;
            cameraTar.Z+=0.3*DeltaTime;
        }
        else if (receiver.isKeyDown(KEY_KEY_S))
        {
            cameraPos.Z-=0.3*DeltaTime;
            cameraTar.Z-=0.3*DeltaTime;
        }

        if(receiver.isKeyDown(KEY_LSHIFT))
           prota->velocidad = 4.5f;
        else
           prota->velocidad = 10.0f;


        //// RAYO LASER paralizador
        if(prota->getLaser() > 0){
            if(receiver.isKeyDown(KEY_KEY_Q) && !rayolaser){
                balamenos= prota->getLaser() - 1;
                prota->setLaser(balamenos);
                rayolaser = true;
                rayolaser1 = true;
                b2RayCastInput input2;
                input2.maxFraction	=	1.0f;
                b2RayCastOutput	output2;

                ray3 = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(
                receiver.GetMouseState().Position, camera);

                plane.getIntersectionWithLine(ray3.start, ray3.getVector(), mousePosition);

                toMousePosition = mousePosition - prota->getCuboProta();

                input2.p1.Set(prota->getBody()->GetPosition().x, prota->getBody()->GetPosition().y);	//	Punto	inicial	del	rayo
                float modulo = sqrt((toMousePosition.X*toMousePosition.X) + (toMousePosition.Z*toMousePosition.Z));
                input2.p2.Set(prota->getCuboProta().X+((toMousePosition.X/modulo)*50), prota->getCuboProta().Z+((toMousePosition.Z/modulo)*50));

                //bool    hitmuro     =   muro1->body15->GetFixtureList()->RayCast(&output,	input,	0);
                //bool    hitprota	=	prota->getBody()->GetFixtureList()->RayCast(&output,	input,	0);


                distancia3 = sqrt(pow(input2.p2.x-input2.p1.x, 2)+pow(input2.p2.y-input2.p1.y, 2));
                angulo3 = atan2f((input2.p2.y-input2.p1.y) , -(input2.p2.x-input2.p1.x)) * 180.f / irr::core::PI;

                if(enemigos[0]->getBody()->GetFixtureList()->RayCast(&output2,	input2,	0))
                    congelado1 = true;
                else if(enemigos[1]->getBody()->GetFixtureList()->RayCast(&output2,	input2,	0))
                    congelado2 = true;
                else if(enemigos[2]->getBody()->GetFixtureList()->RayCast(&output2,	input2,	0))
                    congelado3 = true;

                if(kiko){

                if(enemigos[3]->getBody()->GetFixtureList()->RayCast(&output2,	input2,	0))
                    congelado4 = true;
                else if(enemigos[4]->getBody()->GetFixtureList()->RayCast(&output2,	input2,	0))
                    congelado5 = true;
                }



                s10 = engine->play3D(rayopara,posicion,false,false,true);
                s11 = engine->play3D(hack,posicion,false,false,true);

                modelo2->setVisible(true);
                modelo2->setScale(core::vector3df(distancia3/10, 0.5f, 0.5f));
                modelo2->setPosition(core::vector3df((input2.p2.x+input2.p1.x)/2,0,(input2.p2.y+input2.p1.y)/2));
                modelo2->setRotation(core::vector3df(0,angulo3,0));
            }
        }


        if(rayolaser == true && s10->isFinished()){
            rayolaser = false;
            congelado1 = false;
            congelado2 = false;
            congelado3 = false;
            congelado4 = false;
            congelado5 = false;
            congelado6 = false;
        }

        if(rayolaser1 == true && s11->isFinished()){
            rayolaser1 = false;
            modelo2->setVisible(false);
        }



        // ALARMA
        if(enemigos[1]->getEstado() == 3){
            if(cambiao == false){
                //smgr->getMeshManipulator()->setVertexColors(enemigos[1]->getModelo()->getMesh(),irr::video::SColor(255, 0, 255, 0));
                s4 = engine->play3D(alarma,posicion,false,false,true);
                cambiao = true;
            }
            else if(s4->isFinished()){
                aparcao = true;
                vector3df posicion= enemigos[1]->getPosicion()+vector3df(5,0,5);
                vector3df posicion2= enemigos[1]->getPosicion()+vector3df(-5,0,-5);
                enemigos[3]->inicialiazar(0,4,smgr,posicion,pr03);
                enemigos[4]->inicialiazar(0,5,smgr,posicion2,pr04);
                enemigos[3]->setEstado(8);
                enemigos[4]->setEstado(8);
                enemigos[3]->setPunto(enemigos[1]->getPunto());
                enemigos[4]->setPunto(enemigos[1]->getPunto());
                enemigos[1]->setEstado(10);
                kiko = true;
                    //eliminar enemigo
                enemigos[1]->setPosicion(core::vector3df(-1000,0,0), prota->getCuboProta());

            }
        }

        ///SONIDOS ENEMIGOS
        //GUARDIA

        if(enemigos[0]->getEstado() == 1 && escaneando==false) {
                escaneando = true;
                combatiendo = false;
                investigando = false;
                patrullando = false;
                if(engine->isCurrentlyPlaying(combate) || engine->isCurrentlyPlaying(patrullar) || engine->isCurrentlyPlaying(investigar) || engine->isCurrentlyPlaying(escaneo))
                s2->stop();
                s2 = engine->play3D(escaneo,posicion,false,false,true);
        }
        else if(enemigos[0]->getEstado() == 3 && combatiendo==false) {
                escaneando = false;
                combatiendo = true;
                investigando = false;
                patrullando = false;
                if(engine->isCurrentlyPlaying(combate) || engine->isCurrentlyPlaying(patrullar) || engine->isCurrentlyPlaying(investigar) || engine->isCurrentlyPlaying(escaneo))
                s2->stop();
                s2 = engine->play3D(combate,posicion,false,false,true);
        }
        else if(enemigos[0]->getEstado() == 8 && investigando==false) {
                escaneando = false;
                combatiendo = false;
                investigando = true;
                patrullando = false;
                if(engine->isCurrentlyPlaying(combate) || engine->isCurrentlyPlaying(patrullar) || engine->isCurrentlyPlaying(investigar) || engine->isCurrentlyPlaying(escaneo))
                s2->stop();
                s2 = engine->play3D(investigar,posicion,false,false,true);
        }
        else if(enemigos[0]->getEstado() == 0 && patrullando==false) {
                escaneando = false;
                combatiendo = false;
                investigando = false;
                patrullando = true;
                if(engine->isCurrentlyPlaying(combate) || engine->isCurrentlyPlaying(patrullar) || engine->isCurrentlyPlaying(investigar) || engine->isCurrentlyPlaying(escaneo))
                s2->stop();
                s2 = engine->play3D(patrullar,posicion,false,false,true);
        }

        //GUARDIAS DEL DRON LUL

        if(kiko){
            if(enemigos[3]->getEstado() == 1 && escaneandog2==false) {
                escaneandog2 = true;
                combatiendog2 = false;
                investigandog2 = false;
                patrullandog2 = false;
                if(engine->isCurrentlyPlaying(combate) || engine->isCurrentlyPlaying(patrullar) || engine->isCurrentlyPlaying(investigar) || engine->isCurrentlyPlaying(escaneo))
                s6->stop();
                s6 = engine->play3D(escaneo,posicion,false,false,true);
        }
        else if(enemigos[3]->getEstado() == 3 && combatiendog2==false) {
                escaneandog2 = false;
                combatiendog2 = true;
                investigandog2 = false;
                patrullandog2 = false;
                if(engine->isCurrentlyPlaying(combate) || engine->isCurrentlyPlaying(patrullar) || engine->isCurrentlyPlaying(investigar) || engine->isCurrentlyPlaying(escaneo))
                s6->stop();
                s6 = engine->play3D(combate,posicion,false,false,true);
        }
        else if(enemigos[3]->getEstado() == 8 && investigandog2==false) {
                escaneandog2 = false;
                combatiendog2 = false;
                investigandog2 = true;
                patrullandog2 = false;
                if(engine->isCurrentlyPlaying(combate) || engine->isCurrentlyPlaying(patrullar) || engine->isCurrentlyPlaying(investigar) || engine->isCurrentlyPlaying(escaneo))
                s6->stop();
                s6 = engine->play3D(investigar,posicion,false,false,true);
        }
        else if(enemigos[3]->getEstado() == 0 && patrullandog2==false) {
                escaneandog2 = false;
                combatiendog2 = false;
                investigandog2 = false;
                patrullandog2 = true;
                if(engine->isCurrentlyPlaying(combate) || engine->isCurrentlyPlaying(patrullar) || engine->isCurrentlyPlaying(investigar) || engine->isCurrentlyPlaying(escaneo))
                s6->stop();
                s6 = engine->play3D(patrullar,posicion,false,false,true);
        }
        if(enemigos[4]->getEstado() == 1 && escaneandog3==false) {
                escaneandog3 = true;
                combatiendog3 = false;
                investigandog3 = false;
                patrullandog3 = false;
                //if(engine->isCurrentlyPlaying(combate) || engine->isCurrentlyPlaying(patrullar) || engine->isCurrentlyPlaying(investigar) || engine->isCurrentlyPlaying(escaneo))
                //s7->stop();
                s7 = engine->play3D(escaneo,posicion,false,false,true);
        }
        else if(enemigos[4]->getEstado() == 3 && combatiendog3==false) {
                escaneandog3 = false;
                combatiendog3 = true;
                investigandog3 = false;
                patrullandog3 = false;
                //if(engine->isCurrentlyPlaying(combate) || engine->isCurrentlyPlaying(patrullar) || engine->isCurrentlyPlaying(investigar) || engine->isCurrentlyPlaying(escaneo))
                //s7->stop();
                s7 = engine->play3D(combate,posicion,false,false,true);
        }
        else if(enemigos[4]->getEstado() == 8 && investigandog3==false) {
                escaneandog3 = false;
                combatiendog3 = false;
                investigandog3 = true;
                patrullandog3 = false;
                //if(engine->isCurrentlyPlaying(combate) || engine->isCurrentlyPlaying(patrullar) || engine->isCurrentlyPlaying(investigar) || engine->isCurrentlyPlaying(escaneo))
                //s7->stop();
                s7 = engine->play3D(investigar,posicion,false,false,true);
        }
        else if(enemigos[4]->getEstado() == 0 && patrullandog3==false) {
                escaneandog3 = false;
                combatiendog3 = false;
                investigandog3 = false;
                patrullandog3 = true;
                //if(engine->isCurrentlyPlaying(combate) || engine->isCurrentlyPlaying(patrullar) || engine->isCurrentlyPlaying(investigar) || engine->isCurrentlyPlaying(escaneo))
                //s7->stop();
                s7 = engine->play3D(patrullar,posicion,false,false,true);
        }

        }


        //DRON

        if(enemigos[1]->getEstado() == 1 && escaneando3==false) {
                escaneando3 = true;
                investigando3 = false;
                patrullando3 = false;
                if(engine->isCurrentlyPlaying(escaneodron) || engine->isCurrentlyPlaying(patrullardron) || engine->isCurrentlyPlaying(investigardron))
                s5->stop();
                s5 = engine->play3D(escaneodron,posicion,false,false,true);
        }
        else if(enemigos[1]->getEstado() == 8 && investigando3==false) {
                escaneando3 = false;
                investigando3 = true;
                patrullando3 = false;
                if(engine->isCurrentlyPlaying(escaneodron) || engine->isCurrentlyPlaying(patrullardron) || engine->isCurrentlyPlaying(investigardron))
                s5->stop();
                s5 = engine->play3D(investigardron,posicion,false,false,true);
        }
        else if(enemigos[1]->getEstado() == 0 && patrullando3==false) {
                escaneando3 = false;
                investigando3 = false;
                patrullando3 = true;
                if(engine->isCurrentlyPlaying(escaneodron) || engine->isCurrentlyPlaying(patrullardron) || engine->isCurrentlyPlaying(investigardron))
                s5->stop();
                s5 = engine->play3D(patrullardron,posicion,false,false,true);
        }


        //MEDICO
        if(enemigos[2]->getEstado() == 1 && escaneando2==false) {
                escaneando2 = true;
                combatiendo2 = false;
                investigando2 = false;
                patrullando2 = false;
                huyendo = false;
                if(engine->isCurrentlyPlaying(investigarmedico) || engine->isCurrentlyPlaying(patrullarmedico) || engine->isCurrentlyPlaying(huir)|| engine->isCurrentlyPlaying(defensa) || engine->isCurrentlyPlaying(escaneomedico))
                s3->stop();
                s3 = engine->play3D(escaneomedico,posicion,false,false,true);
        }
        else if(enemigos[2]->getEstado() == 9 && combatiendo2==false) {
                escaneando2 = false;
                combatiendo2 = true;
                investigando2 = false;
                patrullando2 = false;
                huyendo = false;
                if(engine->isCurrentlyPlaying(investigarmedico) || engine->isCurrentlyPlaying(patrullarmedico) || engine->isCurrentlyPlaying(huir)|| engine->isCurrentlyPlaying(defensa) || engine->isCurrentlyPlaying(escaneomedico))
                s3->stop();
                s3 = engine->play3D(defensa,posicion,false,false,true);
        }
         if(enemigos[2]->getEstado() == 8 && investigando2==false) {
                escaneando2 = false;
                combatiendo2 = false;
                investigando2 = true;
                patrullando2 = false;
                huyendo = false;
                if(engine->isCurrentlyPlaying(investigarmedico) || engine->isCurrentlyPlaying(patrullarmedico) || engine->isCurrentlyPlaying(huir)|| engine->isCurrentlyPlaying(defensa) || engine->isCurrentlyPlaying(escaneomedico))
                s3->stop();
                s3 = engine->play3D(investigarmedico,posicion,false,false,true);
        }
         if(enemigos[2]->getEstado() == 0 && patrullando2==false) {
                escaneando2 = false;
                combatiendo2 = false;
                investigando2 = false;
                patrullando2 = true;
                huyendo = false;
                if(engine->isCurrentlyPlaying(investigarmedico) || engine->isCurrentlyPlaying(patrullarmedico) || engine->isCurrentlyPlaying(huir)|| engine->isCurrentlyPlaying(defensa) || engine->isCurrentlyPlaying(escaneomedico))
                s3->stop();
                s3 = engine->play3D(patrullarmedico,posicion,false,false,true);
        }
         if(enemigos[2]->getEstado() == 3 && huyendo==false) {
                escaneando2 = false;
                combatiendo2 = false;
                investigando2 = false;
                patrullando2 = false;
                huyendo = true;
                if(engine->isCurrentlyPlaying(investigarmedico) || engine->isCurrentlyPlaying(patrullarmedico) || engine->isCurrentlyPlaying(huir)|| engine->isCurrentlyPlaying(defensa) || engine->isCurrentlyPlaying(escaneomedico))
                s3->stop();
                s3 = engine->play3D(huir,posicion,false,false,true);
        }


        //// TORRETA


        input.p1.Set(enemigos[5]->getBody()->GetPosition().x, enemigos[5]->getBody()->GetPosition().y);	//	Punto	inicial	del	rayo
        input.p2.Set(prota->getBody()->GetPosition().x, prota->getBody()->GetPosition().y);	//	Punto	final	del	rayo

        bool    hitmuro     =   muro1->body15->GetFixtureList()->RayCast(&output,	input,	0);
        bool    hitprota	=	prota->getBody()->GetFixtureList()->RayCast(&output,	input,	0);


        distancia = sqrt(pow(input.p2.x-input.p1.x, 2)+pow(input.p2.y-input.p1.y, 2));
        angulo2 = atan2f((input.p2.y-input.p1.y) , -(input.p2.x-input.p1.x)) * 180.f / irr::core::PI;


            if(hitprota && distancia<90 && !hitmuro && angulo2>-150 && angulo2<40){

                   // b2Vec2 hitPoint = input.p1+output.fraction * (input.p2 - input.p1);
                   // b2Vec2 normal = output.normal;

                enemigos[5]->getBody()->SetTransform(enemigos[5]->getBody()->GetPosition(), angulo2);
                enemigos[5]->getModelo()->setRotation(core::vector3df(0,enemigos[5]->getBody()->GetAngle(),0));

                if(!kiko2){
                    s9 = engine->play3D(aviso,posicion,false,false,true);
                    kiko2 = true;
                }
                if(s9->isFinished()){


                if(engine->isCurrentlyPlaying(lasertorreta)==false)
                        s8 = engine->play3D(lasertorreta,posicion,true,false,true);



                modelo->setVisible(true);
                modelo->setScale(core::vector3df(distancia/10, 0.5f, 0.5f));
                modelo->setPosition(core::vector3df((input.p2.x+input.p1.x)/2,0,(input.p2.y+input.p1.y)/2));
                modelo->setRotation(core::vector3df(0,enemigos[5]->getBody()->GetAngle(),0));
                smgr->getMeshManipulator()->setVertexColors(enemigos[5]->getModelo()->getMesh(),irr::video::SColor(255, 255, 255, 255));

                vidaProta=prota->getVida();
                vidaProta-=0.1*DeltaTime;
                prota->setVida(vidaProta);

                }

            }
            else{

                if(engine->isCurrentlyPlaying(lasertorreta))
                s8->stop();

                smgr->getMeshManipulator()->setVertexColors(enemigos[5]->getModelo()->getMesh(),irr::video::SColor(0, 0, 0, 0));
                modelo->setVisible(false);

                kiko2 = false;

            }

        //ATAQUE ENEMIGO
        if(enemigos[0]->getEstado() == 7){
            vidaProta=prota->getVida();
            vidaProta-=0.1*DeltaTime;
            prota->setVida(vidaProta);

        }
        if(prota->getVida()<=0){
            prota->muerte();
        }

        DeltaTime = timer->getTime() - TimeStamp;
        TimeStamp = timer->getTime();
        tiempo.update();

        camera->setPosition(cameraPos);
        camera->setTarget(cameraTar);
        ///UPDATES ENEMIGO
        //Guardia
        if(!congelado1)
        enemigos[0]->update(prota->getCuboProta(), tiempo, enemigos);
        //Alarma
         if(!congelado2)
        enemigos[1]->update(prota->getCuboProta(), tiempo, enemigos);
        //Medico
         if(!congelado3)
        enemigos[2]->update(prota->getCuboProta(), tiempo, enemigos);
        if(aparcao){
                 if(!congelado4)
        enemigos[3]->update(prota->getCuboProta(), tiempo, enemigos);
                 if(!congelado5)
        enemigos[4]->update(prota->getCuboProta(), tiempo, enemigos);
        }
        enemigos[6]->update(prota->getCuboProta(), tiempo, enemigos);
        ///SET POSITION ENEMIGOS
        enemigos[0]->setPosicion(enemigos[0]->getCuboEnemigo(), prota->getCuboProta());

        //Si el dron no se ha convertido en alarma
        if(cambiao == false)
            enemigos[1]->setPosicion(enemigos[1]->getCuboEnemigo(), prota->getCuboProta());
        if(aparcao){
            enemigos[3]->setPosicion(enemigos[3]->getCuboEnemigo(), prota->getCuboProta());
            enemigos[4]->setPosicion(enemigos[4]->getCuboEnemigo(), prota->getCuboProta());
        }
        enemigos[2]->setPosicion(enemigos[2]->getCuboEnemigo(), prota->getCuboProta());
        enemigos[6]->setPosicion(enemigos[6]->getCuboEnemigo(), prota->getCuboProta());


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
