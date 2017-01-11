#include "Objeto.h"
#include <Box2D/Box2D.h>
#include <iostream>


using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

Objeto::Objeto()
{
    //ctor
}

Objeto::~Objeto()
{
    //dtor
}


void Objeto::inicializar(scene::ISceneManager* smgr, IVideoDriver* driver, core::vector3df p){

    tam= 3;

    escalado= core::vector3df(1,0,1);

    esfera= smgr->addCubeSceneNode(3);
    esfera->setScale(escalado);
    esfera->setPosition(p);

    modelo = smgr->addCubeSceneNode(tam);
    modelo->setMaterialFlag(video::EMF_LIGHTING, false);
    modelo->setMaterialTexture( 0, driver->getTexture("texturas/obj.png") );
    modelo->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
    modelo->setPosition(p);

    b2BodyDef bodyDef;
    bodyDef.type= b2_dynamicBody;
    bodyDef.position.Set(p.X, p.Z);
    iworld= World::Instance();
    body= iworld->getWorld()->CreateBody(&bodyDef);

    b2PolygonShape bodyShape;
    bodyShape.SetAsBox(tam/2, tam/2);
    body->CreateFixture(&bodyShape, 1.0f);

    cuboProta = modelo->getPosition();

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &bodyShape;
    fixtureDef.friction = 0.5f;
    fixtureDef.restitution  = 0.9f;
    fixtureDef.density  = 1.f;
    body->CreateFixture(&fixtureDef);
}

core::vector3df Objeto::getPosicionObjeto(){
    return modelo->getPosition();
}


bool Objeto::comprobarPunto(b2Vec2 v){
    bool si= false;
    si= body->GetFixtureList()->TestPoint(v);
    return si;
}
/*
bool Objeto::comprobarPunto(b2Vec2 v){
    bool si= false;
    b2Fixture *f = body->GetFixtureList();
    while(f){
        if(f -> TestPoint(v)){
            std::cout<<"bingo \n";
            si= true;
            return si;
        }
        f = f->GetNext();
    }
    return si;
}
*/
void Objeto::setPosition(core::vector3df vec){
    body->SetTransform(b2Vec2(vec.X, vec.Z), 0);
    modelo->setPosition(vec);
    esfera->setPosition(core::vector3df(vec.X, vec.Y, vec.Z));
}

b2Body* Objeto::getBody(){
    return body;
}

void Objeto::destroyObj(){
    modelo->remove();
}

void Objeto::destroyObj2(){
    //modelo->remove();
}
