#include "Player.h"
#include "Fachada/GraphicsFacade.h"
#include "PhisicsWorld.h"
#include "Enemies/Path/PathFinding.h"
#include "Enemies/Path/PathPlanner.h"
#include "MapComponent.h"
#include "PhisicsWorld.h"
#include "Muerto.h"
#include "GUI/HUD.h"


Player::Player()
{
    rayo = new Player_Ray();
    vida = 5;
}

Player::~Player()
{
    delete rayo;
}

void Player::inicializar_player(Map* m){

    velocidad = 0.75;
    id = 0;
    vida = 5;
    EntityMgr->registrarEntity(this);

    Mapa=m;
    grafo = Mapa->getGrafo();
    //path = new PathFinding(grafo,this);
    path2 = new PathPlanner(grafo,this);

    Structs::TPosicion posicionInicial (170,0,50);
    Structs::TColor color = {0,0,0,0};
    modelo = GraphicsFacade::getInstance().createCubeSceneNode(2, posicionInicial);
    modelo->cambiarColor(color);
    posicion = modelo->getPosition();

    radio = 1.0;

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(170, 50);
    body = PhisicsWorld::getInstance()->getWorld()->CreateBody(&bodyDef);

    b2PolygonShape bodyShape;
    bodyShape.SetAsBox(1,1);
    body->CreateFixture(&bodyShape, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &bodyShape;
    fixtureDef.density  = 10.f;
    fixtureDef.friction = 1.f;
    fixtureDef.restitution  = -100.f;
    body->CreateFixture(&fixtureDef);
    //Para los ray!
    input.maxFraction	=	1.0f;
    input2.maxFraction  =   1.0f;


    ruido = new Trigger_Ruido();
    ruido->AddCircularRegion(posicion, 90);
    isMoving = false;
}


void Player::moverBody(Structs::TPosicion vec){
    vec.Normalize();
    float movx = vec.X * avMovement * velocidad;
    float movy = vec.Z * avMovement * velocidad;

    if (vec == quietoParado){
        isMoving = false;
        speed = 0;
    }else{
        isMoving = true;
        speed = 1;
    }
    if(MyEventReceiver::getInstance().isKeyDown(KEY_LSHIFT)){
        speed++;
        velocidad = 0.5;
        HUD::getInstance()->sigiloUsed();
    }
    else
        HUD::getInstance()->sigiloNotUsed();
    if(velocidad > 0.75)
        comprobarVelocidad();

    body->SetLinearVelocity(b2Vec2(movx, movy));
}

void Player::comprobarVelocidad(){
    if(GraphicsFacade::getInstance().getTimer()->getTime()/1000.f - tiempo_con_mas_speed > 2){
        velocidad = 0.75;
        tiempo_con_mas_speed = GraphicsFacade::getInstance().getTimer()->getTime()/1000.f;
    }
}


bool Player::getMoving(){
    return isMoving;
}

void Player::TriggerRuido(){
    if (isMoving){
        if (!ruido->isActive()){
            //std::cout << "creamos el triggersito" << std::endl;
            ruido->AddCircularRegion(this->posicion, 20);
            ruido->activar();
        }
    }else{
        if (ruido->isActive()){
            //std::cout << "borramos el triggersito" << std::endl;
            ruido->desactivar();
        }
    }
}

void Player::update(Camera* camara){

    deltaTime = PhisicsWorld::getInstance()->getDeltaTime()/1000.f;
    avMovement = deltaTime * 700;

    rayo->borrar_rayo();

    if(rayo->getBalas() > 0 && GraphicsFacade::getInstance().getTimer()->getTime()/1000.f - rayo->getVidaRayo() > 1.5){
        HUD::getInstance()->rayoNotUsed();
    }
    if(MyEventReceiver::getInstance().isKeyDown(KEY_KEY_W)){
        if(rayo->getBalas() > 0){
            if(GraphicsFacade::getInstance().getTimer()->getTime()/1000.f - rayo->getVidaRayo() > 1.5){
                HUD::getInstance()->rayoUsed();
                GraphicsFacade::getInstance().cambiarRay(camara);
                rayo->lanzar_rayo(posicion);
                SoundMgr->playSonido("Player/disparoprota");
            }
        }
        else
            HUD::getInstance()->activateNotMunicion();
    }
    TriggerRuido();

    if(MyEventReceiver::getInstance().GetMouseState().RightButtonDown){

        GraphicsFacade::getInstance().cambiarRay(camara);
        //listaNodos.clear();
        listaEjes.clear();
        GraphicsFacade::getInstance().interseccionRayPlano(mousePosition);
        calcularMirarHacia(mousePosition);
        //path->crearPath(posicion,mousePosition,listaNodos);
        path2->crearPath(mousePosition,listaEjes);
        path2->SmoothPathEdgesQuick(listaEjes);
        //it=listaNodos.begin();
        it2=listaEjes.begin();

    }

    if(MyEventReceiver::getInstance().isKeyDown(KEY_KEY_Q)){
        std::vector<Enemy*> enemies = EntityManager::Instance()->getEnemigos();
        for(size_t i = 0; i < enemies.size(); i++){
            if(enemies[i]->getPosition().Distance(this->getPosition()) < 8.f){
                if(imSeeingThisEnemy(enemies[i])){
                    if(enemies[i]->getAngulo() - 30 < angulo + 30 && enemies[i]->getAngulo() + 30 > angulo - 30){
                        SoundMgr->playSonido("Player/metal1");
                        enemies[i]->GetFSM()->ChangeState(Muerto::Instance());
                    }
                    else{
                        enemies[i]->quitarVida();
                    }
                    //std::cout<<"Vida: "<<enemies[i]->getVida()<<std::endl;
                }
            }
        }
    }
    if(!listaEjes.empty() && it2 != listaEjes.end())
        toNextNodo = (*it2).getDestination() - posicion;
    else
        toNextNodo=quietoParado;

    if(toNextNodo.Length() <= 1) //CUANDO LLEGA AL NODO
    {
        moverBody(quietoParado);
        if(!listaEjes.empty() && it2 != listaEjes.end()) //SI AUN NO ES EL ULTIMO NODO
            it2++;
    }
    else
    { //CUANDO AUN NO HA LLEGADO A UN NODO
        MoverPlayer((*it2).getDestination(),toNextNodo);
    }

}

void Player::CogerMunicion()
{
    rayo->cogerBalas();
    HUD::getInstance()->activateMunicion();
}
bool Player::isPathObstructured(Structs::TPosicion destino){
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
bool Player::canWalkBetween(Structs::TPosicion desde, Structs::TPosicion hasta){

     input2.p1.Set(desde.X, desde.Z);	//	Punto	inicial	del	rayo
     input2.p2.Set(hasta.X, hasta.Z);	//	Punto	final	del	rayo

     ///colision con paredes
    for (int i = 0; i < Mapa->muros.size(); i++) {
        if (Mapa->muros.at(i)->body->GetFixtureList()->RayCast(&output2,input2,0)){
            return false;
        }
    }

    return true;
}
void Player::MoverPlayer(Structs::TPosicion p1,Structs::TPosicion p2){
    angulo = atan2f((p1.Z-posicion.Z) ,
                          -(p1.X-posicion.X)) * 180.f / irr::core::PI;
    body->SetTransform(body->GetPosition(), angulo);
    modelo->setRotation(body->GetAngle());
    moverBody(p2);
    posicion = {body->GetPosition().x, 0, body->GetPosition().y};
    modelo->setPosition(posicion);

}

bool Player::imSeeingThisEnemy(Enemy* enemy){

    Structs::TPosicion p;
    if(p.isSecondInFOVOfFirst(posicion,mirarHacia,enemy->getPosition(),90*PI/180) && !isPathObstructured(enemy->getPosition()))
        return true;
    else
        return false;
}

void Player::calcularMirarHacia(Structs::TPosicion mousePos){

    mirarHacia = mousePos - getPosition();
}

void Player::CogerLlave(){
    llaves++;
    HUD::getInstance()->activateTarjeta();
}

void Player::UsarLlave(){
    llaves--;
    HUD::getInstance()->desactivateTarjeta();
}

void Player::NecesitoLlave(){
    HUD::getInstance()->activateNotTarjeta();
}

void Player::subirVelocidad(){
    velocidad *= 2;
    tiempo_con_mas_speed = GraphicsFacade::getInstance().getTimer()->getTime()/1000.f;
    HUD::getInstance()->activateAceite();
}
