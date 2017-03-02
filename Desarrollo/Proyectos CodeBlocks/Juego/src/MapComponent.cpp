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
    bodyShape.SetAsBox(2.f/2, 2.f/2);
    body->CreateFixture(&bodyShape, 1.0f);
    body->SetTransform(b2Vec2(b.X, b.Z), 180 / 3.14159265358979323846 * a);

    modelo = new AnimatedMesh("Modelos/cubito.obj", color, b, a);

        //file = "Modelos/cubito.obj";
        /*bodyDef.type = b2_staticBody;
        bodyDef.position.Set(b.X, b.Z);
        body = PhisicsWorld::getInstance().getWorld()->CreateBody(&bodyDef);
        bodyShape.SetAsBox(2.f/2, 2.f/2);
        body->CreateFixture(&bodyShape, density);

        modelo = new AnimatedMesh("Modelos/cubito.obj", color);*/
        //file = "Modelos/cubito.obj";


}

MapComponent::~MapComponent()
{
    //dtor
}
