#include "Muros.h"
#include "MapComponent.h"
#include "PhisicsWorld.h"
#include "Fachada/AnimatedMesh.h"

Muros::Muros(MapComponent* inicio, MapComponent* fin)
{
    float x = (fin->getPosition().X + inicio->getPosition().X) / 2;
    float y = (fin->getPosition().Z + inicio->getPosition().Z) / 2;

    float angulo = calcularAngulo(fin->getPosition(), inicio->getPosition());

    b2BodyDef bodyDef;
    b2PolygonShape bodyShape;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(x, y);
    body = PhisicsWorld::getInstance()->getWorld()->CreateBody(&bodyDef);

    //bodyShape.SetAsBox(1,1);
    bodyShape.SetAsBox(fin->getPosition().X - inicio->getPosition().X + 1.f, fin->getPosition().Z - inicio->getPosition().Z + 1.f);
    body->CreateFixture(&bodyShape, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &bodyShape;
    fixtureDef.density  = 100.f;
    fixtureDef.friction = 100.f;
    fixtureDef.restitution  = -100.f;
    body->CreateFixture(&fixtureDef);

    body->SetTransform(b2Vec2(x, y), 180 / (3.14159265 * angulo));

    std::cout<<"Posicion X: "<<body->GetPosition().x<<std::endl;
    std::cout<<"Posicion Y: "<<body->GetPosition().y<<std::endl;
    std::cout<<"Angulo: "<<body->GetAngle()<<std::endl;

}

Muros::~Muros()
{
    //dtor
}

float Muros::calcularAngulo(Structs::TPosicion p1, Structs::TPosicion p2){
    float angulo = atan2f((p1.X-p2.X) ,
                -(p1.Z-p2.Z)) * 180.f / irr::core::PI;
    return angulo;
}
