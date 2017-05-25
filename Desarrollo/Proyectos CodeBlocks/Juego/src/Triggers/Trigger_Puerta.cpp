#include "Trigger_Puerta.h"
#include "GameEntity.h"
#include "SoundManager.h"
#include "PhisicsWorld.h"
#include "Fachada/GraphicsFacade.h"

Trigger_Puerta::Trigger_Puerta(float x, float z, float r)
{
    mx=x;mz=z;ma=r;

    puerta = new MeshSceneNode("resources/Modelos/puerta_puerta.obj");
    puerta->setTexture("resources/Texturas/puerta_puerta.png");

    //b2body
    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;
    bodyDef.position.Set(x,z);
    body = PhisicsWorld::getInstance()->getWorld()->CreateBody(&bodyDef);
    posicion = {body->GetPosition().x,0,body->GetPosition().y};

    b2PolygonShape bodyShape;
    bodyShape.SetAsBox(10.f,1.f);
    body->CreateFixture(&bodyShape, 1.0f);
    body->SetTransform({posicion.X,posicion.Z},r);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &bodyShape;
    body->CreateFixture(&fixtureDef);
    puerta->setPosition(posicion);
    puerta->setRotation(r);

}

Trigger_Puerta::~Trigger_Puerta()
{
    //dtor
    delete puerta;
    body->GetWorld()->DestroyBody(body);
}

void Trigger_Puerta::triggerDisparado()
{
    fired = true;
    SoundMgr->soundStop("Triggers/puerta_cerrar");
    SoundMgr->playSonido("Triggers/puerta_abrir");
}

void Trigger_Puerta::triggerFuera()
{
    fired = false;
    SoundMgr->soundStop("Triggers/puerta_abrir");
    SoundMgr->playSonido("Triggers/puerta_cerrar");
}

void Trigger_Puerta::Try(GameEntity* ent)
{
    if (isActive() && isTouchingTrigger(ent->getPosition(), ent->getRadio())){
        if (!fired)
            triggerDisparado();

        f32 tiempo = GraphicsFacade::getInstance().getTimer()->getTime()/1000.f;
        if (tiempo - aniTime > 0.025){
            aniTime = tiempo;
            time2+=0.025;
            if (posicion.Y > -8){
                posicion.Y -= 0.25f;
                puerta->setPosition(posicion);
            }
        }

        if (!abierta){
            if (time2 > 1.25){
                time2 = 0;
                abierta = true;
                body->SetTransform(b2Vec2(mx,mz+10),0);
                body->SetActive(false);
            }else{
                abierta = false;
                body->SetTransform(b2Vec2(mx,mz),0);
                body->SetActive(true);
            }
        }
    }
}

void Trigger_Puerta::Update()
{
    if(noHayNingunaEntidad()){
        if (fired)
            triggerFuera();

        f32 tiempo = GraphicsFacade::getInstance().getTimer()->getTime()/1000.f;
        if (tiempo - aniTime > 0.025){
            aniTime = tiempo;
            if (posicion.Y < 0){
                posicion.Y += 0.25f;
                puerta->setPosition(posicion);
            }
        }

        abierta = false;
        body->SetTransform(b2Vec2(mx,mz),0);
        body->SetActive(true);

    }
}
