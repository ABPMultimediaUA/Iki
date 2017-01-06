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


    //std::cout << "1\n";

    ///ENEMIGOS
    Enemigo  *enemigos[6];
    for(int i=0;i<6;i++){
        enemigos[i]= new Enemigo;
    }
    if(enemigos[0])
        enemigos[0]->inicialiazar(0,0, smgr, core::vector3df(90,0,110));
    if(enemigos[1])
        enemigos[1]->inicialiazar(1,1, smgr, core::vector3df(200,0,100));
    if(enemigos[2])
        enemigos[2]->inicialiazar(2,2,smgr,core::vector3df(40,0,200));
    if(enemigos[5])
        enemigos[5]->inicialiazar2(smgr);

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
    ///OBJETO
    Objeto *objeto= new Objeto;
    if(objeto){
        objeto->inicializar(smgr,driver);

    }
    ///RATON
    core::plane3df plane(prota->getCuboProta(), core::vector3df(0, -1, 0));
    core::vector3df mousePosition= core::vector3df(0,0,0);
    core::line3df ray(mousePosition, prota->getCuboProta());

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
	vec3df posicion(0,0,0);
	ISound* s1;
	ISound* s2;
	ISound* s3;
	ISound* s4;
	ISound* s5;


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

	///BOOLEANS Y DECLARACIONES RANDOM

	bool pasosP = false;
	bool pasos2P = false;
	bool escaneando = false;
	bool combatiendo = false;
	bool investigando = false;
	bool patrullando = true;
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
    bool hayobj= false;
    bool centinela= false;
    bool tocado= false;
    bool stop= true;

    //PERCEPCION SENSONRIAL

    b2RayCastInput input;
    input.maxFraction	=	1.0f;
    b2RayCastOutput	output;
    float angulo2 = 0;
    float distancia = 0;
    scene::IMesh *rayo = smgr->getGeometryCreator()->createCubeMesh(core::vector3df(10.f, 1.f, 1.f));
    scene::IMeshSceneNode *modelo = smgr->addMeshSceneNode(rayo);
    modelo->setVisible(false);

    int lastFPS = -1;
    u32 myClock;
    int frame = 0;
    Time tiempo;
    tiempo.set(device);
    float vidaProta;

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
        if(receiver.GetMouseState().LeftButtonDown && stop== true){
            centinela= true;
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
            core::vector3df toMousePosition(mousePosition - prota->getCuboProta());
            hayobj= objeto->comprobarPunto(b2Vec2(mousePosition.X, mousePosition.Z));

            if(hayobj && centinela == true){
               tocado= prota->cogerObjeto(toMousePosition, smgr);
            }
            else if(centinela == false){
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
                }
            }
        }

        //importante para cambiar posicion de body
        //prota->moverBody(mousePosition);
        prota->setPosition(vector3df(prota->getBody()->GetPosition().x, 0, prota->getBody()->GetPosition().y));
        if(tocado == true)
            objeto->setPosition(vector3df(5000, 0, 5000));
        else
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

        if(receiver.isKeyDown(KEY_LSHIFT))
           prota->velocidad = 4.5f;
        else
           prota->velocidad = 10.0f;


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
                enemigos[3]->inicialiazar(0,4,smgr,posicion);
                enemigos[4]->inicialiazar(0,5,smgr,posicion2);
                enemigos[3]->setEstado(8);
                enemigos[3]->setPunto(enemigos[1]->getPunto());
                enemigos[4]->setEstado(8);
                enemigos[4]->setPunto(enemigos[1]->getPunto());
                enemigos[1]->setEstado(10);
                    //eliminar enemigo
                enemigos[1]->setPosicion(core::vector3df(-1000,0,0), prota->getCuboProta());

            }
        }

        //SONIDOS ENEMIGOS
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
                if(engine->isCurrentlyPlaying(combate) || engine->isCurrentlyPlaying(patrullar) || engine->isCurrentlyPlaying(investigar) || engine->isCurrentlyPlaying(escaneo))
                s3->stop();
                s3 = engine->play3D(escaneomedico,posicion,false,false,true);
        }
        else if(enemigos[2]->getEstado() == 9 && combatiendo2==false) {
                escaneando2 = false;
                combatiendo2 = true;
                investigando2 = false;
                patrullando2 = false;
                huyendo = false;
                if(engine->isCurrentlyPlaying(combate) || engine->isCurrentlyPlaying(patrullar) || engine->isCurrentlyPlaying(investigar) || engine->isCurrentlyPlaying(escaneo))
                s3->stop();
                s3 = engine->play3D(defensa,posicion,false,false,true);
        }
         if(enemigos[2]->getEstado() == 8 && investigando2==false) {
                escaneando2 = false;
                combatiendo2 = false;
                investigando2 = true;
                patrullando2 = false;
                huyendo = false;
                if(engine->isCurrentlyPlaying(combate) || engine->isCurrentlyPlaying(patrullar) || engine->isCurrentlyPlaying(investigar) || engine->isCurrentlyPlaying(escaneo))
                s3->stop();
                s3 = engine->play3D(investigarmedico,posicion,false,false,true);
        }
         if(enemigos[2]->getEstado() == 0 && patrullando2==false) {
                escaneando2 = false;
                combatiendo2 = false;
                investigando2 = false;
                patrullando2 = true;
                huyendo = false;
                if(engine->isCurrentlyPlaying(combate) || engine->isCurrentlyPlaying(patrullar) || engine->isCurrentlyPlaying(investigar) || engine->isCurrentlyPlaying(escaneo))
                s3->stop();
                s3 = engine->play3D(patrullarmedico,posicion,false,false,true);
        }
         if(enemigos[2]->getEstado() == 3 && huyendo==false) {
                escaneando2 = false;
                combatiendo2 = false;
                investigando2 = false;
                patrullando2 = false;
                huyendo = true;
                if(engine->isCurrentlyPlaying(combate) || engine->isCurrentlyPlaying(patrullar) || engine->isCurrentlyPlaying(investigar) || engine->isCurrentlyPlaying(escaneo))
                s3->stop();
                s3 = engine->play3D(huir,posicion,false,false,true);
        }


        input.p1.Set(enemigos[5]->getBody()->GetPosition().x, enemigos[5]->getBody()->GetPosition().y);	//	Punto	inicial	del	rayo
        input.p2.Set(prota->getBody()->GetPosition().x, prota->getBody()->GetPosition().y);	//	Punto	final	del	rayo

        bool    hitmuro     =   muro1->body15->GetFixtureList()->RayCast(&output,	input,	0);
        bool    hitprota	=	prota->getBody()->GetFixtureList()->RayCast(&output,	input,	0);


        distancia = sqrt(pow(input.p2.x-input.p1.x, 2)+pow(input.p2.y-input.p1.y, 2));


            if(hitprota && distancia<90 && !hitmuro){

                   // b2Vec2 hitPoint = input.p1+output.fraction * (input.p2 - input.p1);
                   // b2Vec2 normal = output.normal;

                angulo2 = atan2f((input.p2.y-input.p1.y) , -(input.p2.x-input.p1.x)) * 180.f / irr::core::PI;
                enemigos[5]->getBody()->SetTransform(enemigos[5]->getBody()->GetPosition(), angulo2);
                enemigos[5]->getModelo()->setRotation(core::vector3df(0,enemigos[5]->getBody()->GetAngle(),0));




                modelo->setVisible(true);
                modelo->setScale(core::vector3df(distancia/10, 0.5f, 0.5f));
                modelo->setPosition(core::vector3df((input.p2.x+input.p1.x)/2,0,(input.p2.y+input.p1.y)/2));
                modelo->setRotation(core::vector3df(0,enemigos[5]->getBody()->GetAngle(),0));
                smgr->getMeshManipulator()->setVertexColors(enemigos[5]->getModelo()->getMesh(),irr::video::SColor(255, 0, 255, 0));

            }
            else{
                smgr->getMeshManipulator()->setVertexColors(enemigos[5]->getModelo()->getMesh(),irr::video::SColor(0, 0, 0, 0));
                modelo->setVisible(false);

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

        //Guardia
        enemigos[0]->update(prota->getCuboProta(), tiempo, enemigos);
        //Alarma
        enemigos[1]->update(prota->getCuboProta(), tiempo, enemigos);
        //Medico
        enemigos[2]->update(prota->getCuboProta(), tiempo, enemigos);
        if(aparcao){
        enemigos[3]->update(prota->getCuboProta(), tiempo, enemigos);
        enemigos[4]->update(prota->getCuboProta(), tiempo, enemigos);
        }
        enemigos[0]->setPosicion(enemigos[0]->getCuboEnemigo(), prota->getCuboProta());

        //Si el dron no se ha convertido en alarma
        if(cambiao == false)
            enemigos[1]->setPosicion(enemigos[1]->getCuboEnemigo(), prota->getCuboProta());
        if(aparcao){
            enemigos[3]->setPosicion(enemigos[3]->getCuboEnemigo(), prota->getCuboProta());
            enemigos[4]->setPosicion(enemigos[4]->getCuboEnemigo(), prota->getCuboProta());
        }
        enemigos[2]->setPosicion(enemigos[2]->getCuboEnemigo(), prota->getCuboProta());


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
