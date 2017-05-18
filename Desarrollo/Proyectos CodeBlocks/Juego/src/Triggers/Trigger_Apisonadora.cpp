#include "Trigger_Apisonadora.h"
#include "PhisicsWorld.h"
#include "Fachada/GraphicsFacade.h"

Trigger_Apisonadora::Trigger_Apisonadora(float x, float z, float r)
{
    plancha = new MeshSceneNode("resources/Modelos/apisonadora-plancha.obj");

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(x,z);
    body = PhisicsWorld::getInstance()->getWorld()->CreateBody(&bodyDef);
    posicion = {body->GetPosition().x,0,body->GetPosition().y};

    b2PolygonShape bodyShape;
    if (r==90)                  bodyShape.SetAsBox(2.f,14.f);
    else                        bodyShape.SetAsBox(14.f,2.f);
    body->CreateFixture(&bodyShape, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &bodyShape;
    body->CreateFixture(&fixtureDef);

    bajando = true;
}

Trigger_Apisonadora::~Trigger_Apisonadora()
{
    delete plancha;
}

void Trigger_Apisonadora::Try(GameEntity* ent)
{
    //if (ent->isPlayer())
        if (isActive() && isTouchingTrigger(ent->getPosition(), ent->getRadio())){
            ent->matar();
        }
}

void Trigger_Apisonadora::Update(){
    if(isActive()){
        movimiento_apisonadora();
    }
}

void Trigger_Apisonadora::movimiento_apisonadora(){
    Structs::TPosicion posi = plancha->getPosition();
    if(bajando){
        posi.Y -= 0.2;
        if(posi.Y <= 0.25)
            bajando = false;
    }else{
        posi.Y += 0.1;
        if(posi.Y >= 8.6f)
            bajando = true;
    }
    plancha->setPosition(posi);
}

void Trigger_Apisonadora::setPosicionPlancha(){
    plancha->setPosition(Structs::TPosicion(aniMesh->getPosition().X, 8.6f, aniMesh->getPosition().Z));
}

void Trigger_Apisonadora::ActDesact(){
    if(GraphicsFacade::getInstance().getTimer()->getTime()/1000.f - timer > 0.5){
        if(this->isActive()){
            body->SetActive(false);
            this->setPosicionPlancha();
            this->SetInactive();
        }
        else
            this->SetActive();
        timer = GraphicsFacade::getInstance().getTimer()->getTime()/1000.f;
    }
}
