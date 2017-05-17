#include "Trigger_PuertaLlave.h"
#include "Player.h"
#include "PhisicsWorld.h"

Trigger_PuertaLlave::Trigger_PuertaLlave(float x, float z, float r)
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

Trigger_PuertaLlave::~Trigger_PuertaLlave()
{
    //dtor
}

void Trigger_PuertaLlave::Try(GameEntity* ent)
{
    if (isActive() && ent->isPlayer() && isTouchingTrigger(ent->getPosition(), ent->getRadio())){

        if (static_cast<Player*>(ent)->GetLlaves() > 0){
            static_cast<Player*>(ent)->UsarLlave();
            aniMesh->setVisible(false);
            body->SetActive(false);
            body->SetTransform(b2Vec2(mx+5,mz),ma);
            SoundMgr->playSonido("Triggers/puerta_abrir");
            SoundMgr->playSonido("Triggers/acceso_confirmado");
            this->SetInactive();
        }else{
            if (!fired){
                SoundMgr->playSonido("Triggers/acceso_denegado");
                static_cast<Player*>(ent)->NecesitoLlave();
                fired = true;
            }
        }
    }

    if (ent->isPlayer() && !isTouchingTrigger(ent->getPosition(), ent->getRadio())){
        fired = false;
        //aniMesh->setVisible(true);
        //body->SetActive(true);
    }
}

void Trigger_PuertaLlave::Update()
{

}
