#include "Player.h"
#include "Fachada/GraphicsFacade.h"
#include "PhisicsWorld.h"
#include "Player_Ray.h"
#include "Path/PathFinding.h"
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

    id=nextID;
    nextID++;

    Mapa=m;
    grafo = Mapa->getGrafo();
    path = new PathFinding(grafo,this);

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
    bodyShape.SetAsBox(2/2, 2/2);
    body->CreateFixture(&bodyShape, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &bodyShape;
    fixtureDef.friction = 100.f;
    fixtureDef.restitution  = 0.f;
    fixtureDef.density  = 100.f;
    body->CreateFixture(&fixtureDef);
    //Para los ray!
    input.maxFraction	=	1.0f;

}

void Player::moverBody(Structs::TPosicion vec){
    vec.Normalize();
    float movx = vec.X * avMovement;
    float movy = vec.Z * avMovement;
    body->SetLinearVelocity(b2Vec2(movx, movy));
}

bool Player::isMoving(){
    return false;
}

void Player::update(Camera* camara){

    deltaTime = PhisicsWorld::getInstance()->getDeltaTime()/1000;
    avMovement = deltaTime * 700;

    if(rayo->getBalas() > 0){
        if(MyEventReceiver::getInstance().isKeyDown(KEY_KEY_Q)){
            GraphicsFacade::getInstance().cambiarRay(camara);
            rayo->lanzar_rayo(posicion);
        }
    }

    if(MyEventReceiver::getInstance().GetMouseState().RightButtonDown){

        GraphicsFacade::getInstance().cambiarRay(camara);
        listaNodos.clear();
        GraphicsFacade::getInstance().interseccionRayPlano(mousePosition);
        path->crearPath(posicion,mousePosition,listaNodos);
        it=listaNodos.begin();
    }
   /* if(GraphicsFacade::getInstance().interseccionRayPlano(mousePosition))
    {
        toMousePosition.X = mousePosition.X - posicion.X;
        toMousePosition.Y = mousePosition.Y - posicion.Y;
        toMousePosition.Z = mousePosition.Z - posicion.Z;

        if(GraphicsFacade::getInstance().calcularDistancia(toMousePosition) <= 1)
        {
            toMousePosition = {0,0,0};
            moverBody(toMousePosition);
        }
        else
        {
            moverBody(toMousePosition);

            posicion = {body->GetPosition().x, 0, body->GetPosition().y};
            modelo->setPosition(posicion);

            float angulo = atan2f((mousePosition.Z-modelo->getNode()->getPosition().Z) ,
                              -(mousePosition.X-modelo->getNode()->getPosition().X)) * 180.f / irr::core::PI;
            body->SetTransform(body->GetPosition(), angulo);
            modelo->setRotation(body->GetAngle());
        }
    }*/
    if(GraphicsFacade::getInstance().interseccionRayPlano(mousePosition))
    {
        if(!listaNodos.empty() && it != listaNodos.end())
            toNextNodo = grafo->getNode(*it).posicion - posicion;
        else
            toNextNodo=quietoParado;

            toMousePosition = mousePosition - posicion;

        if(toNextNodo.Length() <= 1) //CUANDO LLEGA AL NODO
        {
            moverBody(quietoParado);
            if(it != listaNodos.end()) //SI AUN NO ES EL ULTIMO NODO
                it++;
            else if(it == listaNodos.end()){ //SI ES EL ULTIMO NODO
                if(toMousePosition.Length() <= 1) //CUANDO LLEGA AL DESTINO
                {
                    moverBody(quietoParado);
                }
                else{ //CUANDO AUN NO HA LLEGADO AL DESTINO
                    MoverPlayer(mousePosition,toMousePosition);
                }
            }
        }
        else
        { //CUANDO AUN NO HA LLEGADO A UN NODO
            if(!listaNodos.empty() && it != listaNodos.end()){
                MoverPlayer(grafo->getNode(*it).posicion,toNextNodo);
            }
            /*else if(listaNodos.empty()){ //CUANDO NO HAY NODOS POR RECORRER
                     if(toMousePosition.Length() <= 1){ //CUANDO LLEGA AL DESTINO
                        moverBody(quietoParado);
                    }
                    else{ //CUANDO AUN NO HA LLEGADO AL DESTINO
                        moverBody(toMousePosition);
                        posicion = {body->GetPosition().x, 0, body->GetPosition().y};
                        modelo->setPosition(posicion);
                    }
            }*/
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
void Player::MoverPlayer(Structs::TPosicion p1,Structs::TPosicion p2){
    float angulo = atan2f((p1.Z-modelo->getNode()->getPosition().Z) ,
                          -(p1.X-modelo->getNode()->getPosition().X)) * 180.f / irr::core::PI;
    body->SetTransform(body->GetPosition(), angulo);
    modelo->setRotation(body->GetAngle());
    moverBody(p2);
    posicion = {body->GetPosition().x, 0, body->GetPosition().y};
    modelo->setPosition(posicion);
}
