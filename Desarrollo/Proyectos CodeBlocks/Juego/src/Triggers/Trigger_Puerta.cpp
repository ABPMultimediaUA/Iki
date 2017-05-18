#include "Trigger_Puerta.h"
#include "GameEntity.h"
#include "SoundManager.h"
#include "PhisicsWorld.h"

Trigger_Puerta::Trigger_Puerta(float x, float z, float r)
{
    mx=x;mz=z;ma=r;
//b2body
    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;
    bodyDef.position.Set(x,z);
    body = PhisicsWorld::getInstance()->getWorld()->CreateBody(&bodyDef);
    posicion = {body->GetPosition().x,0,body->GetPosition().y};

    b2PolygonShape bodyShape;
    if (r==90)                  bodyShape.SetAsBox(5.f,1.f);
    else                        bodyShape.SetAsBox(1.f,5.f);
    body->CreateFixture(&bodyShape, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &bodyShape;
    body->CreateFixture(&fixtureDef);

}

Trigger_Puerta::~Trigger_Puerta()
{
    //dtor
}

void Trigger_Puerta::triggerDisparado()
{
    aniMesh->setVisible(false);
    body->SetTransform(b2Vec2(mx,mz+10),0);
    body->SetActive(false);
    if (!fired){
        //if (!(SoundManager::getInstance()->isPlaying("alarma_sintetizada2"))){
        SoundMgr->soundStop("Triggers/puerta_cerrar");
        SoundMgr->playSonido("Triggers/puerta_abrir");
        fired = true;
    }
}

void Trigger_Puerta::triggerFuera()
{
    if (fired){
        SoundMgr->soundStop("Triggers/puerta_abrir");
        SoundMgr->playSonido("Triggers/puerta_cerrar");
    }
    fired = false;
    aniMesh->setVisible(true);
    body->SetTransform(b2Vec2(mx,mz),0);
    body->SetActive(true);
}

void Trigger_Puerta::Try(GameEntity* ent)
{
    //if (ent->isPlayer())
        if (isActive() && isTouchingTrigger(ent->getPosition(), ent->getRadio())){
            triggerDisparado();
        }
}

void Trigger_Puerta::Update()
{
    if(noHayNingunaEntidad())
        triggerFuera();
}
