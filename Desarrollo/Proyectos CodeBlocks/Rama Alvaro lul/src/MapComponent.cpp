#include "Map.h"


MapComponent::MapComponent(float a, core::vector3df b, scene::ISceneManager* smgr, int i)
{


    if (i==1)
    {

        b2BodyDef bodyDef;
        bodyDef.type= b2_staticBody;
        iworld= World::Instance();
        b2PolygonShape bodyShape;

        bodyDef.position.Set(b.X, b.Z);
        body= iworld->getWorld()->CreateBody(&bodyDef);
        bodyShape.SetAsBox(2.f/2, 2.f/2);
        body->CreateFixture(&bodyShape, 1.0f);


        mesh = smgr->getMesh("Modelos/cubito.obj");
        modelo = smgr->addAnimatedMeshSceneNode(mesh);
        smgr->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(0, 0, 0, 0));


    }
    else if(i==2)
    {

        mesh = smgr->getMesh("Modelos/puertita.obj");
        modelo = smgr->addAnimatedMeshSceneNode(mesh);
        smgr->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(0, 128, 128, 255));

        b2BodyDef bodyDef;
        bodyDef.type= b2_kinematicBody;
        iworld= World::Instance();
        b2PolygonShape bodyShape;

        bodyDef.position.Set(b.X, b.Z);
        body= iworld->getWorld()->CreateBody(&bodyDef);
        bodyShape.SetAsBox(2.f/2, 6.f/2);
        body->CreateFixture(&bodyShape, 1.0f);


    }

    else if(i==3)
    {

        mesh = smgr->getMesh("Modelos/palanca.obj");
        modelo = smgr->addAnimatedMeshSceneNode(mesh);
        smgr->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(0, 128, 128, 128));

        b2BodyDef bodyDef;
        bodyDef.type= b2_kinematicBody;
        iworld= World::Instance();
        b2PolygonShape bodyShape;

        bodyDef.position.Set(b.X, b.Z);
        body= iworld->getWorld()->CreateBody(&bodyDef);
        bodyShape.SetAsBox(1.f/2, 1.f/2);
        body->CreateFixture(&bodyShape, 1.0f);

    }

    else if(i==4)
    {

        mesh = smgr->getMesh("Modelos/objeto.obj");
        modelo = smgr->addAnimatedMeshSceneNode(mesh);
        smgr->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(0, 255, 255, 255));

        b2BodyDef bodyDef;
        bodyDef.type= b2_kinematicBody;
        iworld= World::Instance();
        b2PolygonShape bodyShape;

        bodyDef.position.Set(b.X, b.Z);
        body= iworld->getWorld()->CreateBody(&bodyDef);
        bodyShape.SetAsBox(1.f/2, 1.f/2);
        body->CreateFixture(&bodyShape, 1.0f);

    }

    else if(i==5)
    {

        mesh = smgr->getMesh("Modelos/apisonadora.obj");
        modelo = smgr->addAnimatedMeshSceneNode(mesh);
        smgr->getMeshManipulator()->setVertexColors(modelo->getMesh(),video::SColor(0, 0, 0, 0));

        b2BodyDef bodyDef;
        bodyDef.type= b2_kinematicBody;
        iworld= World::Instance();
        b2PolygonShape bodyShape;

        bodyDef.position.Set(b.X, b.Z);
        body= iworld->getWorld()->CreateBody(&bodyDef);
        bodyShape.SetAsBox(3.f/2, 1.f/2);
        body->CreateFixture(&bodyShape, 1.0f);


    }

    else if(i==6)
    {

    pp = new PatrolPoint(b);

    }

    if(i!=6){
    body->SetTransform(b2Vec2(b.X, b.Z), 180 / 3.14159265358979323846 * a);
    modelo = smgr->addAnimatedMeshSceneNode(mesh);
    modelo->setMaterialFlag(video::EMF_LIGHTING, false);
    modelo->setPosition(b);
    modelo->setRotation(core::vector3df(0, a, 0));
    }


}

core::vector3df MapComponent::getPosicionObjeto()
{
    return modelo->getPosition();
}


bool MapComponent::comprobarPunto(b2Vec2 v)
{
    bool si= false;
    si= body->GetFixtureList()->TestPoint(v);
    return si;
}

void MapComponent::setPosition(core::vector3df vec){

    modelo->setPosition(vec);

}

void MapComponent::Desactivar()
{
    body->SetActive(false);
    modelo->setVisible(false);
}

void MapComponent::Activar()
{
    body->SetActive(true);
    modelo->setVisible(true);
}


void MapComponent::destroyObj()
{
    modelo->remove();
}
