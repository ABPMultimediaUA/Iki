#include "Muros.h"
#include <Box2D/Box2D.h>
#include <iostream>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

Muros::Muros()
{

}

Muros::~Muros()
{
    //dtor
}

void Muros::inicializar(scene::ISceneManager* smgr,video::IVideoDriver* driver, vector3df pos){
    tam= 4;

    tipo1= smgr->getGeometryCreator()->createCubeMesh(core::vector3df(4.f, 4.f, 4.f));
    modelo = smgr->addMeshSceneNode(tipo1);
    smgr->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(0, 0, 0, 0));


/*
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
    */

    scene::IMesh *mura1 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 50.f));
    scene::IMeshSceneNode *muro1 = smgr->addMeshSceneNode(mura1);
    muro1->setPosition(core::vector3df(60,0,0));

    scene::IMesh *mura2 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 10.f));
    scene::IMeshSceneNode *muro2 = smgr->addMeshSceneNode(mura2);
    muro2->setPosition(core::vector3df(40,0,-20));


    scene::IMesh *mura3 = smgr->getGeometryCreator()->createCubeMesh(vector3df(80.f, 10.f, 10.f));
    scene::IMeshSceneNode *muro3 = smgr->addMeshSceneNode(mura3);
    muro3->setPosition(core::vector3df(25,0,30));


    scene::IMesh *mura4 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 25.f));
    scene::IMeshSceneNode *muro4 = smgr->addMeshSceneNode(mura4);
    muro4->setPosition(core::vector3df(25,0,-5));

    scene::IMesh *mura5 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 300.f));
    scene::IMeshSceneNode *muro5 = smgr->addMeshSceneNode(mura5);
    muro5->setPosition(core::vector3df(-40,0,0));



    scene::IMesh *mura6 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 10.f));
    scene::IMeshSceneNode *muro6 = smgr->addMeshSceneNode(mura6);
    muro6->setPosition(core::vector3df(10,0,5));


    scene::IMesh *mura7 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 100.f));
    scene::IMeshSceneNode *muro7 = smgr->addMeshSceneNode(mura7);
    muro7->setPosition(core::vector3df(-10,0,-40));


    scene::IMesh *mura8 = smgr->getGeometryCreator()->createCubeMesh(vector3df(30.f, 10.f, 10.f));
    scene::IMeshSceneNode *muro8 = smgr->addMeshSceneNode(mura8);
    muro8->setPosition(core::vector3df(-20,0,-90));


    scene::IMesh *mura9 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 40.f));
    scene::IMeshSceneNode *muro9 = smgr->addMeshSceneNode(mura9);
    muro9->setPosition(core::vector3df(50,0,140));


    scene::IMesh *mura10 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 60.f));
    scene::IMeshSceneNode *muro10 = smgr->addMeshSceneNode(mura10);
    muro10->setPosition(core::vector3df(80,0,60));


    scene::IMesh *mura11 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 40.f));
    scene::IMeshSceneNode *muro11 = smgr->addMeshSceneNode(mura11);
    muro11->setPosition(core::vector3df(10,0,80));


    scene::IMesh *mura12 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 40.f));
    scene::IMeshSceneNode *muro12 = smgr->addMeshSceneNode(mura12);
    muro12->setPosition(core::vector3df(70,0,160));


    scene::IMesh *mura13 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 40.f));
    scene::IMeshSceneNode *muro13 = smgr->addMeshSceneNode(mura13);
    muro13->setPosition(core::vector3df(90,0,180));


    scene::IMesh *mura14 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 40.f));
    scene::IMeshSceneNode *muro14 = smgr->addMeshSceneNode(mura14);
    muro14->setPosition(core::vector3df(110,0,200));


    scene::IMesh *mura15 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 40.f));
    scene::IMeshSceneNode *muro15 = smgr->addMeshSceneNode(mura15);
    muro15->setPosition(core::vector3df(130,0,220));


    scene::IMesh *mura16 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 250.f));
    scene::IMeshSceneNode *muro16 = smgr->addMeshSceneNode(mura16);
    muro16->setPosition(core::vector3df(40,0,230));
    muro16->setRotation(core::vector3df(0,45,0));

    scene::IMesh *mura17 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 70.f));
    scene::IMeshSceneNode *muro17 = smgr->addMeshSceneNode(mura17);
    muro17->setPosition(core::vector3df(150,0,300));
    muro17->setRotation(core::vector3df(0,-45,0));

    scene::IMesh *mura18 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 70.f));
    scene::IMeshSceneNode *muro18 = smgr->addMeshSceneNode(mura18);
    muro18->setPosition(core::vector3df(230,0,220));
    muro18->setRotation(core::vector3df(0,-45,0));

    scene::IMesh *mura19 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 150.f));
    scene::IMeshSceneNode *muro19 = smgr->addMeshSceneNode(mura19);
    muro19->setPosition(core::vector3df(255,0,125));

    scene::IMesh *mura20 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 150.f));
    scene::IMeshSceneNode *muro20 = smgr->addMeshSceneNode(mura20);
    muro20->setPosition(core::vector3df(300,0,125));

    scene::IMesh *mura21 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 80.f));
    scene::IMeshSceneNode *muro21 = smgr->addMeshSceneNode(mura21);
    muro21->setPosition(core::vector3df(160,0,70));

    scene::IMesh *mura22 = smgr->getGeometryCreator()->createCubeMesh(vector3df(60.f, 10.f, 10.f));
    scene::IMeshSceneNode *muro22 = smgr->addMeshSceneNode(mura22);
    muro22->setPosition(core::vector3df(120,0,40));

    scene::IMesh *mura23 = smgr->getGeometryCreator()->createCubeMesh(vector3df(15.f, 10.f, 10.f));
    scene::IMeshSceneNode *muro23 = smgr->addMeshSceneNode(mura23);
    muro23->setPosition(core::vector3df(135,0,100));

    scene::IMesh *mura24 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 100.f));
    scene::IMeshSceneNode *muro24 = smgr->addMeshSceneNode(mura24);
    muro24->setPosition(core::vector3df(210,0,20));
    muro24->setRotation(core::vector3df(0,-60,0));

    scene::IMesh *mura25 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 90.f));
    scene::IMeshSceneNode *muro25 = smgr->addMeshSceneNode(mura25);
    muro25->setPosition(core::vector3df(280,0,30));
    muro25->setRotation(core::vector3df(0,45,0));

    scene::IMesh *mura26 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 25.f));
    scene::IMeshSceneNode *muro26 = smgr->addMeshSceneNode(mura26);
    muro26->setPosition(core::vector3df(255,0,20));
    muro26->setRotation(core::vector3df(0,-60,0));

}

core::vector3df Muros::getCuboMuros(){
    return cuboMuros;
}

void Muros::setPosition(core::vector3df vec){
    modelo->setPosition(core::vector3df(vec.X, 0, vec.Z));
}

b2Body* Muros::getBody(){
    return body;
}

void Muros::setCuboMuros(core::vector3df cb){
    cuboMuros = cb;
}

scene::IMeshSceneNode* Muros::getModelo(){
    return modelo;
}

