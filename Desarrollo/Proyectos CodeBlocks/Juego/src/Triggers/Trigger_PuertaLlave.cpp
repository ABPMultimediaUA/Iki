#include "Trigger_PuertaLlave.h"
#include "Player.h"
#include "PhisicsWorld.h"
#include "Fachada/GraphicsFacade.h"

Trigger_PuertaLlave::Trigger_PuertaLlave(float x, float z, float r)
{
    mx=x;mz=z;ma=r;

    puerta = new MeshSceneNode("resources/Modelos/puerta_puerta.obj");
    //puerta->setTexture("resources/Texturas/plancha.png");

    //b2body
        b2BodyDef bodyDef;
        bodyDef.type = b2_kinematicBody;
        bodyDef.position.Set(x,z);
        body = PhisicsWorld::getInstance()->getWorld()->CreateBody(&bodyDef);
        posicion = {body->GetPosition().x,0,body->GetPosition().y};

        b2PolygonShape bodyShape;
        bodyShape.SetAsBox(8.f,1.f);
        body->CreateFixture(&bodyShape, 1.0f);
        body->SetTransform({posicion.X,posicion.Z},r);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &bodyShape;
        body->CreateFixture(&fixtureDef);
        puerta->setPosition(posicion);
        puerta->setRotation(r);
}

Trigger_PuertaLlave::~Trigger_PuertaLlave()
{
    //dtor
    delete puerta;
    body->GetWorld()->DestroyBody(body);
}

void Trigger_PuertaLlave::triggerDisparado()
{
    if (!fired){
        SoundMgr->playSonido("Triggers/puerta_abrir");
        SoundMgr->playSonido("Triggers/acceso_confirmado");
        fired = true;
    }

    f32 tiempo = GraphicsFacade::getInstance().getTimer()->getTime()/1000.f;
    if (tiempo - timer > 0.05){
        timer = tiempo;
        if (posicion.Y > -8){
            posicion.Y -= 0.5f;
            puerta->setPosition(posicion);
        }

        if (tiempo - time2 > 3){
            time2 = tiempo;
            body->SetTransform(b2Vec2(mx+5,mz),0);
            body->SetActive(false);
            this->SetInactive();
        }
    }
}

void Trigger_PuertaLlave::Try(GameEntity* ent)
{
    if (isActive() && ent->isPlayer() && isTouchingTrigger(ent->getPosition(), ent->getRadio())){

        if (static_cast<Player*>(ent)->GetLlaves() > 0){
            static_cast<Player*>(ent)->UsarLlave();
            abierta = true;
        }else{
            if (!fired){
                SoundMgr->playSonido("Triggers/acceso_denegado");
                static_cast<Player*>(ent)->NecesitoLlave();
                fired = true;
            }
        }
    }

}

void Trigger_PuertaLlave::Update()
{
    if (abierta){
        triggerDisparado();
    }
}
