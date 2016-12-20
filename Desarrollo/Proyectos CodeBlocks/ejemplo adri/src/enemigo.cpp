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
    tam= 4;
    mura1 = smgr->getGeometryCreator()->createCubeMesh(core::vector3df(1.f, 3.f, 1.f));
    modelo = smgr->addMeshSceneNode(mura1);
    smgr->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(0, 0, 0, 0));
    //modelo->setMaterialFlag(video::EMF_LIGHTING, false);
    //modelo->setMaterialTexture( 0, driver->getTexture("texturas/metal.png") );
    //modelo->setMaterialType( video::EMT_SOLID );
    modelo->setPosition(core::vector3df(0,0,20));

    cuboEnemigo = modelo->getPosition();

    b2BodyDef bodyDef;
    bodyDef.type= b2_staticBody;
    bodyDef.position.Set(0, 20);
    iworld= World::Instance();
    body2= iworld->getWorld()->CreateBody(&bodyDef);

    b2PolygonShape bodyShape;
    bodyShape.SetAsBox((50/2)+0.5, (10/2)+0.5);
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

void Enemigo::setPosition(core::vector3df vec){
    modelo->setPosition(core::vector3df(vec.X, 0, vec.Z));
}

b2Body* Enemigo::getBody(){
    return body2;
}

void Enemigo::setCuboEnemigo(core::vector3df cb){
    cuboEnemigo = cb;
}

scene::IMeshSceneNode* Enemigo::getModelo(){
    return modelo;
}
