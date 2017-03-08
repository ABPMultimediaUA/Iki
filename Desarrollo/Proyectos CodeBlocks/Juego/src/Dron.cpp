#include "Dron.h"
#include "Fachada/GraphicsFacade.h"
#include "PhisicsWorld.h"

void Dron::update(){
    G_stateMachine->Update();
    avMovement=9.5*PhisicsWorld::getInstance()->getDeltaTime()/1000;

}

void Dron::inicializar_enemigo()
{
    b2BodyDef bodyDef;
    bodyDef.type= b2_dynamicBody;
    bodyDef.position.Set(posicion.X, posicion.Z);
    body = PhisicsWorld::getInstance()->getWorld()->CreateBody(&bodyDef);


    b2PolygonShape bodyShape;
    bodyShape.SetAsBox(1, 1);
    body->CreateFixture(&bodyShape, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &bodyShape;
    fixtureDef.friction = 10.5f;
    fixtureDef.restitution  = 0.9f;
    fixtureDef.density  = 10.f;
    body->CreateFixture(&fixtureDef);


    pRuta = ruta->getInicial();
    Structs::TColor color = {0,255,0,0};
    tipo = 3;
    modelo = GraphicsFacade::getInstance().createCubeSceneNode(2, posicion);
    modelo->cambiarColor(color);

    posaux = Structs::TPosicion{body->GetPosition().x, 0, body->GetPosition().y};
    posinit = pRuta->getPunto()-posaux;
    angulo = atan2f((posinit.Z) ,-(posinit.X)) * 180.f /PI;

}
