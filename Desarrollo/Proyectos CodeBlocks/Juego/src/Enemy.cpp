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
    tiempoEnEstado =  tiempoEnEstado + PhisicsWorld::getInstance()->getDeltaTime()/1000;
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
bool Enemy::isEnemySeeing(Structs::TPosicion destino){
    float anguloQueForman = atan2f((destino.Z-posicion.Z) , -(destino.X-posicion.X)) * 180.f / irr::core::PI;
    if (anguloQueForman < angulo+30 && anguloQueForman > angulo-30 && !isPathObstructured(posicionProta) )
        return true;
    else
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
    fixtureDef.friction = 0.f;
    fixtureDef.restitution  = -1.f;
    fixtureDef.density  = 1.f;
    body->CreateFixture(&fixtureDef);
}
void Enemy::setID(int val){
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
void Enemy::setPosition(){
    body->SetTransform(b2Vec2(posicion.X, posicion.Z), angulo);
    modelo->setRotation(body->GetAngle());
    modelo->setPosition(Structs::TPosicion{body->GetPosition().x, 0, body->GetPosition().y});
}
///PARA MOVER CON IMPULSOS?¿
void Enemy::moverBody(Structs::TPosicion vec){
    vec.Normalize();
    float movx = vec.X * avMovement *40;
    float movy = vec.Z * avMovement *40;
    body->SetLinearVelocity(b2Vec2(movx, movy));
}
void Enemy::MoverEnemigo(Structs::TPosicion p1,Structs::TPosicion p2){
    body->SetTransform(body->GetPosition(), angulo);
    moverBody(p2);
    posicion = {body->GetPosition().x, 0, body->GetPosition().y};
    modelo->setPosition(posicion);
    modelo->setRotation(body->GetAngle());
}
///ESTADOS

void Enemy::patrullar()
{

   if(posicion.Distance(pRuta->getPunto()) >0.5) //AVANZAR
    {
        //MoverEnemigo(pRuta->getPunto(),posinit);
        posinit.Normalize();
        posicion = posicion + posinit * avMovement;
    }
    else //CUANDO LLEGA A UN PUNTO PATRULLA
    {
        //moverBody(quietoParado);
        posicion = pRuta->getPunto();
        if(direccion == 0){
            if(pRuta->getNext() == pRuta->getPrev())
                direccion = 1;
            pRuta = pRuta->getNext();

        }else{
            if(pRuta->getNext() == pRuta->getPrev())
                direccion = 0;
            pRuta = pRuta->getPrev();
        }

        posinit = pRuta->getPunto() - posicion;
        angulo = atan2f((pRuta->getPunto().Z-posicion.Z) ,
                -(pRuta->getPunto().X-posicion.X)) * 180.f / irr::core::PI;
    }
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
void Enemy::escanear(){
    Structs::TColor color = {0,0,0,0};
    modelo->cambiarColor(color);
    //if(tiempoEnEstado < 1.5 && sospecha < 99 && distanciaPlayer<10 && isEnemySeeing(posicionProta) )
    if(tiempoEnEstado < 1.5 && sospecha < 99 && distanciaPlayer<10)
    {
        sospecha=sospecha+1;
        //std::cout<<"Sospecha: "<<sospecha<<std::endl;
    }
}
void Enemy::volverALaPatrulla(){
      //mover medico con la lista de edges creada
    if(!listaEjes.empty() && it != listaEjes.end())
        toNextNodo = (*it).getDestination() - posicion;
    else
        toNextNodo=quietoParado;

    if(toNextNodo.Length() <= 1) //CUANDO LLEGA AL NODO
    {
        //moverBody(quietoParado);
        if(it != listaEjes.end()) //SI AUN NO ES EL ULTIMO NODO
            it++;
        else
            posicion = pRuta->getPunto();
    }
    else
    { //CUANDO AUN NO HA LLEGADO A UN NODO
        //MoverEnemigo((*it).getDestination(),toNextNodo);
        toNextNodo.Normalize();
        posicion=posicion+toNextNodo*(avMovement*2);
        angulo = atan2f(((*it).getDestination().Z-posicion.Z) ,
                -((*it).getDestination().X-posicion.X)) * 180.f / irr::core::PI;
    }
    setPosition();
}

