#include "Enemy.h"
#include "Fachada/GraphicsFacade.h"
#include "PatrolPoint.h"
#include "PatrolRoute.h"
#include "PhisicsWorld.h"
#include "Enemies/Path/PathPlanner.h"
#include "MapComponent.h"
#include "Muerto.h"
#include "Enemies/Guardia.h"

#include "Trigger.h"
#include "TriggerSystem.h"

void Enemy::update(){
    posicionProta = EntityMgr->getEntityByID(0)->getPosition();
    distanciaPlayer = posicionProta.Distance(posicion);
    //toProtaPosition=posicionProta-posicion;

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
    //modelo = GraphicsFacade::getInstance().createCubeSceneNode(2, posicion);
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

    time_since_hitted = 0;

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
    fixtureDef.density  = 1.f;
    fixtureDef.friction = 0.f;
    fixtureDef.restitution  = 0.f;
    body->CreateFixture(&fixtureDef);
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
    if(p.isSecondInFOVOfFirst(posicion,mirandoHacia,destino,120*DegToRad) && !isPathObstructured(posicionProta))
        return true;
    else
        return false;
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
    std::vector<Trigger*> triggers = TriggerSystem::getInstance()->GetTriggers();
    for (int i = 0; i < triggers.size(); i++) {
        if (triggers.at(i)->isPuerta()){
                if(triggers.at(i)->getBody()->GetFixtureList())
            if (triggers.at(i)->getBody()->GetFixtureList()->RayCast(&output2,input,0)){
                return true;
            }
        }
    }

    //if(colisionPuertas(destino))
        //return true;
    return false;
}
bool Enemy::colisionPuertas(Structs::TPosicion destino){
    input.p1.Set(this->getBody()->GetPosition().x, this->getBody()->GetPosition().y);	//	Punto	inicial	del	rayo (la posicion del prota)
    input.p2.Set(destino.X, destino.Z);	//	Punto final del	rayo (la posicion que le paso)
    ///colision con triggers con body
    std::vector<Trigger*> triggers = TriggerSystem::getInstance()->GetTriggers();
    for (int i = 0; i < triggers.size(); i++) {
        if (triggers.at(i)->isPuerta()){
                //std::cout<<i<<std::endl;
            if (triggers.at(i)->getBody()->GetFixtureList()->RayCast(&output2,input,0)){
                std::cout<<"entraaaa"<<std::endl;
                return true;
            }
        }
    }

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
    return true;
}

void Enemy::crearPath(Structs::TPosicion destino){
    listaEjes.clear();
    if(path->crearPath(destino,listaEjes))
    it=listaEjes.begin();
}
void Enemy::setPosition(){
    body->SetTransform(b2Vec2(posicion.X, posicion.Z), angulo);
    aniMesh->setRotation(body->GetAngle());
    aniMesh->setPosition(Structs::TPosicion{body->GetPosition().x, 0, body->GetPosition().y});
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
        mirandoHacia=toNextNodo;
        toNextNodo.Normalize();
        posicion=posicion+toNextNodo*(avMovement*velocidad);
        calcularAngulo((*it).getDestination());
    }
}
void Enemy::cambiarColor(Structs::TColor c){
    aniMesh->cambiarColor(c);
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
bool Enemy::hayGuardias(){
    if(EntityMgr->hayGuardia())
        return true;
    return false;
}
void Enemy::quitarVida(){
    if(GraphicsFacade::getInstance().getTimer()->getTime()/1000.f - time_since_hitted > 0.8){
        if(vida > 0){
            SoundMgr->playSonido("Player/metal2");
            vida--;
            time_since_hitted = GraphicsFacade::getInstance().getTimer()->getTime()/1000.f;
        }
        else{
            SoundMgr->playSonido("Player/metal1");
            GetFSM()->ChangeState(Muerto::Instance());
        }
    }
}
///PARA MOVER CON IMPULSOS?¿
void Enemy::moverBody(Structs::TPosicion vec){
    vec.Normalize();
    float movx = vec.X * avMovement*5;
    float movy = vec.Z * avMovement*5;
    body->SetLinearVelocity(b2Vec2(movx, movy));
}
void Enemy::MoverEnemigo(Structs::TPosicion p){
    body->SetTransform(body->GetPosition(), angulo);
    moverBody(p);
    posicion = {body->GetPosition().x, 0, body->GetPosition().y};
    aniMesh->setPosition(posicion);
    aniMesh->setRotation(body->GetAngle());
}
///ESTADOS

void Enemy::patrullar()
{

   if(posicion.Distance(pRuta->getPunto()) >0.5) //AVANZAR
    {
        //MoverEnemigo(posinit);
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
        mirandoHacia=posinit;
        posinit.Normalize();
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
    if(sospecha < 100 && distanciaPlayer<30 && isEnemySeeing(posicionProta))
    {
        calcularAngulo(posicionProta);
        sospecha++;;
        //std::cout<<"Sospecha: "<<sospecha<<std::endl;
    }
     setPosition();
}
void Enemy::escuchar(){
    calcularAngulo(posicionProta);
    setPosition();
}
void Enemy::volverALaPatrulla(){
    andarPath(1,pRuta->getPunto());
    setPosition();
}
void Enemy::muerto(){
    posicion = {1000,0,1000};
    setPosition();
    if(this->isGuardia())
        static_cast<Guardia*>(this)->setModeloVisible(false);
    EntityMgr->borrarEnemigo(this);
}
