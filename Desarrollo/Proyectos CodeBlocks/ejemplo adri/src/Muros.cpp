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



void Muros::inicializar(scene::ISceneManager* smgr,video::IVideoDriver* driver){



///1
    mura1 = smgr->getGeometryCreator()->createCubeMesh(core::vector3df(10.f, 10.f, 50.f));
    muro1 = smgr->addMeshSceneNode(mura1);
    smgr->getMeshManipulator()->setVertexColors(muro1->getMesh(),video::SColor(0, 0, 0, 0));
    muro1->setPosition(core::vector3df(0,0,20));


    b2BodyDef bodyDef;
    bodyDef.type= b2_staticBody;
    bodyDef.position.Set(0, 20);
    iworld= World::Instance();
    body= iworld->getWorld()->CreateBody(&bodyDef);

    b2PolygonShape bodyShape;
    bodyShape.SetAsBox(10/2, 50/2);
    body->CreateFixture(&bodyShape, 1.0f);


///2

    mura2 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 10.f));
    muro2 = smgr->addMeshSceneNode(mura2);
    smgr->getMeshManipulator()->setVertexColors(muro2->getMesh(),video::SColor(0, 0, 0, 0));
    muro2->setPosition(core::vector3df(40,0,-20));

    bodyDef.position.Set(40, -20);
    body2= iworld->getWorld()->CreateBody(&bodyDef);

    bodyShape.SetAsBox(40/2, 10/2);
    body2->CreateFixture(&bodyShape, 1.0f);
/*
///3
    scene::IMesh *mura3 = smgr->getGeometryCreator()->createCubeMesh(vector3df(80.f, 10.f, 10.f));
    scene::IMeshSceneNode *muro3 = smgr->addMeshSceneNode(mura3);
    smgr->getMeshManipulator()->setVertexColors(muro3->getMesh(),video::SColor(0, 0, 0, 0));
    muro3->setPosition(core::vector3df(25,0,30));

    b2BodyDef bodyDef3;
    bodyDef3.type= b2_staticBody;
    bodyDef3.position.Set(25, 30);
    body3= iworld->getWorld()->CreateBody(&bodyDef3);

    b2PolygonShape bodyShape3;
    bodyShape3.SetAsBox(80/2, 10/2);
    body3->CreateFixture(&bodyShape3, 1.0f);

///4
    scene::IMesh *mura4 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 25.f));
    scene::IMeshSceneNode *muro4 = smgr->addMeshSceneNode(mura4);
    smgr->getMeshManipulator()->setVertexColors(muro4->getMesh(),video::SColor(0, 0, 0, 0));
    muro4->setPosition(core::vector3df(25,0,-5));

    bodyDef.position.Set(25, -5);
    body4= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(10/2, 25.f/2);
    body4->CreateFixture(&bodyShape, 1.0f);

///5
    scene::IMesh *mura5 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 300.f));
    scene::IMeshSceneNode *muro5 = smgr->addMeshSceneNode(mura5);
    smgr->getMeshManipulator()->setVertexColors(muro5->getMesh(),video::SColor(0, 0, 0, 0));
    muro5->setPosition(core::vector3df(-40,0,0));

    bodyDef.position.Set(-40, 0);
    body5= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(10/2, 300/2);
    body5->CreateFixture(&bodyShape, 1.0f);

///6
    scene::IMesh *mura6 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 10.f));
    scene::IMeshSceneNode *muro6 = smgr->addMeshSceneNode(mura6);
    smgr->getMeshManipulator()->setVertexColors(muro6->getMesh(),video::SColor(0, 0, 0, 0));
    muro6->setPosition(core::vector3df(10,0,5));

    bodyDef.position.Set(10, 5);
    body6= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(40/2, 10/2);
    body6->CreateFixture(&bodyShape, 1.0f);

///7
    scene::IMesh *mura7 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 100.f));
    scene::IMeshSceneNode *muro7 = smgr->addMeshSceneNode(mura7);
    smgr->getMeshManipulator()->setVertexColors(muro7->getMesh(),video::SColor(0, 0, 0, 0));
    muro7->setPosition(core::vector3df(-10,0,-40));

    bodyDef.position.Set(-10, -40);
    body7= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(10/2, 100/2);
    body7->CreateFixture(&bodyShape, 1.0f);

///8
    scene::IMesh *mura8 = smgr->getGeometryCreator()->createCubeMesh(vector3df(30.f, 10.f, 10.f));
    scene::IMeshSceneNode *muro8 = smgr->addMeshSceneNode(mura8);
    smgr->getMeshManipulator()->setVertexColors(muro8->getMesh(),video::SColor(0, 0, 0, 0));
    muro8->setPosition(core::vector3df(-20,0,-90));

    bodyDef.position.Set(-20, -90);
    body8= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(30/2, 10/2);
    body8->CreateFixture(&bodyShape, 1.0f);

///9
    scene::IMesh *mura9 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 40.f));
    scene::IMeshSceneNode *muro9 = smgr->addMeshSceneNode(mura9);
    smgr->getMeshManipulator()->setVertexColors(muro9->getMesh(),video::SColor(0, 0, 0, 0));
    muro9->setPosition(core::vector3df(50,0,140));

    bodyDef.position.Set(50, 140);
    body9= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(40/2, 40/2);
    body9->CreateFixture(&bodyShape, 1.0f);

///10
    scene::IMesh *mura10 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 60.f));
    scene::IMeshSceneNode *muro10 = smgr->addMeshSceneNode(mura10);
    smgr->getMeshManipulator()->setVertexColors(muro10->getMesh(),video::SColor(0, 0, 0, 0));
    muro10->setPosition(core::vector3df(80,0,60));

    bodyDef.position.Set(80, 60);
    body10= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(40/2, 60/2);
    body10->CreateFixture(&bodyShape, 1.0f);

///11
    scene::IMesh *mura11 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 40.f));
    scene::IMeshSceneNode *muro11 = smgr->addMeshSceneNode(mura11);
    smgr->getMeshManipulator()->setVertexColors(muro11->getMesh(),video::SColor(0, 0, 0, 0));
    muro11->setPosition(core::vector3df(10,0,80));

    bodyDef.position.Set(10, 80);
    body11= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(40/2, 40/2);
    body11->CreateFixture(&bodyShape, 1.0f);

///12
    scene::IMesh *mura12 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 40.f));
    scene::IMeshSceneNode *muro12 = smgr->addMeshSceneNode(mura12);
    smgr->getMeshManipulator()->setVertexColors(muro12->getMesh(),video::SColor(0, 0, 0, 0));
    muro12->setPosition(core::vector3df(70,0,160));

    bodyDef.position.Set(70, 160);
    body12= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(40/2, 40/2);
    body12->CreateFixture(&bodyShape, 1.0f);

///13
    scene::IMesh *mura13 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 40.f));
    scene::IMeshSceneNode *muro13 = smgr->addMeshSceneNode(mura13);
    smgr->getMeshManipulator()->setVertexColors(muro13->getMesh(),video::SColor(0, 0, 0, 0));
    muro13->setPosition(core::vector3df(90,0,180));

    bodyDef.position.Set(90, 180);
    body13= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(40/2, 40/2);
    body13->CreateFixture(&bodyShape, 1.0f);

///14
    scene::IMesh *mura14 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 40.f));
    scene::IMeshSceneNode *muro14 = smgr->addMeshSceneNode(mura14);
    smgr->getMeshManipulator()->setVertexColors(muro14->getMesh(),video::SColor(0, 0, 0, 0));
    muro14->setPosition(core::vector3df(110,0,200));

    bodyDef.position.Set(110, 200);
    body14= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(40/2, 40/2);
    body14->CreateFixture(&bodyShape, 1.0f);

///15
    scene::IMesh *mura15 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 40.f));
    scene::IMeshSceneNode *muro15 = smgr->addMeshSceneNode(mura15);
    smgr->getMeshManipulator()->setVertexColors(muro15->getMesh(),video::SColor(0, 0, 0, 0));
    muro15->setPosition(core::vector3df(130,0,220));

    bodyDef.position.Set(130, 220);
    body15= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(40/2, 40/2);
    body15->CreateFixture(&bodyShape, 1.0f);

///16
    scene::IMesh *mura16 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 250.f));
    scene::IMeshSceneNode *muro16 = smgr->addMeshSceneNode(mura16);
    smgr->getMeshManipulator()->setVertexColors(muro16->getMesh(),video::SColor(0, 0, 0, 0));
    muro16->setPosition(core::vector3df(40,0,230));
    muro16->setRotation(core::vector3df(0,45,0));

    bodyDef.position.Set(40, 230);
    body16= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(10/2, 250/2);
    body16->CreateFixture(&bodyShape, 1.0f);

///17
    scene::IMesh *mura17 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 70.f));
    scene::IMeshSceneNode *muro17 = smgr->addMeshSceneNode(mura17);
    smgr->getMeshManipulator()->setVertexColors(muro17->getMesh(),video::SColor(0, 0, 0, 0));
    muro17->setPosition(core::vector3df(150,0,300));
    muro17->setRotation(core::vector3df(0,-45,0));

    bodyDef.position.Set(150, 300);
    body17= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(10/2, 70/2);
    body17->CreateFixture(&bodyShape, 1.0f);

///18
    scene::IMesh *mura18 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 70.f));
    scene::IMeshSceneNode *muro18 = smgr->addMeshSceneNode(mura18);
    smgr->getMeshManipulator()->setVertexColors(muro18->getMesh(),video::SColor(0, 0, 0, 0));
    muro18->setPosition(core::vector3df(230,0,220));
    muro18->setRotation(core::vector3df(0,-45,0));

    bodyDef.position.Set(230, 220);
    body18= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(10/2, 70/2);
    body18->CreateFixture(&bodyShape, 1.0f);

///19
    scene::IMesh *mura19 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 150.f));
    scene::IMeshSceneNode *muro19 = smgr->addMeshSceneNode(mura19);
    smgr->getMeshManipulator()->setVertexColors(muro19->getMesh(),video::SColor(0, 0, 0, 0));
    muro19->setPosition(core::vector3df(255,0,125));

    bodyDef.position.Set(255, 125);
    body19= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(10/2, 150/2);
    body19->CreateFixture(&bodyShape, 1.0f);smgr->getMeshManipulator()->setVertexColors(muro1->getMesh(),video::SColor(0, 0, 0, 0));

///20
    scene::IMesh *mura20 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 150.f));
    scene::IMeshSceneNode *muro20 = smgr->addMeshSceneNode(mura20);
    smgr->getMeshManipulator()->setVertexColors(muro20->getMesh(),video::SColor(0, 0, 0, 0));
    muro20->setPosition(core::vector3df(300,0,125));

    bodyDef.position.Set(300, 125);
    body20= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(10/2, 150/2);
    body20->CreateFixture(&bodyShape, 1.0f);

///21
    scene::IMesh *mura21 = smgr->getGeometryCreator()->createCubeMesh(vector3df(40.f, 10.f, 80.f));
    scene::IMeshSceneNode *muro21 = smgr->addMeshSceneNode(mura21);
    smgr->getMeshManipulator()->setVertexColors(muro21->getMesh(),video::SColor(0, 0, 0, 0));
    muro21->setPosition(core::vector3df(160,0,70));

    bodyDef.position.Set(160, 70);
    body21= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(40/2, 80/2);
    body21->CreateFixture(&bodyShape, 1.0f);

///22
    scene::IMesh *mura22 = smgr->getGeometryCreator()->createCubeMesh(vector3df(60.f, 10.f, 10.f));
    scene::IMeshSceneNode *muro22 = smgr->addMeshSceneNode(mura22);
    smgr->getMeshManipulator()->setVertexColors(muro22->getMesh(),video::SColor(0, 0, 0, 0));
    muro22->setPosition(core::vector3df(120,0,40));

    bodyDef.position.Set(120, 40);
    body22= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(60/2, 10/2);
    body22->CreateFixture(&bodyShape, 1.0f);

///23
    scene::IMesh *mura23 = smgr->getGeometryCreator()->createCubeMesh(vector3df(15.f, 10.f, 10.f));
    scene::IMeshSceneNode *muro23 = smgr->addMeshSceneNode(mura23);
    smgr->getMeshManipulator()->setVertexColors(muro23->getMesh(),video::SColor(0, 0, 0, 0));
    muro23->setPosition(core::vector3df(135,0,100));

    bodyDef.position.Set(135, 100);
    body23= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(15.f/2, 10/2);
    body23->CreateFixture(&bodyShape, 1.0f);

///24
    scene::IMesh *mura24 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 100.f));
    scene::IMeshSceneNode *muro24 = smgr->addMeshSceneNode(mura24);
    smgr->getMeshManipulator()->setVertexColors(muro24->getMesh(),video::SColor(0, 0, 0, 0));
    muro24->setPosition(core::vector3df(210,0,20));
    muro24->setRotation(core::vector3df(0,-60,0));

    bodyDef.position.Set(210, 20);
    body24= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(10/2, 100/2);
    body24->CreateFixture(&bodyShape, 1.0f);

///25
    scene::IMesh *mura25 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 90.f));
    scene::IMeshSceneNode *muro25 = smgr->addMeshSceneNode(mura25);
    smgr->getMeshManipulator()->setVertexColors(muro25->getMesh(),video::SColor(0, 0, 0, 0));
    muro25->setPosition(core::vector3df(280,0,30));
    muro25->setRotation(core::vector3df(0,45,0));

    bodyDef.position.Set(280, 30);
    body25= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(10/2, 90/2);
    body25->CreateFixture(&bodyShape, 1.0f);

///26
    scene::IMesh *mura26 = smgr->getGeometryCreator()->createCubeMesh(vector3df(10.f, 10.f, 25.f));
    scene::IMeshSceneNode *muro26 = smgr->addMeshSceneNode(mura26);
    smgr->getMeshManipulator()->setVertexColors(muro26->getMesh(),video::SColor(0, 0, 0, 0));
    muro26->setPosition(core::vector3df(255,0,20));
    muro26->setRotation(core::vector3df(0,-60,0));

    bodyDef.position.Set(255, 20);
    body26= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(10/2, 25.f/2);
    body26->CreateFixture(&bodyShape, 1.0f);
*/
}
