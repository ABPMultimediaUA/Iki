#include "Enemy.h"
#include "Fachada/GraphicsFacade.h"
#include "PatrolPoint.h"
#include "PatrolRoute.h"
#include "PhisicsWorld.h"
#include "Path/PathPlanner.h"
#include "MapComponent.h"

void Enemy::update(){
    posicionProta = EntityMgr->getEntityByID(0)->getPosition();
    distanciaPlayer = posicionProta.Distance(posicion);

    deltaTime = PhisicsWorld::getInstance()->getDeltaTime()/1000;
    avMovement = deltaTime * 9.5; //9.5 es la velocidad
    tiempoEnEstado = PhisicsWorld::getInstance()->getDeltaTime()/1000 + tiempoEnEstado;
    G_stateMachine->Update();
}
void Enemy::init(Map* m){
    //Almaceno el mapa
    Mapa = m;
    //Creo los body y cosas box2d;
    crearBody();
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
    //Pathplanning
    grafo = Mapa->getGrafo();
    path = new PathPlanner(grafo,this);
     //Para los ray!
    input.maxFraction	=	1.0f;
}
void Enemy::crearBody(){
    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;
    bodyDef.position.Set(posicion.X, posicion.Z);
    body = PhisicsWorld::getInstance()->getWorld()->CreateBody(&bodyDef);

    b2PolygonShape bodyShape;
    bodyShape.SetAsBox(1, 1);
    body->CreateFixture(&bodyShape, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &bodyShape;
    fixtureDef.friction = 10.f;
    fixtureDef.restitution  = 0.0f;
    fixtureDef.density  = 10.f;
    body->CreateFixture(&fixtureDef);
}
void Enemy::setPosition(){
    body->SetTransform(b2Vec2(posicion.X, posicion.Z), angulo);
    modelo->setRotation(body->GetAngle());
    modelo->setPosition(Structs::TPosicion{body->GetPosition().x, 0, body->GetPosition().y});
}
void Enemy::SetID(int val){
    assert ( (val >= nextID) && "<GameEntity::SetID>: invalid ID");
    id = val;
    nextID = id + 1;
}
void Enemy::crearPath(Structs::TPosicion destino){
    listaEjes.clear();
    if(path->crearPath(destino,listaEjes))
        std::cout<<"Path creado"<<std::endl;
    it=listaEjes.begin();
}
bool Enemy::isPathObstructured(Structs::TPosicion destino){
    input.p1.Set(this->getBody()->GetPosition().x, this->getBody()->GetPosition().y);	//	Punto	inicial	del	rayo (la posicion del prota)
    input.p2.Set(destino.X, destino.Z);	//	Punto final del	rayo (la posicion que le paso)

    ///colision con paredes
    for (int i = 0; i < Mapa->muros.size(); i++) {
        if (Mapa->muros.at(i)->body->GetFixtureList()->RayCast(&output,input,0)){
            return true;
        }
    }

    return false;
}
bool Enemy::canWalkBetween(Structs::TPosicion desde, Structs::TPosicion hasta){

     input.p1.Set(desde.X, hasta.Z);	//	Punto	inicial	del	rayo
     input.p2.Set(hasta.X, hasta.Z);	//	Punto	final	del	rayo

      ///colision con paredes
    for (int i = 0; i < Mapa->muros.size(); i++) {
        if (Mapa->muros.at(i)->body->GetFixtureList()->RayCast(&output,input,0)){
            return true;
        }
    }

    return false;
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

