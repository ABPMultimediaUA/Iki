#include "Enemy.h"
#include "Fachada/GraphicsFacade.h"
#include "PatrolPoint.h"
#include "PatrolRoute.h"
#include "PhisicsWorld.h"
#include "Enemies/Path/PathPlanner.h"
#include "MapComponent.h"
#include "Muerto.h"
#include "Enemies/Guardia.h"
#include "Investigar.h"
#include "Atacar.h"
#include "Player.h"

#include "Trigger.h"
#include "TriggerSystem.h"

void Enemy::update(){
    posicionProta = EntityMgr->getEntityByID(0)->getPosition();
    distanciaPlayer = posicionProta.Distance(posicion);
    toProtaPosition=posicionProta-posicion;
    ///SE RECARGA LA BATERIA POCO A POCO
    /*if (   G_stateMachine->CurrentState() != Atacar::Instance()
        && G_stateMachine->CurrentState() != Investigar::Instance() ){

        f32 tiempo = GraphicsFacade::getInstance().getTimer()->getTime()/1000.f;
        if (tiempo - bateriaT > 0.1){
            //std::cout << bateria << std::endl;
            bateriaT = tiempo;
            if (bateria < 100) bateria += 1;
        }
    }*/

    if (guessing){
        guessing = false;
        posicionInteres = posicionProta;
        G_stateMachine->ChangeState(Investigar::Instance());
    }

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
    bateria = 100;
    fieldOfView = 120*DegToRad;
    //inicializo una posicion auxiliar y una posicion inicial para darle un angulo al enemigo
    posaux = Structs::TPosicion{body->GetPosition().x, 0, body->GetPosition().y};
    posinit = pRuta->getPunto()-posaux;
    posinit.Normalize();
    mirandoHacia=posinit;
    angulo = atan2f((posinit.Z) ,-(posinit.X)) * 180.f /PI;
    //Pathplanning
    grafo = Mapa->getGrafo();
    path = new PathPlanner(grafo,this);
    //SensorMemory
    memory = new SensorMemory(this,10);
     //Para los ray!
    input.maxFraction	=	1.0f;

    time_since_hitted = 0;
    sTime = 0;

    EntityMgr->registrarEntity(this);
    EntityMgr->registrarEnemigo(this);
    questionMark = new MeshSceneNode("resources/Modelos/Interrogacion.obj");
    questionMark->setPosition({posicion.X,6,posicion.Z});
    questionMark->setVisible(false);
    excMark = new MeshSceneNode("resources/Modelos/exclamation.obj");
    excMark->setPosition({posicion.X,6,posicion.Z});
    excMark->setVisible(false);

    modeloAtaque = new MeshSceneNode("resources/Modelos/conoray2.obj");
    modeloAtaque->setTexture("resources/Texturas/rojo.png");
    modeloAtaque->setVisible(false);

    holoScan = new MeshSceneNode("resources/Modelos/holoscan2.obj");
    holoScan->setTexture("resources/Texturas/textura_verde.png");
    holoScan->setVisible(false);
    holoScan->setScale({2,2,2});
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

bool Enemy::isPathObstructured(Structs::TPosicion destino){
    input.p1.Set(this->getBody()->GetPosition().x, this->getBody()->GetPosition().y);	//	Punto	inicial	del	rayo (la posicion del prota)
    input.p2.Set(destino.X, destino.Z);	//	Punto final del	rayo (la posicion que le paso)

    ///colision con paredes
    for (int i = 0; i < Mapa->getMuros().size(); i++) {
        if (Mapa->getMuros().at(i)->getBody()->GetFixtureList()->RayCast(&output,input,0)){
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
    return false;
}
bool Enemy::isEnemySeeing(Structs::TPosicion destino){
    Structs::TPosicion p;
    if(p.isSecondInFOVOfFirst(posicion,mirandoHacia,destino,120*DegToRad) && !isPathObstructured(destino))
        return true;
    else
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
                //std::cout<<"entraaaa"<<std::endl;
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
    for (int i = 0; i < Mapa->getMuros().size(); i++) {
        if (Mapa->getMuros().at(i)->getBody()->GetFixtureList()->RayCast(&output,input,0)){
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
    questionMark->setPosition({posicion.X,6,posicion.Z});
    questionMark->setRotation(90);
    excMark->setPosition({posicion.X,6,posicion.Z});
    excMark->setRotation(90);
}
void Enemy::andarPath(float velocidad, Structs::TPosicion posFinal){

    if (listaEjes.empty()){
        //G_stateMachine->ChangeState(Atacar::Instance());
            mirandoHacia=toProtaPosition;
            toProtaPosition.Normalize();
            posicion=posicion+toProtaPosition*(avMovement*velocidad);
            calcularAngulo(posicionProta);
    }else{
       //mover medico con la lista de edges creada
        if(!listaEjes.empty() && it != listaEjes.end())
            toNextNodo = (*it).getDestination() - posicion;

        if(toNextNodo.Length() <= 1) //CUANDO LLEGA AL NODO
        {
            //moverBody(quietoParado);
            if(it != listaEjes.end()) //SI AUN NO ES EL ULTIMO NODO
                it++;
            else{
                posicion=posFinal;
                // posFinal.Normalize();
               //toPosicionFinal= posFinal - posicion;
               //posicion = posicion+toPosicionFinal *(avMovement*velocidad);
            }
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
}
void Enemy::cambiarColor(Structs::TColor c){
    aniMesh->cambiarColor(c);
}
void Enemy::calcularAngulo(Structs::TPosicion p1){
    angulo = atan2f((p1.Z-posicion.Z) ,
                -(p1.X-posicion.X)) * 180.f / irr::core::PI;
}
void Enemy::girarVista(float giro, int posV){
    angulo = angulo + giro;
    posVigilando = posV ;
    double radianes = (-giro) * DegToRad;
    mirandoHacia.rotarVector(radianes);
}
bool Enemy::hayGuardias(){
    if(EntityMgr->hayGuardia()){
        return true;
    }
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
float Enemy::getTimePlayerHasBeenOutOfView(){
    //std::cout<< "tiempo que ha estado fuera de vista: " << memory->GetTimeEntityHasBeenOutOfView(EntityMgr->getEntityByID(0)) << std::endl;
    //tiempo desde la ultima vez que vio al prota, si es mayor que diez olvido el recuerdo y pongo la sospecha a 0
    return memory->GetTimeEntityHasBeenOutOfView(EntityMgr->getEntityByID(0));
}
float Enemy::getTimeSinceLastSensed(){
    return memory->GetTimeSinceLastSensed(EntityMgr->getEntityByID(0));
}
void Enemy::borrarMemoria(){
    memory->removeMemory(this);
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
void Enemy::actualizarMemoriaVision(GameEntity* entity){
    memory->updateVision(entity);
}
void Enemy::actualizarMemoriaOido(GameEntity* entity){
    memory->updateSoundSource(entity);
}
void Enemy::showExcMark(bool b){
    excMark->setVisible(b);
    questionMark->setVisible(false);
}
void Enemy::subirSospechaValorConcreto(float valor){
    sospecha+=valor;
}
void Enemy::subirSospecha(float velocidad){
    f32 tiempo = GraphicsFacade::getInstance().getTimer()->getTime()/1000.f;
    if (tiempo - sTime > velocidad){
        //std::cout << sospecha << std::endl;
        sTime = tiempo;
        if (sospecha < 100) sospecha++;
    }

    if(sospecha > 0){
        float sos = 1 + sospecha/50;
        questionMark->setScale({sos,sos,sos});
        if (   G_stateMachine->CurrentState()!=Atacar::Instance()
            || G_stateMachine->CurrentState()!=Investigar::Instance() )
            questionMark->setVisible(true);
        else
            questionMark->setVisible(false);
        /*if(sospecha>0 && sospecha<25){
            //questionMark->setScale({1,1,1});
            //questionMark->cambiarColor({0,128,255,0});
        }
        else if(sospecha>=25 && sospecha<=50){
            //questionMark->setScale({1.5,1.5,1.5});
            //questionMark->cambiarColor({0,255,255,0});
        }
        else if(sospecha>50 && sospecha<75){
            //questionMark->setScale({2,2,2});
            //questionMark->cambiarColor({0,255,153,51});
        }
        else if(sospecha>=75){
            //questionMark->setScale({2.5,2.5,2.5});
            //questionMark->cambiarColor({0,255,0,0});
        }*/

    }
}
void Enemy::escanear(){

    f32 tiempo = GraphicsFacade::getInstance().getTimer()->getTime()/1000.f;
    if (tiempo - scanT < 0.75){
        scanAngle -= 0.5;
    }else if (tiempo - scanT < 1.5){
        scanAngle += 0.5;
    }else{
        scanT = tiempo;
    }
    holoScan->setRotationXYZ(0,angulo,0);
    holoScan->setPosition(posicion);
    activeHoloScan(true);

    if(distanciaPlayer<36 && isEnemySeeing(posicionProta))
    {
        calcularAngulo(posicionProta);
        toProtaPosition = posicionProta - posicion;
        mirandoHacia = toProtaPosition;
        subirSospecha(distanciaPlayer/1000);
        memory->updateVision(EntityMgr->getEntityByID(0));
    }
    setPosition();
}
void Enemy::escuchar(){
    if(static_cast<Player*>(EntityMgr->getEntityByID(0))->getSpeed() == 2){
        calcularAngulo(posicionProta);
        toProtaPosition = posicionProta - posicion;
        mirandoHacia= toProtaPosition;
        subirSospecha(0.02);
        memory->updateSoundSource(EntityMgr->getEntityByID(0));
    }
    setPosition();
}
void Enemy::investigar(){
    andarPath(2,posicionInteres);
    setPosition();
}
void Enemy::volverALaPatrulla(){
    andarPath(1,pRuta->getPunto());
    setPosition();
}
void Enemy::muerto(){
    //posicion = {1000,0,1000};
    //setPosition();
    aniMesh->setRotationXYZ(0.0,0.0,90.0);
    aniMesh->setPosition(Structs::TPosicion{body->GetPosition().x, 0, body->GetPosition().y});
    //EntityMgr->borrarEntity(this);
    //if(this->isGuardia())
        //static_cast<Guardia*>(this)->setModeloVisible(false);
    EntityMgr->borrarEnemigo(this);
    modeloAtaque->setVisible(false);
    questionMark->setVisible(false);
}

void Enemy::matar(){
    vida = 0;
    G_stateMachine->ChangeState(Muerto::Instance());
}
