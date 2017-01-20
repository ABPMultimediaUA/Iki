#include "Map.h"







MapComponent::MapComponent(core::vector3df a, core::vector3df b, scene::ISceneManager* smgr){

    b2BodyDef bodyDef;
    bodyDef.type= b2_staticBody;
    iworld= World::Instance();
    b2PolygonShape bodyShape;

    bodyDef.position.Set(b.X, b.Z);
    body= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(1.f/2, 1.f/2);
    body->CreateFixture(&bodyShape, 1.0f);


mesh = smgr->getMesh("cubito.obj");
//smgr->getParameters()->setAttribute(irr::scene::COLLADA_CREATE_SCENE_INSTANCES, true);
modelo = smgr->addAnimatedMeshSceneNode(mesh);
modelo->setPosition(b);
//modelo->setScale(a);


}
