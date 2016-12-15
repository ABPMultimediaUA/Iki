#include <iostream>
#include <irrlicht.h>
#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>
#include <vector>


#define SCREENWIDTH 1280
#define SCREENHEIGHT 720

//si los inicializamos aqui luego no tendremos que ponerlos.

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

//creamos un cubo
struct cubo{
    cubo(ISceneManager* smgr, int tam, vector3df pos){
        cubeNode = smgr->addCubeSceneNode(tam);
        cubeNode->setPosition(pos);
        smgr->getMeshManipulator()->setVertexColors(cubeNode->getMesh(), SColor(255, rand()%255, rand()%255, rand()%255));
    }
    IMeshSceneNode* cubeNode;
    b2Body *body;
};



IrrlichtDevice *device = 0;
b2Vec2 gravity(0.0f, 0.0f);



//bool doSleep = true;  depende de la version de box2d

b2World world(gravity); //se pondria aqui doSleep
ISceneManager* smgr;
ICameraSceneNode* camera;


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

     device = createDevice( video::EDT_OPENGL, dimension2d<u32>(SCREENWIDTH,SCREENHEIGHT), 16, false, false, false, &receiver);
     device->setWindowCaption(L"Irrlicht/Box2D Sample");

     IVideoDriver* driver = device->getVideoDriver();

     smgr = device->getSceneManager();
     IGUIEnvironment* guienv = device->getGUIEnvironment();
     ITimer* timer = device->getTimer();
     guienv->addStaticText(L"Box2D integrated with Irrlicht", rect<s32>(10,10,130,22), true);
     camera = smgr->addCameraSceneNode(0, vector3df(0,0,-140), vector3df(0,0,0));
     smgr->addLightSceneNode(0, vector3df(0, 100, -100), video::SColorf(1, 1, 1), 40.f);

     b2BodyDef groundBodyDef;
     groundBodyDef.position.Set(0.0f, -80.0f);

     b2Body* groundBody = world.CreateBody(&groundBodyDef);
     b2PolygonShape groundBox;
     groundBox.SetAsBox(1290.0f, 0.1f);
     groundBody->CreateFixture(&groundBox, 0.0f);

     groundBodyDef.position.Set(0.0f, 100.0f);
     groundBody = world.CreateBody(&groundBodyDef);
     groundBox.SetAsBox(1290.0f, 0.1f);
     groundBody->CreateFixture(&groundBox, 0.0f);


     groundBodyDef.position.Set(-160.0f, -100.0f);
     groundBody = world.CreateBody(&groundBodyDef);
     groundBox.SetAsBox(0.1f, 1290.0f);
     groundBody->CreateFixture(&groundBox, 0.0f);

     groundBodyDef.position.Set(160.0f, -100.0f);
     groundBody = world.CreateBody(&groundBodyDef);
     groundBox.SetAsBox(0.1f, 1290.0f);
     groundBody->CreateFixture(&groundBox, 0.0f);


     float32 timeStep = 1.0f / 250.0f;
     int32 velocityIterations = 6;
     int32 positionIterations = 6;
     f32 TimeStamp = timer->getTime();
     f32 DeltaTime = timer->getTime() - TimeStamp;

     cubo* cuboNuevo = new cubo(smgr, 16, vector3df(0, 0 ,0));

                         b2PolygonShape polyShape;
                         b2FixtureDef fixtureDef;
                         b2BodyDef bodyDef;

                         bodyDef.type = b2_kinematicBody;
                         bodyDef.position.Set(0, 0);

                         cuboNuevo->body = world.CreateBody(&bodyDef);

                         polyShape.SetAsBox(16/2, 16/2);

                         fixtureDef.shape = &polyShape;
                         fixtureDef.friction = 10.5f;
                         fixtureDef.restitution  = 0.4f;
                         fixtureDef.density  = 10.f;

                         cuboNuevo->body->CreateFixture(&fixtureDef);

     cubo* cuboNuevo2 = new cubo(smgr, 16, vector3df(0, 0 ,0));

                         b2BodyDef bodyDef2;

                         bodyDef2.type = b2_staticBody;
                         bodyDef2.position.Set(50, -50);

                         cuboNuevo2->body = world.CreateBody(&bodyDef2);
                         cuboNuevo2->body->CreateFixture(&fixtureDef);

                         core::plane3df plane(cuboNuevo->cubeNode->getPosition(), core::vector3df(0, -1, 0));
                         core::vector3df mousePosition = core::vector3df(40,0,0);
                         core::line3df ray(mousePosition, cuboNuevo->cubeNode->getPosition());

     while(device->run()){
          driver->beginScene(true, true, SColor(255,100,101,140));

          DeltaTime = timer->getTime() - TimeStamp;
          TimeStamp = timer->getTime();

          world.Step(DeltaTime*timeStep, velocityIterations, positionIterations);
          world.ClearForces();


          if(receiver.GetMouseState().RightButtonDown)
        {
           cuboNuevo->body->SetLinearVelocity(b2Vec2(4 , -4));
           //->setVelocity(b2Vec2(0 , 90), b2Vec2(0.0, 0.0) , true);

        }




         cuboNuevo->cubeNode->setPosition(vector3df(cuboNuevo->body->GetPosition().x,cuboNuevo->body->GetPosition().y,0));
         cuboNuevo->cubeNode->setRotation(vector3df(0,0,cuboNuevo->body->GetAngle()* 180 / 3.14159265));

         cuboNuevo2->cubeNode->setPosition(vector3df(cuboNuevo2->body->GetPosition().x,cuboNuevo2->body->GetPosition().y,0));
         cuboNuevo2->cubeNode->setRotation(vector3df(0,0,cuboNuevo2->body->GetAngle()* 180 / 3.14159265));



          smgr->drawAll();
          guienv->drawAll();
          driver->endScene();
       }
       device->drop();
       return 0;
    }

