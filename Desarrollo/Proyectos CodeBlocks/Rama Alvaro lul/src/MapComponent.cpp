#include "Map.h"



MapComponent::MapComponent(float a, core::vector3df b, scene::ISceneManager* smgr, int i){


    if (i==1){

    b2BodyDef bodyDef;
    bodyDef.type= b2_staticBody;
    iworld= World::Instance();
    b2PolygonShape bodyShape;

    bodyDef.position.Set(b.X, b.Z);
    body= iworld->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(1.f/2, 1.f/2);
    body->CreateFixture(&bodyShape, 1.0f);


    mesh = smgr->getMesh("Modelos/cubito.obj");
//smgr->getParameters()->setAttribute(irr::scene::COLLADA_CREATE_SCENE_INSTANCES, true);

    }
    else if(i==2){

            mesh = smgr->getMesh("Modelos/puertita.obj");
            //smgr->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(0, 128, 128, 0));


    }

    modelo = smgr->addAnimatedMeshSceneNode(mesh);
    modelo->setPosition(b);
    modelo->setRotation(core::vector3df(0, a, 0));
}
