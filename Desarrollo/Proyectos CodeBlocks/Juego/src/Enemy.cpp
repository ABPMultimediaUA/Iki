#include "Enemy.h"
#include "Fachada/GraphicsFacade.h"
#include "PatrolPoint.h"
#include "PatrolRoute.h"
#include "PhisicsWorld.h"

void Enemy::init(Map* m){
    //ID del enemigo
    id = nextID;
    nextID++;
    //Almaceno el mapa
    Mapa = m;
    //Creo los body y cosas box2d esto podria ser una funcion
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(posicion.X, posicion.Z);
    body = PhisicsWorld::getInstance()->getWorld()->CreateBody(&bodyDef);
    b2PolygonShape bodyShape;
    bodyShape.SetAsBox(1, 1);
    body->CreateFixture(&bodyShape, 1.0f);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &bodyShape;
    fixtureDef.friction = 10.5f;
    fixtureDef.restitution  = 0.9f;
    fixtureDef.density  = 10.f;
    body->CreateFixture(&fixtureDef);
    //incializo un punto de ruta
    pRuta = ruta->getInicial();
    direccion = 0;
    estadoVigilando = 0;
    //creo un cubo
    modelo = GraphicsFacade::getInstance().createCubeSceneNode(2, posicion);
    //inicializo una posicion auxiliar y una posicion inicial para darle un angulo al enemigo
    posaux = Structs::TPosicion{body->GetPosition().x, 0, body->GetPosition().y};
    posinit = pRuta->getPunto()-posaux;
    angulo = atan2f((posinit.Z) ,-(posinit.X)) * 180.f /PI;
}
void Enemy::setPosition(){
    body->SetTransform(b2Vec2(posicion.X, posicion.Z), angulo);
    modelo->setPosition(Structs::TPosicion{body->GetPosition().x, 0, body->GetPosition().y});
    modelo->setRotation(body->GetAngle());
}

///ESTADOS

void Enemy::patrullar()
{

   if(posaux.Distance(pRuta->getPunto()) >0.1) //AVANZAR
    {
        posinit.Normalize();
        posaux = posaux + posinit * avMovement;
    }
    else //CUANDO LLEGA A UN PUNTO PATRULLA
    {
        posaux = pRuta->getPunto();
        if(direccion == 0){
            if(pRuta->getNext() == pRuta->getPrev())
                direccion = 1;
            pRuta = pRuta->getNext();

        }else{
            if(pRuta->getNext() == pRuta->getPrev())
                direccion = 0;
            pRuta = pRuta->getPrev();
        }

        posinit = pRuta->getPunto() - posaux;

    }
    posicion = posaux;
    angulo = atan2f((pRuta->getPunto().Z-posicion.Z) ,-(pRuta->getPunto().X-posicion.X)) * 180.f /PI;
    setPosition();

}

void Enemy::vigilar(){

    if(estadoVigilando != 1 && tiempoEnEstado < 1.5){
        angulo += 30;
        estadoVigilando = 1;
    }
    else if(estadoVigilando != 2 && tiempoEnEstado >= 1.5 && tiempoEnEstado < 3.0){
        angulo -= 60;
        estadoVigilando = 2;
    }
    else if(estadoVigilando != 3 && tiempoEnEstado >= 3.0){
        angulo += 30;
        estadoVigilando = 3;
    }


    setPosition();
}

