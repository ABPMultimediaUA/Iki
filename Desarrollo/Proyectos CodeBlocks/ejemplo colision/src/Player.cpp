#include "Player.h"
#include <Box2D/Box2D.h>
#include <iostream>


Player::Player()
{
    //ctor
}

Player::~Player()
{
    //dtor
}

void Player::inicializar(scene::ISceneManager* smgr,video::IVideoDriver* driver){
    tam= 4;

    modelo = smgr->addCubeSceneNode(tam);
    modelo->setMaterialFlag(video::EMF_LIGHTING, false);
    modelo->setMaterialTexture( 0, driver->getTexture("texturas/metal.png") );
    modelo->setMaterialType( video::EMT_SOLID );
    modelo->setPosition(core::vector3df(0,0,0));

    b2BodyDef bodyDef;
    bodyDef.type= b2_kinematicBody;
    bodyDef.position.Set(0, 0);
    iworld= World::Instance();
    body= iworld->getWorld()->CreateBody(&bodyDef);

    b2PolygonShape bodyShape;
    bodyShape.SetAsBox(tam/2, tam/2);
    body->CreateFixture(&bodyShape, 1.0f);

    cuboProta = modelo->getPosition();

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &bodyShape;
    fixtureDef.friction = 10.5f;
    fixtureDef.restitution  = 0.9f;
    fixtureDef.density  = 10.f;
    body->CreateFixture(&fixtureDef);
//    body.postion.Set
}

core::vector3df Player::getCuboProta(){
    return cuboProta;
}

void Player::setCuboProta(core::vector3df cb){
    cuboProta = cb;
}

void Player::setPosicionModelo(b2Vec2 v){
    modelo->setPosition(core::vector3df(v.x, 0, v.y));
}

scene::IMeshSceneNode* Player::getModelo(){
    return modelo;
}

b2Body* Player::getBody(){
    return body;
}

void Player::setPosicionBody(core::vector3df vec, float ang){
    body->SetTransform(b2Vec2(vec.X, vec.Z), ang);
    std::cout << "cubo X: "<<cuboProta.X<<" \n";
    std::cout << "cubo Z: "<<cuboProta.Z<<" \n";
    std::cout << "body X: "<<body->GetPosition().x  <<" \n";
    std::cout << "body Z: "<<body->GetPosition().y  <<" \n";
    std::cout << "-------------- \n";
}

void Player::moverBody(core::vector3df vec){
    if(vec.X != body->GetPosition().x){
       body->ApplyForce( b2Vec2(force,0), body->GetWorldCenter() );
    }
    if(vec.Y != body->GetPosition().y){
        //body->SetLinearVelocity(b2Vec2(0.0, 15.0));
    }
}
