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



void Muros::inicializar(scene::ISceneManager* smgr,IVideoDriver* driver){

b2BodyDef bodyDef;
bodyDef.type= b2_staticBody;
iworld= World::Instance();
b2PolygonShape bodyShape;

///1
    mura1 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 50.f));
    muro1 = smgr->addMeshSceneNode(mura1);
    smgr->getMeshManipulator()->setVertexColors(muro1->getMesh(),SColor(0, 0, 0, 0));
    muro1->setPosition(vector3df(60,0, 0));

    bodyDef.position.Set(60, 0);
    body= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(10.f/2, 40.f/2);
    body->CreateFixture(&bodyShape, 1.0f);

///2
    mura2 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 10.f));
    muro2 = smgr->addMeshSceneNode(mura2);
    smgr->getMeshManipulator()->setVertexColors(muro2->getMesh(), SColor(0, 0, 0, 0));
    muro2->setPosition(vector3df(40,0,-20));

    bodyDef.position.Set(40, -20);
    body2= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(40/2, 10/2);
    body2->CreateFixture(&bodyShape, 1.0f);

///3
    mura3 = smgr->getGeometryCreator()->createCubeMesh(vector3df(80.f, 10.f, 10.f));
    muro3 = smgr->addMeshSceneNode(mura3);
    smgr->getMeshManipulator()->setVertexColors(muro3->getMesh(),SColor(0, 0, 0, 0));
    muro3->setPosition(vector3df(25,0,30));

    bodyDef.position.Set(25, 30);
    body3= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(80/2, 10/2);
    body3->CreateFixture(&bodyShape, 1.0f);

///4
    mura4 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 25.f));
    muro4 = smgr->addMeshSceneNode(mura4);
    smgr->getMeshManipulator()->setVertexColors(muro4->getMesh(),SColor(0, 0, 0, 0));
    muro4->setPosition(vector3df(25,0,-5));

    bodyDef.position.Set(25, -5);
    body4= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(10/2, 25.f/2);
    body4->CreateFixture(&bodyShape, 1.0f);

///5
    mura5 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 300.f));
    muro5 = smgr->addMeshSceneNode(mura5);
    smgr->getMeshManipulator()->setVertexColors(muro5->getMesh(),SColor(0, 0, 0, 0));
    muro5->setPosition(vector3df(-40,0,0));

    bodyDef.position.Set(-40, 0);
    body5= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(10/2, 300/2);
    body5->CreateFixture(&bodyShape, 1.0f);

///6
    mura6 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 10.f));
    muro6 = smgr->addMeshSceneNode(mura6);
    smgr->getMeshManipulator()->setVertexColors(muro6->getMesh(),SColor(0, 0, 0, 0));
    muro6->setPosition(vector3df(10,0,5));

    bodyDef.position.Set(10, 5);
    body6= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(40/2, 10/2);
    body6->CreateFixture(&bodyShape, 1.0f);

///7
    mura7 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 100.f));
    muro7 = smgr->addMeshSceneNode(mura7);
    smgr->getMeshManipulator()->setVertexColors(muro7->getMesh(),SColor(0, 0, 0, 0));
    muro7->setPosition(vector3df(-10,0,-40));

    bodyDef.position.Set(-10, -40);
    body7= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(10/2, 100/2);
    body7->CreateFixture(&bodyShape, 1.0f);

///8
    mura8 = smgr->getGeometryCreator()->createCubeMesh(vector3df(30.f, 10.f, 10.f));
    muro8 = smgr->addMeshSceneNode(mura8);
    smgr->getMeshManipulator()->setVertexColors(muro8->getMesh(),SColor(0, 0, 0, 0));
    muro8->setPosition(vector3df(-20,0,-90));

    bodyDef.position.Set(-20, -90);
    body8= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(30/2, 10/2);
    body8->CreateFixture(&bodyShape, 1.0f);

///9
    mura9 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 40.f));
    muro9 = smgr->addMeshSceneNode(mura9);
    smgr->getMeshManipulator()->setVertexColors(muro9->getMesh(),SColor(0, 0, 0, 0));
    muro9->setPosition(vector3df(50,0,140));

    bodyDef.position.Set(50, 140);
    body9= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(40/2, 40/2);
    body9->CreateFixture(&bodyShape, 1.0f);

///10
    mura10 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 60.f));
    muro10 = smgr->addMeshSceneNode(mura10);
    smgr->getMeshManipulator()->setVertexColors(muro10->getMesh(),SColor(0, 0, 0, 0));
    muro10->setPosition(vector3df(80,0,60));

    bodyDef.position.Set(80, 60);
    body10= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(40/2, 60/2);
    body10->CreateFixture(&bodyShape, 1.0f);

///11
    mura11 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 40.f));
    muro11 = smgr->addMeshSceneNode(mura11);
    smgr->getMeshManipulator()->setVertexColors(muro11->getMesh(),SColor(0, 0, 0, 0));
    muro11->setPosition(vector3df(10,0,80));

    bodyDef.position.Set(10, 80);
    body11= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(40/2, 40/2);
    body11->CreateFixture(&bodyShape, 1.0f);

///12
    mura12 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 40.f));
    muro12 = smgr->addMeshSceneNode(mura12);
    smgr->getMeshManipulator()->setVertexColors(muro12->getMesh(),SColor(0, 0, 0, 0));
    muro12->setPosition(vector3df(70,0,160));

    bodyDef.position.Set(70, 160);
    body12= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(40/2, 40/2);
    body12->CreateFixture(&bodyShape, 1.0f);

///13
    mura13 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 40.f));
    muro13 = smgr->addMeshSceneNode(mura13);
    smgr->getMeshManipulator()->setVertexColors(muro13->getMesh(),SColor(0, 0, 0, 0));
    muro13->setPosition(vector3df(90,0,180));

    bodyDef.position.Set(90, 180);
    body13= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(40/2, 40/2);
    body13->CreateFixture(&bodyShape, 1.0f);

///14
    mura14 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 40.f));
    muro14 = smgr->addMeshSceneNode(mura14);
    smgr->getMeshManipulator()->setVertexColors(muro14->getMesh(),SColor(0, 0, 0, 0));
    muro14->setPosition(vector3df(110,0,200));

    bodyDef.position.Set(110, 200);
    body14= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(40/2, 40/2);
    body14->CreateFixture(&bodyShape, 1.0f);

///15
    mura15 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 40.f));
    muro15 = smgr->addMeshSceneNode(mura15);
    smgr->getMeshManipulator()->setVertexColors(muro15->getMesh(),SColor(0, 0, 0, 0));
    muro15->setPosition(vector3df(130,0,220));

    bodyDef.position.Set(130, 220);
    body15= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(40/2, 40/2);
    body15->CreateFixture(&bodyShape, 1.0f);

///16
    mura16 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 250.f));
    muro16 = smgr->addMeshSceneNode(mura16);
    smgr->getMeshManipulator()->setVertexColors(muro16->getMesh(),SColor(0, 0, 0, 0));
    muro16->setPosition(vector3df(40,0,230));
    muro16->setRotation(vector3df(0, 45, 0));

    bodyDef.position.Set(40, 230);
    body16= iworld->getWorld()->CreateBody(&bodyDef);
    body16->SetTransform(b2Vec2(40, 230), 180 / 3.14159265 * 45);
    bodyShape.SetAsBox(10/2, 250/2);
    body16->CreateFixture(&bodyShape, 1.0f);

///17
    mura17 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 70.f));
    muro17 = smgr->addMeshSceneNode(mura17);
    smgr->getMeshManipulator()->setVertexColors(muro17->getMesh(),SColor(0, 0, 0, 0));
    muro17->setPosition(vector3df(150,0,300));
    muro17->setRotation(vector3df(0, -45, 0));

    bodyDef.position.Set(150, 300);
    body17= iworld->getWorld()->CreateBody(&bodyDef);
    body17->SetTransform(b2Vec2(150, 300),  180 / 3.14159265 * (-45));
    bodyShape.SetAsBox(10/2, 70/2);
    body17->CreateFixture(&bodyShape, 1.0f);

///18
    mura18 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 70.f));
    muro18 = smgr->addMeshSceneNode(mura18);
    smgr->getMeshManipulator()->setVertexColors(muro18->getMesh(),SColor(0, 0, 0, 0));
    muro18->setPosition(vector3df(230,0,220));
    muro18->setRotation(vector3df(0, -45, 0));

    bodyDef.position.Set(230, 220);
    body18= iworld->getWorld()->CreateBody(&bodyDef);
    body18->SetTransform(b2Vec2(230, 220),  180 / 3.14159265 * (-45));
    bodyShape.SetAsBox(10/2, 70/2);
    body18->CreateFixture(&bodyShape, 1.0f);

///19
    mura19 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 150.f));
    muro19 = smgr->addMeshSceneNode(mura19);
    smgr->getMeshManipulator()->setVertexColors(muro19->getMesh(),SColor(0, 0, 0, 0));
    muro19->setPosition(vector3df(255,0,125));

    bodyDef.position.Set(255, 125);
    body19= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(10/2, 150/2);
    body19->CreateFixture(&bodyShape, 1.0f);smgr->getMeshManipulator()->setVertexColors(muro1->getMesh(),SColor(0, 0, 0, 0));

///20
    mura20 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 150.f));
    muro20 = smgr->addMeshSceneNode(mura20);
    smgr->getMeshManipulator()->setVertexColors(muro20->getMesh(),SColor(0, 0, 0, 0));
    muro20->setPosition(vector3df(300,0,125));

    bodyDef.position.Set(300, 125);
    body20= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(10/2, 150/2);
    body20->CreateFixture(&bodyShape, 1.0f);

///21
    mura21 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 80.f));
    muro21 = smgr->addMeshSceneNode(mura21);
    smgr->getMeshManipulator()->setVertexColors(muro21->getMesh(),SColor(0, 0, 0, 0));
    muro21->setPosition(vector3df(160,0,70));

    bodyDef.position.Set(160, 70);
    body21= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(40/2, 80/2);
    body21->CreateFixture(&bodyShape, 1.0f);

///22
    mura22 = smgr->getGeometryCreator()->createCubeMesh(vector3df(60.f, 10.f, 10.f));
    muro22 = smgr->addMeshSceneNode(mura22);
    smgr->getMeshManipulator()->setVertexColors(muro22->getMesh(),SColor(0, 0, 0, 0));
    muro22->setPosition(vector3df(120,0,40));

    bodyDef.position.Set(120, 40);
    body22= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(60/2, 10/2);
    body22->CreateFixture(&bodyShape, 1.0f);

///23
    mura23 = smgr->getGeometryCreator()->createCubeMesh(vector3df(15.f, 10.f, 10.f));
    muro23 = smgr->addMeshSceneNode(mura23);
    smgr->getMeshManipulator()->setVertexColors(muro23->getMesh(),SColor(0, 0, 0, 0));
    muro23->setPosition(vector3df(135,0,100));

    bodyDef.position.Set(135, 100);
    body23= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(15.f/2, 10/2);
    body23->CreateFixture(&bodyShape, 1.0f);

///24
    mura24 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 100.f));
    muro24 = smgr->addMeshSceneNode(mura24);
    smgr->getMeshManipulator()->setVertexColors(muro24->getMesh(),SColor(0, 0, 0, 0));
    muro24->setPosition(vector3df(210,0,20));
    muro24->setRotation(vector3df(0, -60, 0));

    bodyDef.position.Set(210, 20);
    body24= iworld->getWorld()->CreateBody(&bodyDef);
    body24->SetTransform(b2Vec2(210, 20),   180 / 3.14159265 * (300));
    bodyShape.SetAsBox(10/2, 100/2);
    body24->CreateFixture(&bodyShape, 1.0f);

///25
    mura25 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 90.f));
    muro25 = smgr->addMeshSceneNode(mura25);
    smgr->getMeshManipulator()->setVertexColors(muro25->getMesh(),SColor(0, 0, 0, 0));
    muro25->setPosition(vector3df(280,0,30));
    muro25->setRotation(vector3df(0, 45, 0));

    bodyDef.position.Set(280, 30);
    body25= iworld->getWorld()->CreateBody(&bodyDef);
    body25->SetTransform(b2Vec2(280, 30),   180 / 3.14159265 * (45));
    bodyShape.SetAsBox(10/2, 90/2);
    body25->CreateFixture(&bodyShape, 1.0f);

///26
    mura26 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 25.f));
    muro26 = smgr->addMeshSceneNode(mura26);
    smgr->getMeshManipulator()->setVertexColors(muro26->getMesh(),SColor(0, 0, 0, 0));
    muro26->setPosition(vector3df(255,0,20));
    muro26->setRotation(vector3df(0, -60, 0));

    bodyDef.position.Set(255, 20);
    body26= iworld->getWorld()->CreateBody(&bodyDef);
    body26->SetTransform(b2Vec2(255, 20),   180 / 3.14159265 * (300));
    bodyShape.SetAsBox(10/2, 25.f/2);
    body26->CreateFixture(&bodyShape, 1.0f);

}
