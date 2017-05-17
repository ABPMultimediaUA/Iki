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
    modeloDisparo->setVisible(false);
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
}

void Trigger_Torreta::disparo(){
  /*  input.p1.Set(enemigos[5]->getBody()->GetPosition().x, enemigos[5]->getBody()->GetPosition().y);	//	Punto	inicial	del	rayo
            input.p2.Set(prota->getBody()->GetPosition().x, prota->getBody()->GetPosition().y);	//	Punto	final	del	rayo

    distancia = sqrt(pow(input.p2.x-input.p1.x, 2)+pow(input.p2.y-input.p1.y, 2));*/
}

void Trigger_Torreta::Try(GameEntity* ent)
{
    if (ent->isPlayer())
        if (isActive() && isTouchingTrigger(ent->getPosition(), ent->getRadio())){
            if(!fired){
                triggerDisparado();
            }
        }else{
            fired = false;
        }

}

void Trigger_Torreta::Update()
{
    if (fired){
        f32 tiempo = GraphicsFacade::getInstance().getTimer()->getTime()/1000.f;
        if (tiempo - timer > 1.f){
            //timer = tiempo;
            std::cout << "disparando" << std::endl;

        }else{
            std::cout << "cargando" << std::endl;
        }
    }
}
