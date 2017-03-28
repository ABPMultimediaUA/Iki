#include "Player.h"
#include "Fachada/GraphicsFacade.h"
#include "PhisicsWorld.h"
#include "Player_Ray.h"
#include "Path/PathFinding.h"
#include "Path/PathPlanner.h"
#include "MapComponent.h"
#include "PhisicsWorld.h"


Player::Player()
{
    rayo = new Player_Ray();
}

Player::~Player()
{
    delete rayo;
}

void Player::inicializar_player(Map* m){

    id=0;
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

    ruido = new Trigger_Ruido();
    ruido->AddCircularRegion(posicion, 90);
    isMoving = false;
}


void Player::moverBody(Structs::TPosicion vec){
    vec.Normalize();
    float movx = vec.X * avMovement;
    float movy = vec.Z * avMovement;

    if (vec == quietoParado){
        isMoving = false;
        speed = 0;
    }else{
        isMoving = true;
        speed = 1;
    }
    if(MyEventReceiver::getInstance().isKeyDown(KEY_KEY_X)){
        speed++;
        movx *= 0.5;
        movy *= 0.5;
    }

    body->SetLinearVelocity(b2Vec2(movx, movy));
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

    deltaTime = PhisicsWorld::getInstance()->getDeltaTime()/1000;
    avMovement = deltaTime * 700;

    TriggerRuido();

    if(rayo->getBalas() > 0){
        if(MyEventReceiver::getInstance().isKeyDown(KEY_KEY_Q)){
            GraphicsFacade::getInstance().cambiarRay(camara);
            rayo->lanzar_rayo(posicion);
        }
    }

    if(MyEventReceiver::getInstance().GetMouseState().RightButtonDown){

        GraphicsFacade::getInstance().cambiarRay(camara);
        moverse = true;
        //listaNodos.clear();
        listaEjes.clear();
        GraphicsFacade::getInstance().interseccionRayPlano(mousePosition);
        //path->crearPath(posicion,mousePosition,listaNodos);
        path2->crearPath(mousePosition,listaEjes);
        path2->SmoothPathEdgesQuick(listaEjes);
        //it=listaNodos.begin();
        it2=listaEjes.begin();

        
    }

    if(GraphicsFacade::getInstance().interseccionRayPlano(mousePosition))

        if(!listaEjes.empty() && it2 != listaEjes.end())
            toNextNodo = (*it2).getDestination() - posicion;
        else
            toNextNodo=quietoParado;

        if(toNextNodo.Length() <= 1) //CUANDO LLEGA AL NODO
        {
            moverBody(quietoParado);
            if(it2 != listaEjes.end()) //SI AUN NO ES EL ULTIMO NODO
                it2++;
        }
        else
        { //CUANDO AUN NO HA LLEGADO A UN NODO
            MoverPlayer((*it2).getDestination(),toNextNodo);
        }
    }
}

void Player::CogerMunicion()
{
    rayo->cogerBalas();
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

     input.p1.Set(desde.X, hasta.Z);	//	Punto	inicial	del	rayo
     input.p2.Set(desde.X, hasta.Z);	//	Punto	final	del	rayo

     ///colision con paredes
    for (int i = 0; i < Mapa->muros.size(); i++) {
        if (Mapa->muros.at(i)->body->GetFixtureList()->RayCast(&output,input,0)){
            return true;
        }
    }

    return false;
}
void Player::MoverPlayer(Structs::TPosicion p1,Structs::TPosicion p2){
    float angulo = atan2f((p1.Z-posicion.Z) ,
                          -(p1.X-posicion.X)) * 180.f / irr::core::PI;
    body->SetTransform(body->GetPosition(), angulo);
    modelo->setRotation(body->GetAngle());
    moverBody(p2);
    posicion = {body->GetPosition().x, 0, body->GetPosition().y};
    modelo->setPosition(posicion);

}


