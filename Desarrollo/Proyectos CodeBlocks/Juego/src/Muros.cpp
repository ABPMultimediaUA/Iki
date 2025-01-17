#include "Muros.h"
#include "MapComponent.h"
#include "PhisicsWorld.h"
#include "Fachada/MeshSceneNode.h"

Muros::Muros(MapComponent* inicio, MapComponent* fin)
{
    float x = (fin->getPosition().X + inicio->getPosition().X) / 2;
    float y = (fin->getPosition().Z + inicio->getPosition().Z) / 2;

    float distancia = inicio->getPosition().Distance(fin->getPosition());

    float angulo = calcularAngulo(fin->getPosition(), inicio->getPosition());

    Structs::TColor holi = {0,0,0,0};
    Structs::TMedida med = {fin->getPosition().X - inicio->getPosition().X + 1.f, 1.f, fin->getPosition().Z - inicio->getPosition().Z + 1.f};

    //modelo = new MeshSceneNode(med, Structs::TPosicion(x,0,y), holi);

    b2BodyDef bodyDef;
    b2PolygonShape bodyShape;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(x, y);
    body = PhisicsWorld::getInstance()->getWorld()->CreateBody(&bodyDef);

    //bodyShape.SetAsBox(abs(fin->getPosition().X - inicio->getPosition().X + 1.f), abs(fin->getPosition().Z - inicio->getPosition().Z + 1.f));
    bodyShape.SetAsBox(distancia / 2, 1.f);
    body->CreateFixture(&bodyShape, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &bodyShape;
    fixtureDef.density  = 100.f;
    fixtureDef.friction = 100.f;
    fixtureDef.restitution  = -100.f;
    body->CreateFixture(&fixtureDef);

    body->SetTransform(body->GetPosition(), angulo - (PI/2));

}

Muros::~Muros()
{
    body->GetWorld()->DestroyBody(body);
}

float Muros::calcularAngulo(Structs::TPosicion p1, Structs::TPosicion p2){
    float angulo = atan2f((p1.X-p2.X) ,
                -(p1.Z-p2.Z));
    return angulo;
}
