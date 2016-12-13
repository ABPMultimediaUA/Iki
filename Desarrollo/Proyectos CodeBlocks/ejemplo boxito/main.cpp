#include <iostream>
#include <irrlicht.h>
#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>

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
b2Vec2 gravity(0.0f, -10.0f);

//bool doSleep = true;  depende de la version de box2d

b2World world(gravity); //se pondria aqui doSleep
ISceneManager* smgr;
ICameraSceneNode* camera;

std::vector<cubo*> cubos;

class MyEventReceiver : public IEventReceiver{
     public:
     virtual bool OnEvent(const SEvent& event){
          if (event.EventType == irr::EET_MOUSE_INPUT_EVENT){
               switch(event.MouseInput.Event){
                    case EMIE_LMOUSE_LEFT_UP:
                         int tam = 16, x = (event.MouseInput.X - (SCREENWIDTH/2))/5, y = (-event.MouseInput.Y+(SCREENHEIGHT/2))/5;
                         cubo* cuboNuevo = new cubo(smgr, tam, vector3df(x, y ,0));

                         b2PolygonShape polyShape;
                         b2FixtureDef fixtureDef;
                         b2BodyDef bodyDef;

                         bodyDef.type = b2_dynamicBody;
                         bodyDef.position.Set(x, y);

                         cuboNuevo->body = world.CreateBody(&bodyDef);

                         polyShape.SetAsBox(tam/2, tam/2);

                         fixtureDef.shape = &polyShape;
                         fixtureDef.friction = 10.5f;
                         fixtureDef.restitution  = 0.9f;
                         fixtureDef.density  = 10.f;

                         cuboNuevo->body->CreateFixture(&fixtureDef);
                         cubos.push_back(cuboNuevo);
                    break;
               }
          }
    }
     MyEventReceiver(){}
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

     while(device->run()){
          driver->beginScene(true, true, SColor(255,100,101,140));

          DeltaTime = timer->getTime() - TimeStamp;
          TimeStamp = timer->getTime();

          world.Step(DeltaTime*timeStep, velocityIterations, positionIterations);
          world.ClearForces();

          for(int i=0; i < cubos.size(); i++){
               cubos[i]->cubeNode->setPosition(vector3df(cubos[i]->body->GetPosition().x,cubos[i]->body->GetPosition().y,0));
               cubos[i]->cubeNode->setRotation(vector3df(0,0,cubos[i]->body->GetAngle()* 180 / 3.14159265));
          }

          smgr->drawAll();
          guienv->drawAll();
          driver->endScene();
       }
       device->drop();
       return 0;
    }
