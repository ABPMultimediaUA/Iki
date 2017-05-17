#include "Trigger_Torreta.h"
#include "Fachada/GraphicsFacade.h"
#include "PhisicsWorld.h"

Trigger_Torreta::Trigger_Torreta(float x, float z, float r)
{
    //b2body
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(x,z);
    body = PhisicsWorld::getInstance()->getWorld()->CreateBody(&bodyDef);

    b2PolygonShape bodyShape;
    bodyShape.SetAsBox(1.f,1.f);
    body->CreateFixture(&bodyShape, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &bodyShape;
    body->CreateFixture(&fixtureDef);

    modeloDisparo = new MeshSceneNode("resources/Modelos/rayitoPlayer.obj");
    modeloDisparo->setVisible(true);

    x = 1; y = 1; z = 1;
}

Trigger_Torreta::~Trigger_Torreta()
{
    //dtor
}

void Trigger_Torreta::calcularAngulo(Structs::TPosicion p1){
    //angulo = atan2f((p1.Z-posicion.Z) , -(p1.X-posicion.X)) * 180.f / irr::core::PI;
    //aniMesh->setRotation(angulo);
}

void Trigger_Torreta::triggerDisparado()
{
    fired = true;
    timer = GraphicsFacade::getInstance().getTimer()->getTime()/1000.f;
    aniMesh->setScale({1,1,1});
}

void Trigger_Torreta::Disparar()
{
    x = 1; y = 1; z = 1;

        //Structs::TPosicion vectorAtaque = pProta - posicion;
        //float anguloAtaque = atan2f((vectorAtaque.Z) , -(vectorAtaque.X)) * 180.f / PI;

        //b2RayCastInput input2;
        //input2.p1.Set(posicion.X, posicion.Z);  //  Punto   inicial del rayo
        //input2.p2.Set(posicion.X+((vectorAtaque.X/vectorAtaque.Length())*10), posicion.Z+((vectorAtaque.Z/vectorAtaque.Length())*10));

        //Structs::TPosicion posicionAtaque = {(input2.p2.x + input2.p1.x)/2, 2.5 , (input2.p2.y + input2.p1.y)/2};
        //float distanciaAtaque = sqrt(pow(input2.p2.x - input2.p1.x, 2) + pow(input2.p2.y - input2.p1.y, 2));

        modeloDisparo->setPosition(posicion);
        //modeloDisparo->setRotation(anguloAtaque);

    modeloDisparo->setVisible(true);
}

void Trigger_Torreta::Try(GameEntity* ent)
{
    if (ent->isPlayer())
        if (isActive() && isTouchingTrigger(ent->getPosition(), ent->getRadio())){
            pProta = ent->getPosition();
            if(!fired){
                triggerDisparado();
            }
        }else{
            fired = false;
            x = 1; y = 1; z = 1;
            aniMesh->setScale({1,1,1});
        }

}

void Trigger_Torreta::Update()
{
    if (fired){
        f32 tiempo = GraphicsFacade::getInstance().getTimer()->getTime()/1000.f;
        if (tiempo - timer > 1.5){
            timer = tiempo;
            Disparar();
        }else{
            x += 0.001; y += 0.001; z += 0.001;
            aniMesh->setScale({x,y,z});
        }
    }
}
