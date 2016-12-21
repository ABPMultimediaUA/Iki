#include <irrlicht.h>
#include <Box2D/Box2D.h>
#include "include/Enemigo.h"
#include "include/Player.h"
#include "include/World.h"
#include <iostream>

#define SCREENWIDTH 1280
#define SCREENHEIGHT 720


using namespace irr;    //Espacio de nombres principal
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

    ///BOX2D
    //class World* world; no se por que puse class
    World* world;
    world = World::Instance();


    //Objeto principal que nos permite interactuar con el motor
    IrrlichtDevice *device= createDevice(video::EDT_SOFTWARE, dimension2d<u32>(SCREENWIDTH, SCREENHEIGHT), 16, false, false, false, &receiver);

    ITimer* timer = device->getTimer();
    f32 TimeStamp = timer->getTime();
    f32 DeltaTime = timer->getTime() - TimeStamp;




    if(!device){
        //std::cout << "no existe\n";
        return 1;
    }

    ISceneManager* smgr= device->getSceneManager();         //Gestion de la escena
    IVideoDriver* driver= device->getVideoDriver();         //Ciclo del juego
    IGUIEnvironment* guienv= device->getGUIEnvironment();   //Interfaz de usuario
    //std::cout << "1\n";

    ///PLAYER
    Enemigo *enemi= new Enemigo;
    if(enemi){
        enemi->inicializar(smgr,driver);

    }
    Enemigo *enemi2= new Enemigo;
    if(enemi2){
        enemi2->inicializar2(smgr,driver);

    }

    Player *prota= new Player;
    if(prota){
        prota->inicializar(smgr,driver);

    }
    ///raton
    core::plane3df plane(prota->getCuboProta(), core::vector3df(0, -1, 0));
    core::vector3df mousePosition= core::vector3df(0,0,0);
    core::line3df ray(mousePosition, prota->getCuboProta());


    scene::ICameraSceneNode * camera = smgr->addCameraSceneNode(0,core::vector3df(0,90,-40),core::vector3df(0,0,0));

//PERCEPCION SENSONRIAL

    b2RayCastInput input;
    input.maxFraction	=	1.0f;
    b2RayCastOutput	output;
    float angulo2 = 0;
    float distancia = 0;
     scene::IMesh *rayo = smgr->getGeometryCreator()->createCubeMesh(core::vector3df(10.f, 1.f, 1.f));
     scene::IMeshSceneNode *modelo = smgr->addMeshSceneNode(rayo);
     smgr->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(0, 0, 0, 0));
     modelo->setVisible(false);




    //Ciclo del juego
    while(device->run()){

       driver->beginScene(true, true, SColor(255, 100, 101, 140));

        ///raton
        if(receiver.GetMouseState().RightButtonDown)
        {
            ray = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(
                      receiver.GetMouseState().Position, camera);

        float angulo = atan2f((mousePosition.Z-prota->getModelo()->getPosition().Z) , -(mousePosition.X-prota->getModelo()->getPosition().X)) * 180.f / irr::core::PI;
        prota->getBody()->SetTransform(prota->getBody()->GetPosition(), angulo);
        prota->getModelo()->setRotation(core::vector3df(0,prota->getBody()->GetAngle(),0));


        }
        if(plane.getIntersectionWithLine(ray.start, ray.getVector(), mousePosition))
        {
            // We now have a mouse position in 3d space; move towards it.
            core::vector3df toMousePosition(mousePosition - prota->getCuboProta());
            if(toMousePosition.getLength() <= 1)
                prota->moverBody(vector3df(0,0,0));
            else
                prota->moverBody(toMousePosition);
        }

        //importante para cambiar posicion de body
//prota->moverBody(mousePosition);
        prota->setPosition(vector3df(prota->getBody()->GetPosition().x, 0, prota->getBody()->GetPosition().y));
        enemi2->setPosition(vector3df(enemi2->getBody()->GetPosition().x, 0, enemi2->getBody()->GetPosition().y));

////PERCEPCION SENSONRIAL

        input.p1.Set(enemi2->getBody()->GetPosition().x, enemi2->getBody()->GetPosition().y);	//	Punto	inicial	del	rayo
        input.p2.Set(prota->getBody()->GetPosition().x, prota->getBody()->GetPosition().y);	//	Punto	final	del	rayo

        bool    hitmuro     =   enemi->getBody()->GetFixtureList()->RayCast(&output,	input,	0);
        bool	hitprota	=	prota->getBody()->GetFixtureList()->RayCast(&output,	input,	0);
            if(hitprota && !hitmuro){

               // b2Vec2 hitPoint = input.p1+output.fraction * (input.p2 - input.p1);
               // b2Vec2 normal = output.normal;



                smgr->getMeshManipulator()->setVertexColors(enemi2->getModelo()->getMesh(),irr::video::SColor(255, 255, 0, 0));
                angulo2 = atan2f((input.p2.y-input.p1.y) , -(input.p2.x-input.p1.x)) * 180.f / irr::core::PI;
                enemi2->getBody()->SetTransform(enemi2->getBody()->GetPosition(), angulo2);
                enemi2->getModelo()->setRotation(core::vector3df(0,enemi2->getBody()->GetAngle(),0));

                distancia = sqrt(pow(input.p2.x-input.p1.x, 2)+pow(input.p2.y-input.p1.y, 2));



                modelo->setVisible(true);
                modelo->setScale(core::vector3df(distancia/10, 0.5f, 0.5f));
                modelo->setPosition(core::vector3df((input.p2.x+input.p1.x)/2,0,(input.p2.y+input.p1.y)/2));
                modelo->setRotation(core::vector3df(0,enemi2->getBody()->GetAngle(),0));



            }
            else{
                smgr->getMeshManipulator()->setVertexColors(enemi2->getModelo()->getMesh(),irr::video::SColor(0, 0, 0, 0));
                modelo->setVisible(false);
            }

                /*if	( b2RayCastCallback.ReportFixture(prota->getBody()->GetFixtureList(), hitPoint, normal, 1.0f) == 0 )	{
                }*/




        DeltaTime = timer->getTime() - TimeStamp;
        TimeStamp = timer->getTime();

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

    return 0;
}
