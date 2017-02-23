#include <irrlicht.h>
#include <Box2D/Box2D.h>
#include "include/Enemigo.h"
#include <irrKlang.h>
#include "irrKlang/conio.h"
#include <iostream>
#include "include/Map.h"
#include "include/CMainMenu.h"

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



int main()
{

    CMainMenu menu;

    if (menu.run())
    {

        MyEventReceiver receiver;
        float posx, posy, posz;
        vector3df posmuro;

        World* world;
        world = World::Instance();

        //Objeto principal que nos permite interactuar con el motor
        IrrlichtDevice* device = createDevice(video::EDT_OPENGL,core::dimension2d<u32>(1360, 768), 16, false, false, false, &receiver);
        device->setWindowCaption(L"IKI" );
        ITimer* timer = device->getTimer();
        f32 TimeStamp = timer->getTime();
        f32 DeltaTime = timer->getTime() - TimeStamp;


        ISceneManager* smgr= device->getSceneManager();         //Gestion de la escena
        IVideoDriver* driver= device->getVideoDriver();         //Ciclo del juego
        IGUIEnvironment* guienv= device->getGUIEnvironment();   //Interfaz de usuario



        ///CAMARA
        ICameraSceneNode * camera = smgr->addCameraSceneNode(0,core::vector3df(190, 30, 40),core::vector3df(170,-10,40));

        vector3df cameraPos = camera->getPosition();
        vector3df cameraTar = camera->getTarget();



        Map *Mapa= new Map;
        if(Mapa)
        {
            Mapa->loadMap(smgr);

        }





///PATRULLAS

        //typedef Mapa->patrullas hola;
        Mapa->patrullas->at(0)->pp->setNext(Mapa->patrullas->at(1)->pp);
        Mapa->patrullas->at(1)->pp->setNext(Mapa->patrullas->at(0)->pp);
        Mapa->patrullas->at(0)->pp->setPrev(Mapa->patrullas->at(1)->pp);
        Mapa->patrullas->at(1)->pp->setPrev(Mapa->patrullas->at(0)->pp);

        PatrolRoute pr03;
        pr03.setInicial(Mapa->patrullas->at(0)->pp);
        pr03.setFinal(Mapa->patrullas->at(0)->pp->getPrev());

        ///4 Enemigos[4] Guardia3
        PatrolPoint *pp15, *pp16;
        pp15 = new PatrolPoint(irr::core::vector3df(70,0,250));
        pp16 = new PatrolPoint(irr::core::vector3df(-10,0,150));

        pp15->setNext(pp16);
        pp16->setNext(pp15);
        pp15->setPrev(pp16);
        pp16->setPrev(pp15);

        PatrolRoute pr04;
        pr04.setInicial(pp15);
        pr04.setFinal(pp15->getPrev());
        ///1-> Enemigos[2] Medico

        Mapa->patrullas->at(2)->pp->setNext(Mapa->patrullas->at(3)->pp);
        Mapa->patrullas->at(3)->pp->setNext(Mapa->patrullas->at(4)->pp);
        Mapa->patrullas->at(4)->pp->setNext(Mapa->patrullas->at(5)->pp);
        Mapa->patrullas->at(5)->pp->setNext(Mapa->patrullas->at(2)->pp);
        Mapa->patrullas->at(3)->pp->setPrev(Mapa->patrullas->at(2)->pp);
        Mapa->patrullas->at(4)->pp->setPrev(Mapa->patrullas->at(3)->pp);
        Mapa->patrullas->at(5)->pp->setPrev(Mapa->patrullas->at(4)->pp);
        Mapa->patrullas->at(2)->pp->setPrev(Mapa->patrullas->at(5)->pp);

        PatrolRoute pr01;
        pr01.setInicial(Mapa->patrullas->at(2)->pp);
        pr01.setFinal(Mapa->patrullas->at(2)->pp->getPrev());

        ///2-> Enemigos[6] GuardiaNuevo

        Mapa->patrullas->at(8)->pp->setNext(Mapa->patrullas->at(9)->pp);
        Mapa->patrullas->at(9)->pp->setNext(Mapa->patrullas->at(10)->pp);
        Mapa->patrullas->at(10)->pp->setNext(Mapa->patrullas->at(11)->pp);
        Mapa->patrullas->at(11)->pp->setNext(Mapa->patrullas->at(8)->pp);
        Mapa->patrullas->at(8)->pp->setPrev(Mapa->patrullas->at(11)->pp);
        Mapa->patrullas->at(11)->pp->setPrev(Mapa->patrullas->at(10)->pp);
        Mapa->patrullas->at(10)->pp->setPrev(Mapa->patrullas->at(9)->pp);
        Mapa->patrullas->at(9)->pp->setPrev(Mapa->patrullas->at(8)->pp);
        PatrolRoute pr02;
        pr02.setInicial(Mapa->patrullas->at(8)->pp);
        pr02.setFinal(Mapa->patrullas->at(8)->pp->getPrev());
        ///5 -> Enemigo[0] Guardia
        Mapa->patrullas->at(0)->pp->setNext(Mapa->patrullas->at(1)->pp);
        Mapa->patrullas->at(1)->pp->setNext(Mapa->patrullas->at(0)->pp);
        Mapa->patrullas->at(0)->pp->setPrev(Mapa->patrullas->at(1)->pp);
        Mapa->patrullas->at(1)->pp->setPrev(Mapa->patrullas->at(0)->pp);

        PatrolRoute pr05;
        pr05.setInicial(Mapa->patrullas->at(0)->pp);
        pr03.setFinal(Mapa->patrullas->at(0)->pp->getPrev());

        ///5 -> Enemigo[1] Dron

        Mapa->patrullas->at(6)->pp->setNext(Mapa->patrullas->at(7)->pp);
        Mapa->patrullas->at(7)->pp->setNext(Mapa->patrullas->at(6)->pp);

        PatrolRoute pr06;
        pr06.setInicial(Mapa->patrullas->at(6)->pp);
        pr06.setFinal(Mapa->patrullas->at(6)->pp->getPrev());




        int danio = 0;

        //std::cout << "1\n";

        ///ENEMIGOS
        Enemigo  *enemigos[7];
        for(int i=0; i<7; i++)
        {
            enemigos[i]= new Enemigo;
        }
        if(enemigos[0])
            enemigos[0]->inicialiazar(0,0, smgr,vector3df(Mapa->patrullas->at(0)->pp->getPunto()),pr05);
        if(enemigos[1])
            enemigos[1]->inicialiazar(1,1, smgr,vector3df(Mapa->patrullas->at(6)->pp->getPunto()),pr06);
        if(enemigos[2])
            enemigos[2]->inicialiazar(2,2,smgr,vector3df(Mapa->patrullas->at(2)->pp->getPunto()),pr01);
        if(enemigos[5])
            enemigos[5]->inicialiazar2(smgr, vector3df(Mapa->patrullas->at(12)->pp->getPunto()));
        if(enemigos[6])
            enemigos[6]->inicialiazar(0,6,smgr,vector3df(Mapa->patrullas->at(8)->pp->getPunto()),pr02);


        smgr->getMeshManipulator()->setVertexColors(enemigos[0]->getModelo()->getMesh(),irr::video::SColor(255, 255, 0, 0));


        ///PLAYER
        Player *prota= new Player;
        if(prota)
        {
            prota->inicializar(smgr,driver);

        }

        for(int i=0; i<7; i++)
        {
            enemigos[i]->setMuro(Mapa, prota);
        }

        ///RATON
        core::plane3df plane(prota->getCuboProta(), core::vector3df(0, -1, 0));
        core::vector3df mousePosition= core::vector3df(0,0,0);
        vector3df toMousePositionObj;
        vector3df toMousePosition;
        core::line3df ray(mousePosition, prota->getCuboProta());
        core::line3df ray11(mousePosition, prota->getCuboProta());
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
        ISoundSource* palancaon = engine->addSoundSourceFromFile("sonidos/palancaon.wav");
        ISoundSource* palancaoff = engine->addSoundSourceFromFile("sonidos/palancaoff.wav");
        ISoundSource* aceite = engine->addSoundSourceFromFile("sonidos/agua.wav");
        ISoundSource* golpe = engine->addSoundSourceFromFile("sonidos/metal1.wav");
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
        ISound* s12;
        ISound* s13;
        ISound* s14;

        pasos1->setDefaultVolume(2.0f);
        pasos2->setDefaultVolume(1.0f);


        ///SUELO


        IMesh *mesh = smgr->getGeometryCreator()->createCubeMesh(vector3df(600.f, -5.f, 600.f));
        scene::IMeshSceneNode *suelo = smgr->addMeshSceneNode(mesh);

        if(suelo)
        {
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
        bool hayobj= false, hayobj2 = false, vez= false, vez2 = false, vez3 = false;
        bool centinela= false;
        bool tocado= false;
        bool stop= true;
        bool kiko= false;
        bool kiko2= false;
        bool rayolaser = false;
        bool rayolaser1 = false;
        bool cerrada = true;
        bool unatarjeta = false;
        bool abriendose = false;
        bool cerrandose = true;
        bool mecagoyaendios = true;


        //PERCEPCION SENSONRIAL

        b2RayCastInput input;
        input.maxFraction	=	1.0f;
        b2RayCastOutput	output;
        b2RayCastInput input2;
        input2.maxFraction	=	1.0f;
        b2RayCastOutput	output2;
        float angulo2 = 0;
        float distancia = 0;
        scene::IMesh *rayo = smgr->getGeometryCreator()->createCubeMesh(core::vector3df(10.f, 1.f, 1.f));
        scene::IMeshSceneNode *modelo = smgr->addMeshSceneNode(rayo);
        modelo->setVisible(false);

        //RAYO PARALIZADOR

        float angulo3 = 0;
        float distancia3 = 0;
        scene::IMesh *rayo2 = smgr->getGeometryCreator()->createCubeMesh(core::vector3df(10.f, 0.5f, 0.5f));
        scene::IMeshSceneNode *modelo2 = smgr->addMeshSceneNode(rayo2);
        modelo2->setVisible(false);

        int lastFPS = -1;
        u32 myClock;
        int frame = 0;
        Time tiempo;
        tiempo.set(device);
        float vidaProta;
        float angulo;
        int n, balamenos= 0;
        float objvida= 0.0f;
        int objlaser= 0;


        ///CICLO DEL JUEGO
        while(device->run())
        {

            driver->beginScene(true, true, SColor(255, 100, 101, 140));


            ///raton
            if(receiver.GetMouseState().RightButtonDown)
            {
                stop= false;

                ray = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(
                          receiver.GetMouseState().Position, camera);
                angulo = atan2f((mousePosition.Z-prota->getModelo()->getPosition().Z) ,
                                -(mousePosition.X-prota->getModelo()->getPosition().X)) * 180.f / irr::core::PI;
                prota->getBody()->SetTransform(prota->getBody()->GetPosition(), angulo);
                prota->getModelo()->setRotation(core::vector3df(0,prota->getBody()->GetAngle(),0));
                prota->getEsfera()->setRotation(core::vector3df(0,prota->getBody()->GetAngle(),0));
            }

            if(plane.getIntersectionWithLine(ray.start, ray.getVector(), mousePosition))
            {

                toMousePosition = mousePosition - prota->getCuboProta();

                if(toMousePosition.getLength() <= 1)
                {
                    prota->moverBody(vector3df(0,0,0));
                    prota->ismoving = false;
                    if(pasosP==true || pasos2P==true)
                    {
                        s1->stop();
                        pasosP = false;
                        pasos2P = false;
                    }

                    stop= true;
                }
                else
                {
                    prota->ismoving = true;
                    prota->moverBody(toMousePosition);
                    if(pasosP==false && !receiver.isKeyDown(KEY_LSHIFT))
                    {
                        if(engine->isCurrentlyPlaying(pasos2))
                            s1->stop();
                        s1 = engine->play3D(pasos1,posicion,true,false,true);
                        pasosP = true;
                        pasos2P = false;
                    }
                    else if (pasos2P==false && receiver.isKeyDown(KEY_LSHIFT))
                    {
                        if(engine->isCurrentlyPlaying(pasos1))
                            s1->stop();
                        s1 = engine->play3D(pasos2,posicion,true,false,true);
                        pasos2P = true;
                        pasosP = false;

                    }
                    stop= true;
                }
            }


            if(prota->getLaser() > 0)
            {
                if(receiver.isKeyDown(KEY_KEY_Q) && !rayolaser)
                {
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
                    input2.p2.Set(prota->getCuboProta().X+((toMousePosition.X/modulo)*30), prota->getCuboProta().Z+((toMousePosition.Z/modulo)*30));

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

                    if(kiko)
                    {

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


            if(rayolaser == true && s10->isFinished())
            {
                rayolaser = false;
                congelado1 = false;
                congelado2 = false;
                congelado3 = false;
                congelado4 = false;
                congelado5 = false;
                congelado6 = false;
            }

            if(rayolaser1 == true && s11->isFinished())
            {
                rayolaser1 = false;
                modelo2->setVisible(false);
            }


            if(enemigos[1]->getEstado() == 3)
            {
                if(cambiao == false)
                {
                    //smgr->getMeshManipulator()->setVertexColors(enemigos[1]->getModelo()->getMesh(),irr::video::SColor(255, 0, 255, 0));
                    s4 = engine->play3D(alarma,posicion,false,false,true);
                    cambiao = true;
                }
                else if(s4->isFinished())
                {
                    aparcao = true;
                    kiko = true;
                    vector3df posicion= enemigos[1]->getPosicion()+vector3df(5,0,5);
                    vector3df posicion2= enemigos[1]->getPosicion()+vector3df(-5,0,-5);
                    enemigos[3]->inicialiazar(0,4,smgr,posicion,pr03);
                    enemigos[4]->inicialiazar(0,5,smgr,posicion2,pr04);
                    enemigos[3]->setEstado(8);
                    enemigos[4]->setEstado(8);
                    enemigos[3]->setPunto(enemigos[1]->getPunto());
                    enemigos[4]->setPunto(enemigos[1]->getPunto());
                    enemigos[1]->setEstado(10);

                    //eliminar enemigo
                    enemigos[1]->matar();

                }
            }


            prota->setPosition(vector3df(prota->getBody()->GetPosition().x, 0, prota->getBody()->GetPosition().y));

            ///VIDA PROTA




            //MECANISMOS DEL MAPA Y TAL

            if((sqrt(pow(Mapa->objetos->at(0)->body->GetPosition().y-prota->getBody()->GetPosition().y, 2) + pow(Mapa->objetos->at(0)->body->GetPosition().x-prota->getBody()->GetPosition().x, 2)))/10 < 0.3)
                hayobj = true;
            if((sqrt(pow(Mapa->objetos->at(1)->body->GetPosition().y-prota->getBody()->GetPosition().y, 2) + pow(Mapa->objetos->at(1)->body->GetPosition().x-prota->getBody()->GetPosition().x, 2)))/10 < 0.3)
            {
                if(vez == false)
                {
                    objlaser= prota->getLaser() + 5;
                    std::cout <<"balas: "<<objlaser<<" \n";
                    prota->setLaser(objlaser);
                    Mapa->objetos->at(1)->Desactivar();
                    vez = true;
                }

            }

            if((sqrt(pow(Mapa->objetos->at(2)->body->GetPosition().y-prota->getBody()->GetPosition().y, 2) + pow(Mapa->objetos->at(2)->body->GetPosition().x-prota->getBody()->GetPosition().x, 2)))/10 < 0.3)
            {
                if(vez2 == false)
                {
                    objvida= prota->getVida() + 1.0f;
                    std::cout <<"vida: "<<objvida<<" \n";
                    prota->setVida(objvida);
                    prota->setNoMuerto();
                    smgr->getMeshManipulator()->setVertexColors(prota->getModelo()->getMesh(),video::SColor(255,255,255, 255));
                    Mapa->objetos->at(2)->Desactivar();
                    vez2 = true;
                }

            }

            if((sqrt(pow(Mapa->objetos->at(3)->body->GetPosition().y-prota->getBody()->GetPosition().y, 2) + pow(Mapa->objetos->at(3)->body->GetPosition().x-prota->getBody()->GetPosition().x, 2)))/10 < 0.3)
            {
                if(vez3 == false)
                {

                    s12 = engine->play3D(aceite,posicion,false,false,true);
                    Mapa->objetos->at(3)->Desactivar();
                    vez3 = true;

                }

            }


            if(hayobj)
            {

                Mapa->objetos->at(0)->Desactivar();

                if((sqrt(pow(Mapa->puertas->at(0)->body->GetPosition().y-prota->getBody()->GetPosition().y, 2) + pow(Mapa->puertas->at(0)->body->GetPosition().x-prota->getBody()->GetPosition().x, 2)))/10 < 0.3)
                {

                    Mapa->puertas->at(0)->Desactivar();
                }
                else
                {
                    Mapa->puertas->at(0)->Activar();
                }


            }


            if((sqrt(pow(Mapa->puertas->at(1)->body->GetPosition().y-prota->getBody()->GetPosition().y, 2) + pow(Mapa->puertas->at(1)->body->GetPosition().x-prota->getBody()->GetPosition().x, 2)))/10 < 0.3)
            {

                Mapa->puertas->at(1)->Desactivar();
            }
            else
            {
                Mapa->puertas->at(1)->Activar();
            }

            //PRENSA/APISONADORA (COMO SE LLAME LUL)

            if(receiver.GetMouseState().LeftButtonDown && (sqrt(pow(Mapa->palancas->at(0)->body->GetPosition().y-prota->getBody()->GetPosition().y, 2) + pow(Mapa->palancas->at(0)->body->GetPosition().x-prota->getBody()->GetPosition().x, 2)))/10 < 0.3)
            {
                if(cerrada && engine->isCurrentlyPlaying(palancaoff) == false)
                {

                    smgr->getMeshManipulator()->setVertexColors(Mapa->palancas->at(0)->modelo->getMesh(),video::SColor(0, 0, 255, 0));
                    s12 = engine->play3D(palancaon,posicion,false,false,true);
                    cerrada = false;
                }
                else if (!cerrada && engine->isCurrentlyPlaying(palancaon) == false)
                {
                    smgr->getMeshManipulator()->setVertexColors(Mapa->palancas->at(0)->modelo->getMesh(),video::SColor(0, 128, 128, 128));
                    s12 = engine->play3D(palancaoff,posicion,false,false,true);
                    cerrada = true;
                }
            }

            if(cerrada == true)
            {
                if((sqrt(pow(Mapa->apisonadoras->at(0)->body->GetPosition().y-Mapa->apisonadoras->at(1)->body->GetPosition().y, 2) + pow(Mapa->apisonadoras->at(0)->body->GetPosition().x-Mapa->apisonadoras->at(1)->body->GetPosition().x, 2)))/10 < 0.5)
                {
                    abriendose = true;
                    cerrandose = false;
                }

                if((sqrt(pow(Mapa->apisonadoras->at(0)->body->GetPosition().y-Mapa->apisonadoras->at(1)->body->GetPosition().y, 2) + pow(Mapa->apisonadoras->at(0)->body->GetPosition().x-Mapa->apisonadoras->at(1)->body->GetPosition().x, 2)))/10 > 1.0)
                {
                    abriendose = false;
                    cerrandose = true;
                }
                if(abriendose)
                {
                    Mapa->apisonadoras->at(0)->body->SetLinearVelocity(b2Vec2(2, 0));
                    Mapa->apisonadoras->at(1)->body->SetLinearVelocity(b2Vec2(-2, 0));
                }
                else if(cerrandose)
                {
                    Mapa->apisonadoras->at(0)->body->SetLinearVelocity(b2Vec2(-2, 0));
                    Mapa->apisonadoras->at(1)->body->SetLinearVelocity(b2Vec2(2, 0));
                }

            }
            else
            {
                Mapa->apisonadoras->at(0)->body->SetLinearVelocity(b2Vec2(0, 0));
                Mapa->apisonadoras->at(1)->body->SetLinearVelocity(b2Vec2(0, 0));
            }

            Mapa->apisonadoras->at(0)->setPosition(vector3df(Mapa->apisonadoras->at(0)->body->GetPosition().x, 0, Mapa->apisonadoras->at(0)->body->GetPosition().y));
            Mapa->apisonadoras->at(1)->setPosition(vector3df(Mapa->apisonadoras->at(1)->body->GetPosition().x, 0, Mapa->apisonadoras->at(1)->body->GetPosition().y));


            //ATAQUE PROTA

            for(n= 0; n <= 6; n++)
            {
                if(enemigos[n]->getCreado())
                {
                    if(sqrt(pow(enemigos[n]->getBody()->GetPosition().y-prota->getBody()->GetPosition().y, 2) + pow(enemigos[n]->getBody()->GetPosition().x-prota->getBody()->GetPosition().x, 2))/10 < 0.4)
                    {
                        input2.p1.Set(prota->getBody()->GetPosition().x, prota->getBody()->GetPosition().y);	//	Punto	inicial	del	rayo
                        input2.p2.Set(enemigos[n]->getBody()->GetPosition().x, enemigos[n]->getBody()->GetPosition().y);	//	Punto	final	del	rayo


                        float angulo4 = atan2f((input2.p2.y-input2.p1.y) , -(input2.p2.x-input2.p1.x)) * 180.f / irr::core::PI;



                        if(!enemigos[n]->getMuerto() && receiver.GetMouseState().LeftButtonDown && engine->isCurrentlyPlaying(golpe) == false)
                        {


                            if(angulo+180 < angulo4+210 && angulo+180 > angulo4+150)
                            {
                                if(enemigos[n]->getEstado()==0 || enemigos[n]->getEstado()==2)
                                {
                                    s14 = engine->play3D(golpe,posicion,false,false,true);
                                    enemigos[n]->matar();
                                }
                                else
                                {
                                    s14 = engine->play3D(golpe,posicion,false,false,true);
                                    enemigos[n]->quitarVida();
                                }
                            }
                        }
                    }
                }
            }


            ////Apisonadora mata gente
            if(cerrandose && cerrada)
            {
                for(n= 0; n <= 6; n++)
                {
                    if(enemigos[n]->getCreado())
                    {
                        if(sqrt(pow(enemigos[n]->getBody()->GetPosition().y-Mapa->patrullas->at(13)->pp->getPunto().Z, 2) + pow(enemigos[n]->getBody()->GetPosition().x-Mapa->patrullas->at(13)->pp->getPunto().X, 2))/10 < 0.1)
                        {
                            enemigos[n]->matar();
                        }
                    }

                }
                if(sqrt(pow(prota->getBody()->GetPosition().y-Mapa->patrullas->at(13)->pp->getPunto().Z, 2) + pow(prota->getBody()->GetPosition().x-Mapa->patrullas->at(13)->pp->getPunto().X, 2))/10 < 0.1){
                    prota->setVida(0);
                }
            }

            //// TORRETA


            input.p1.Set(enemigos[5]->getBody()->GetPosition().x, enemigos[5]->getBody()->GetPosition().y);	//	Punto	inicial	del	rayo
            input.p2.Set(prota->getBody()->GetPosition().x, prota->getBody()->GetPosition().y);	//	Punto	final	del	rayo

            distancia = sqrt(pow(input.p2.x-input.p1.x, 2)+pow(input.p2.y-input.p1.y, 2));
            angulo2 = atan2f((input.p2.y-input.p1.y) , -(input.p2.x-input.p1.x)) * 180.f / irr::core::PI;

            for (int i = 0; i < Mapa->muros->size(); i++)
            {

                if (Mapa->muros->at(i)->body->GetFixtureList()->RayCast(&output,	input,	0))
                {
                    mecagoyaendios =  true;
                    break;
                }
                else
                    mecagoyaendios =  false;

            }

            if(distancia<25 && !mecagoyaendios && angulo2>-180 && angulo2<-40)
            {



                enemigos[5]->getBody()->SetTransform(enemigos[5]->getBody()->GetPosition(), angulo2);
                enemigos[5]->getModelo()->setRotation(core::vector3df(0,enemigos[5]->getBody()->GetAngle(),0));

                if(!kiko2)
                {
                    s9 = engine->play3D(aviso,posicion,false,false,true);
                    kiko2 = true;
                }
                if(s9->isFinished())
                {


                    if(engine->isCurrentlyPlaying(lasertorreta)==false)
                        s8 = engine->play3D(lasertorreta,posicion,true,false,true);



                    modelo->setVisible(true);
                    modelo->setScale(core::vector3df(distancia/10, 0.5f, 0.5f));
                    modelo->setPosition(core::vector3df((input.p2.x+input.p1.x)/2,0,(input.p2.y+input.p1.y)/2));
                    modelo->setRotation(core::vector3df(0,enemigos[5]->getBody()->GetAngle(),0));
                    smgr->getMeshManipulator()->setVertexColors(enemigos[5]->getModelo()->getMesh(),irr::video::SColor(255, 255, 255, 255));

                    vidaProta=prota->getVida();

                    if(vidaProta >=0)
                    {
                        vidaProta-=0.1*DeltaTime;
                        prota->setVida(vidaProta);
                    }

                }

            }
            else
            {

                if(engine->isCurrentlyPlaying(lasertorreta))
                    s8->stop();

                smgr->getMeshManipulator()->setVertexColors(enemigos[5]->getModelo()->getMesh(),irr::video::SColor(0, 0, 0, 0));
                modelo->setVisible(false);

                kiko2 = false;

            }


            //TARJETA CAE DE ENEMIGO

            if(enemigos[6]->getMuerto() && unatarjeta == false)
            {
                unatarjeta = true;
                Mapa->objetos->push_back(new MapComponent(0, core::vector3df(enemigos[6]->getPosicion().X+3, 0, enemigos[6]->getPosicion().Z+3), smgr, 4));
            }


            if(unatarjeta)
            {

                if((sqrt(pow(Mapa->objetos->at(4)->body->GetPosition().y-prota->getBody()->GetPosition().y, 2) + pow(Mapa->objetos->at(4)->body->GetPosition().x-prota->getBody()->GetPosition().x, 2)))/10 < 0.3)
                    hayobj2 = true;

                if(hayobj2)
                {

                    Mapa->objetos->at(4)->Desactivar();

                    if((sqrt(pow(Mapa->puertas->at(2)->body->GetPosition().y-prota->getBody()->GetPosition().y, 2) + pow(Mapa->puertas->at(2)->body->GetPosition().x-prota->getBody()->GetPosition().x, 2)))/10 < 0.3)
                    {

                        Mapa->puertas->at(2)->Desactivar();
                    }
                    else
                    {
                        Mapa->puertas->at(2)->Activar();
                    }


                }


            }


            ///CAMARA
            if(receiver.isKeyDown(KEY_ESCAPE))
            {
                device->closeDevice();
                return 0;
            }

            if(receiver.isKeyDown(KEY_LSHIFT))
            {
                prota->velocidad = 2.5f;
                prota->sigilo = true;
            }
            else if(engine->isCurrentlyPlaying(aceite) == true)
            {
                prota->velocidad = 10.f;
                prota->sigilo = true;
            }
            else
            {
                prota->velocidad = 5.5f;
                prota->sigilo = false;
            }



            DeltaTime = timer->getTime() - TimeStamp;
            TimeStamp = timer->getTime();
            tiempo.update();

            camera->setTarget(prota->getCuboProta());
            camera->setPosition(vector3df(prota->getCuboProta().X + 15, prota->getCuboProta().Y + 30, prota->getCuboProta().Z));

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
            if(aparcao)
            {
                if(!congelado4)
                    enemigos[3]->update(prota->getCuboProta(), tiempo, enemigos);
                if(!congelado5)
                    enemigos[4]->update(prota->getCuboProta(), tiempo, enemigos);
            }
            enemigos[6]->update(prota->getCuboProta(), tiempo, enemigos);


            ///SET POSITION ENEMIGOS
            enemigos[0]->setPosicion();
            //Si el dron no se ha convertido en alarma
            if(cambiao == false)
                enemigos[1]->setPosicion();
            if(aparcao)
            {
                enemigos[3]->setPosicion();
                enemigos[4]->setPosicion();
            }
            enemigos[2]->setPosicion();
            enemigos[6]->setPosicion();


            world->Step(DeltaTime);
            world->getWorld()->ClearForces();

            //std::cout << "nigg\n";
            smgr->drawAll();
            guienv->drawAll();

            if(prota->getVida() >= 3)
            {
                driver->draw2DImage(image, position2d<s32>(10, 10), rect<s32>(0, 0, 47, 47), 0, SColor(255, 255, 255, 255), true);
                driver->draw2DImage(image, position2d<s32>(60, 10), rect<s32>(0, 0, 47, 47), 0, SColor(255, 255, 255, 255), true);
                driver->draw2DImage(image, position2d<s32>(110, 10), rect<s32>(0, 0, 47, 47), 0, SColor(255, 255, 255, 255), true);
            }
            else if(prota->getVida() >= 2)
            {
                driver->draw2DImage(image, position2d<s32>(10, 10), rect<s32>(0, 0, 47, 47), 0, SColor(255, 255, 255, 255), true);
                driver->draw2DImage(image, position2d<s32>(60, 10), rect<s32>(0, 0, 47, 47), 0, SColor(255, 255, 255, 255), true);
            }
            else if(prota->getVida() >= 1)
            {
                driver->draw2DImage(image, position2d<s32>(10, 10), rect<s32>(0, 0, 47, 47), 0, SColor(255, 255, 255, 255), true);
            }

            driver->endScene();
            //std::cout << "yep\n";
        }

        device->drop();
        engine->drop();

    }


    return 0;

}


