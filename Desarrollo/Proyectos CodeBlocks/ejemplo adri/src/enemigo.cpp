#include "Enemigo.h"
#include <Box2D/Box2D.h>



Enemigo::Enemigo()
{
    //ctor
}

Enemigo::~Enemigo()
{
    //dtor
}

void Enemigo::inicializar(scene::ISceneManager* smgr,video::IVideoDriver* driver){
    tam= 10;

    modelo = smgr->addCubeSceneNode(tam);
    modelo->setMaterialFlag(video::EMF_LIGHTING, false);
    modelo->setMaterialTexture( 0, driver->getTexture("texturas/metal.png") );
    modelo->setMaterialType( video::EMT_SOLID );
    modelo->setPosition(core::vector3df(40,0,0));

    cuboEnemigo = modelo->getPosition();

    b2BodyDef bodyDef;
    bodyDef.type= b2_dynamicBody;
    bodyDef.position.Set(40, 0);
    iworld= World::Instance();
    body2= iworld->getWorld()->CreateBody(&bodyDef);

    b2PolygonShape bodyShape;
    bodyShape.SetAsBox(tam/2, tam/2);
    body2->CreateFixture(&bodyShape, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &bodyShape;
    fixtureDef.friction = 10.5f;
    fixtureDef.restitution  = 0.9f;
    fixtureDef.density  = 10.f;
    body2->CreateFixture(&fixtureDef);
}

core::vector3df Enemigo::getCuboEnemigo(){
    return cuboEnemigo;
}

void Enemigo::setCuboEnemigo(core::vector3df cb){
    cuboEnemigo = cb;
}

scene::IMeshSceneNode* Enemigo::getModelo(){
    return modelo;
}
