#include "MapComponent.h"
#include "Fachada/AnimatedMesh.h"
#include "PhisicsWorld.h"

MapComponent::MapComponent(float a, Structs::TPosicion b, int i)
{
    Structs::TColor color = {0,0,0,0};

    b2BodyDef bodyDef;
    b2PolygonShape bodyShape;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(b.X, b.Z);
    body = PhisicsWorld::getInstance()->getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(1,1);
    body->CreateFixture(&bodyShape, 1.0f);

    /*b2FixtureDef fixtureDef;
    fixtureDef.shape = &bodyShape;
    fixtureDef.density  = 100.f;
    fixtureDef.friction = 100.f;
    fixtureDef.restitution  = -100.f;
    body->CreateFixture(&fixtureDef);*/

    body->SetTransform(b2Vec2(b.X, b.Z), 180 / 3.14159265358979323846 * a);

//    modelo = new AnimatedMesh("resources/Modelos/cubito.obj", color, b, a);
    modelo->setTexture("resources/Texturas/textura_pared.jpg");

}

MapComponent::~MapComponent()
{
    //dtor
}
