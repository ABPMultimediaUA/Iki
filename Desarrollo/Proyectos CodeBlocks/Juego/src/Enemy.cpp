#include "Enemy.h"
#include "Fachada/GraphicsFacade.h"
#include "PatrolPoint.h"
#include "PatrolRoute.h"
#include "PhisicsWorld.h"
#include "Enemies/Path/PathPlanner.h"
#include "MapComponent.h"

#include "TriggerSystem.h"
#include "Trigger.h"

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
    pRuta = ruta->getInicial()->getNext();
    direccion = 0;
    posVigilando = 0;
    //creo un cubo
    modelo = GraphicsFacade::getInstance().createCubeSceneNode(2, posicion);
    //inicializo una posicion auxiliar y una posicion inicial para darle un angulo al enemigo
    posaux = Structs::TPosicion{body->GetPosition().x, 0, body->GetPosition().y};
    posinit = pRuta->getPunto()-posaux;
    posinit.Normalize();
    mirandoHacia=posinit;
    angulo = atan2f((posinit.Z) ,-(posinit.X)) * 180.f /PI;
    //Pathplanning
    grafo = Mapa->getGrafo();
    path = new PathPlanner(grafo,this);
     //Para los ray!
    input.maxFraction	=	1.0f;

    EntityMgr->registrarEntity(this);
    EntityMgr->registrarEnemigo(this);
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
bool Enemy::isPathObstructured(Structs::TPosicion destino){
    input.p1.Set(this->getBody()->GetPosition().x, this->getBody()->GetPosition().y);	//	Punto	inicial	del	rayo (la posicion del prota)
    input.p2.Set(destino.X, destino.Z);	//	Punto final del	rayo (la posicion que le paso)

    ///colision con paredes
    for (int i = 0; i < Mapa->muros.size(); i++) {
        if (Mapa->muros.at(i)->body->GetFixtureList()->RayCast(&output,input,0)){
            return true;
        }
    }

        ///colision con triggers con body
    TriggerSystem::TriggerList triggers = TriggerSystem::getInstance()->GetTriggers();
    for (int i = 0; i < triggers.size(); i++) {
        if (triggers.at(i)->getBody()){
            if (triggers.at(i)->getBody()->GetFixtureList()->RayCast(&output,input,0)){
                return false;
            }
        }
    }


    return false;
}
bool Enemy::isWithinFOV(Structs::TPosicion p, float distanceFOV){
    if(posicion.Distance(p) < distanceFOV ){
        if(vectorIsInFOV(p))
            return true;
    }
    return false;

}
bool Enemy::vectorIsInFOV(Structs::TPosicion p){
    Structs::TPosicion target = posicion - p;
    float angle = (float)atan2(target.Y,target.Z);
    //continua...
}
bool Enemy::isEnemySeeing(Structs::TPosicion destino){
    Structs::TPosicion p;
    if(p.isSecondInFOVOfFirst(posicion,mirandoHacia,destino,90*DegToRad) && !isPathObstructured(posicionProta))
        return true;
    else
        return false;
}
bool Enemy::canWalkBetween(Structs::TPosicion desde, Structs::TPosicion hasta){

     input.p1.Set(desde.X, desde.Z);	//	Punto	inicial	del	rayo
     input.p2.Set(hasta.X, hasta.Z);	//	Punto	final	del	rayo

        ///colision con paredes
    for (int i = 0; i < Mapa->muros.size(); i++) {
        if (Mapa->muros.at(i)->body->GetFixtureList()->RayCast(&output,input,0)){
            return false;
        }
    }

        ///colision con triggers con body
    TriggerSystem::TriggerList triggers = TriggerSystem::getInstance()->GetTriggers();
    for (int i = 0; i < triggers.size(); i++) {
        if (triggers.at(i)->getBody()){
            if (triggers.at(i)->getBody()->GetFixtureList()->RayCast(&output,input,0)){
                return false;
            }
        }
    }

    return true;
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
void Enemy::andarPath(float velocidad, Structs::TPosicion posFinal){
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
            posicion = posFinal;
    }
    else
    { //CUANDO AUN NO HA LLEGADO A UN NODO
        //MoverEnemigo((*it).getDestination(),toNextNodo);
        toNextNodo.Normalize();
        mirandoHacia=toNextNodo;
        posicion=posicion+toNextNodo*(avMovement*velocidad);
        calcularAngulo((*it).getDestination());
    }
}
void Enemy::cambiarColor(Structs::TColor c){
    modelo->cambiarColor(c);
}
void Enemy::calcularAngulo(Structs::TPosicion p1){
    angulo = atan2f((p1.Z-posicion.Z) ,
                -(p1.X-posicion.X)) * 180.f / irr::core::PI;
}
bool Enemy::isGuardia(){
    if(this->getTipo() == 1){
        return true;
    }
    else
        return false;
}
void Enemy::girarVista(float giro, int posV){
    angulo = angulo + giro;
    posVigilando = posV ;
    double radianes = (-giro) * DegToRad;
    mirandoHacia.rotarVector(radianes);
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
        mirandoHacia=posinit;
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
        calcularAngulo(pRuta->getPunto());
    }
    setPosition();
}

void Enemy::vigilar(){

    if(posVigilando != 1 && tiempoEnEstado < 1.5){
        girarVista(30,1);
    }
    else if(posVigilando != 2 && tiempoEnEstado >= 1.5 && tiempoEnEstado < 3.0){
        girarVista(-30,2);
    }
    else if(posVigilando != 3 && tiempoEnEstado >= 3.0 && tiempoEnEstado < 4.5){
        girarVista(-30,3);
    }
    else if(posVigilando != 4 && tiempoEnEstado >= 4.5){
        girarVista(30,4);
    }
    setPosition();
}
void Enemy::escanear(){
    calcularAngulo(posicionProta);
    setPosition();
    if(tiempoEnEstado < 1.5 && sospecha < 99 && distanciaPlayer<15)
    {
        sospecha += 1;
        //std::cout<<"Sospecha: "<<sospecha<<std::endl;
    }
}
void Enemy::volverALaPatrulla(){
    andarPath(1,pRuta->getPunto());
    setPosition();
}
void Enemy::muerto(){
    posicion = {1000,0,1000};
    setPosition();
}
