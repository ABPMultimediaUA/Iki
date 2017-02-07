#include "Player.h"
#include "GraphicsFacade.h"
#include "PhisicsWorld.h"

Player::Player()
{

}

Player::~Player()
{

}

void Player::inicializar_player(){

    Structs::TPosicion posicionInicial = {0,0,0};
    Structs::TColor color = {0,0,0,0};
    modelo = GraphicsFacade::getInstance().createCubeSceneNode(5, posicionInicial);
    modelo->cambiarColor(color);
    posicion = modelo->getPosition();


    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0, 0);
    body = PhisicsWorld::getInstance().getWorld()->CreateBody(&bodyDef);

    b2PolygonShape bodyShape;
    bodyShape.SetAsBox(5/2, 5/2);
    body->CreateFixture(&bodyShape, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &bodyShape;
    fixtureDef.friction = 100.f;
    fixtureDef.restitution  = 0.f;
    fixtureDef.density  = 100.f;
    body->CreateFixture(&fixtureDef);

}

void Player::moverBody(Structs::TPosicion vec){
    float movx = vec.X;
    float movy = vec.Z;
    float modulo = sqrt((movx*movx) + (movy*movy));
    if(modulo != 0){
        movx = (movx / modulo) * 10.0f * 0.70;
        movy = (movy / modulo) * 10.0f * 0.70;
    }

    body->SetLinearVelocity(b2Vec2(movx, movy));
}

void Player::update(Camera* camara, Structs::TPosicion mousePosition){

    if(MyEventReceiver::getInstance().GetMouseState().RightButtonDown)
        {
            //stop= false;

            GraphicsFacade::getInstance().cambiarRay(camara);
            float angulo = atan2f((mousePosition.Z-modelo->getNode()->getPosition().Z) ,
                                  -(mousePosition.X-modelo->getNode()->getPosition().X)) * 180.f / irr::core::PI;

            //ray = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(
            //          receiver.GetMouseState().Position, camera);
            //float angulo = atan2f((mousePosition.Z-prota->getModelo()->getPosition().Z) ,
            //                      -(mousePosition.X-prota->getModelo()->getPosition().X)) * 180.f / irr::core::PI;
            body->SetTransform(body->GetPosition(), angulo);
            modelo->setRotation(body->GetAngle());
            //modelo->setRotation(core::vector3df(0,prota->getBody()->GetAngle(),0));
            //prota->getEsfera()->setRotation(core::vector3df(0,prota->getBody()->GetAngle(),0));
        }

        if(GraphicsFacade::getInstance().interseccionRayPlano(mousePosition))
        {
            std::cout<<"MousePosition holi: "<<mousePosition.X<<std::endl;
            toMousePosition.X = mousePosition.X - posicion.X;
            toMousePosition.Y = mousePosition.Y - posicion.Y;
            toMousePosition.Z = mousePosition.Z - posicion.Z;
            std::cout<<"toMousePosition holi: "<<toMousePosition.X<<std::endl;

            if(GraphicsFacade::getInstance().calcularDistancia(toMousePosition) <= 1)
            {
                toMousePosition = {0,0,0};
                moverBody(toMousePosition);
                /*if(pasosP==true || pasos2P==true)
                {
                    s1->stop();
                    pasosP = false;
                    pasos2P = false;
                }*/

                //stop= true;
            }
            else
            {
                moverBody(toMousePosition);
                /*if(pasosP==false && !receiver.isKeyDown(KEY_LSHIFT))
                {
                    if(engine->isCurrentlyPlaying(pasos2))
                        s1->stop();
                    s1 = engine->play3D(pasos1,posicion,true,false,true);
                    pasosP = true;
                    pasos2P = false;
                }
                else if (pasos2P==false && receiver.isKeyDown(KEY_LSHIFT))
                {
                    if(engine->isCurrentlyPlaying(pasos1))
                        s1->stop();
                    s1 = engine->play3D(pasos2,posicion,true,false,true);
                    pasos2P = true;
                    pasosP = false;

                }*/
                //stop= true;
            }
        }
        posicion = {body->GetPosition().x, 0, body->GetPosition().y};
        modelo->setPosition(posicion);
}
