#include "Muros.h"
#include <Box2D/Box2D.h>

Muros::Muros()
{
    //ctor
}

Muros::~Muros()
{
    //dtor
}

void Muros::inicializar(scene::ISceneManager* smgr,video::IVideoDriver* driver){
    tam= 5;

    modelo = smgr->addCubeSceneNode(tam);
    modelo->setMaterialFlag(video::EMF_LIGHTING, false);
    modelo->setMaterialTexture( 0, driver->getTexture("texturas/metal.png") );
    modelo->setMaterialType( video::EMT_SOLID );
    modelo->setPosition(core::vector3df(0,0,20));

    cuboMuros = modelo->getPosition();

    b2BodyDef bodyDef;
    bodyDef.type= b2_dynamicBody;
    bodyDef.position.Set(0, 20);
    iworld= World::Instance();
    body2= iworld->getWorld()->CreateBody(&bodyDef);

    b2PolygonShape bodyShape;
    bodyShape.SetAsBox(tam/2, tam/2);
    body2->CreateFixture(&bodyShape, 1.0f);

    /*b2FixtureDef fixtureDef;
    fixtureDef.shape = &bodyShape;
    fixtureDef.friction = 10.5f;
    fixtureDef.restitution  = 0.9f;
    fixtureDef.density  = 10.f;
    body2->CreateFixture(&fixtureDef);*/
}

core::vector3df Muros::getCuboMuros(){
    return cuboMuros;
}

void Muros::setPosition(core::vector3df vec){
    modelo->setPosition(core::vector3df(vec.X, 0, vec.Z));
}

b2Body* Muros::getBody(){
    return body2;
}

void Muros::setCuboMuros(core::vector3df cb){
    cuboMuros = cb;
}

scene::IMeshSceneNode* Muros::getModelo(){
    return modelo;
}

