#include "MapComponent.h"
#include "AnimatedMesh.h"

MapComponent::MapComponent(float a, Structs::TPosicion b, int i)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;
    b2PolygonShape bodyShape;
    Structs::TColor color = {0,0,0,0};
    float alto = 0, ancho = 0;
    const char* cadena = "";

    switch(i){
    case 1:
        bodyDef.type = b2_staticBody;
        alto = 2.f/2;
        ancho = 2.f/2;
        cadena = "Modelos/cubito.obj";
        break;

        //file = "Modelos/cubito.obj";
        /*bodyDef.type = b2_staticBody;
        bodyDef.position.Set(b.X, b.Z);
        body = PhisicsWorld::getInstance().getWorld()->CreateBody(&bodyDef);
        bodyShape.SetAsBox(2.f/2, 2.f/2);
        body->CreateFixture(&bodyShape, density);

        modelo = new AnimatedMesh("Modelos/cubito.obj", color);*/
    case 2:
        alto = 2.f/2;
        ancho = 6.f/2;
        color = {0,128,128,128};
        cadena = "Modelos/puertita.obj";
        break;

        //file = new Files("Modelos/puertita.obj");
        /*bodyDef.type= b2_kinematicBody;
        bodyDef.position.Set(b.X, b.Z);
        body = PhisicsWorld::getInstance().getWorld()->CreateBody(&bodyDef);
        bodyShape.SetAsBox(2.f/2, 6.f/2);
        body->CreateFixture(&bodyShape, 1.0f);

        color = {0,128,128,128};
        modelo = new AnimatedMesh("Modelos/puertita.obj", color);*/
    case 3:
        alto = 1.f/2;
        ancho = 1.f/2;
        color = {0,128,128,128};
        cadena = "Modelos/palanca.obj";
        break;

        //file = new Files("Modelos/palanca.obj");
        /*bodyDef.type= b2_kinematicBody;
        bodyDef.position.Set(b.X, b.Z);
        body = PhisicsWorld::getInstance().getWorld()->CreateBody(&bodyDef);
        bodyShape.SetAsBox(1.f/2, 1.f/2);
        body->CreateFixture(&bodyShape, 1.0f);

        color = {0,128,128,128};
        modelo = new AnimatedMesh("Modelos/palanca.obj", color);*/
    case 4:
        alto = 1.f/2;
        ancho = 1.f/2;
        color = {0,255,255,255};
        cadena = "Modelos/palanca.obj";
        break;

        //file = new Files("Modelos/objeto.obj");
        /*bodyDef.type= b2_kinematicBody;
        bodyDef.position.Set(b.X, b.Z);
        body = PhisicsWorld::getInstance().getWorld()->CreateBody(&bodyDef);
        bodyShape.SetAsBox(1.f/2, 1.f/2);
        body->CreateFixture(&bodyShape, 1.0f);

        color = {0,255,255,255};
        modelo = new AnimatedMesh("Modelos/objeto.obj", color);*/
    case 5:
        alto = 3.f/2;
        ancho = 1.f/2;
        cadena = "Modelos/apisonadora.obj";
        break;

        //file = new Files("Modelos/apisonadora.obj");
        /*bodyDef.type= b2_kinematicBody;
        bodyDef.position.Set(b.X, b.Z);
        body = PhisicsWorld::getInstance().getWorld()->CreateBody(&bodyDef);
        bodyShape.SetAsBox(3.f/2, 1.f/2);
        body->CreateFixture(&bodyShape, 1.0f);

        modelo = new AnimatedMesh("Modelos/apisonadora.obj", color);*/
    default:
        //std::cout<<"Tonto"<<std::endl;
        break;
    }
        //file = "Modelos/cubito.obj";
    bodyDef.position.Set(b.X, b.Z);
    body = PhisicsWorld::getInstance().getWorld()->CreateBody(&bodyDef);
    bodyShape.SetAsBox(ancho, alto);
    body->CreateFixture(&bodyShape, 1.0f);
    body->SetTransform(b2Vec2(b.X, b.Z), 180 / 3.14159265358979323846 * a);

    modelo = new AnimatedMesh(cadena, color, b, a);

}

MapComponent::~MapComponent()
{
    //dtor
}
