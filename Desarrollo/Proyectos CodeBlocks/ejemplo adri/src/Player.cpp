#include "Player.h"
#include <Box2D/Box2D.h>



Player::Player()
{
    //ctor
}

Player::~Player()
{
    //dtor
}

void Player::inicializar(scene::ISceneManager* smgr,video::IVideoDriver* driver){
    tam= 10;

    modelo = smgr->addCubeSceneNode(tam);
    modelo->setMaterialFlag(video::EMF_LIGHTING, false);
    //modelo->setMaterialTexture( 0, driver->getTexture("texturas/metal.png") );
   // modelo->setMaterialType( video::EMT_SOLID );
    modelo->setPosition(core::vector3df(0,0,0));

    b2BodyDef bodyDef;
    bodyDef.type= b2_dynamicBody;
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
}

core::vector3df Player::getCuboProta(){
    return cuboProta;
}

void Player::setPosition(core::vector3df vec){
    modelo->setPosition(core::vector3df(vec.X, 0, vec.Z));
}

b2Body* Player::getBody(){
    return body;
}

void Player::setPosicionBody(float ang){
    body->SetTransform(b2Vec2(cuboProta.X, cuboProta.Z), ang);
    std::cout << "cubo X: "<<cuboProta.Z<<" \n";
    std::cout << "cubo Z: "<<cuboProta.Z<<" \n";
    std::cout << "body X: "<<body->GetPosition().x  <<" \n";
    std::cout << "body Z: "<<body->GetPosition().y  <<" \n";
    std::cout << "-------------- \n";
}


void Player::setCuboProta(core::vector3df cb){
    cuboProta = cb;
}

scene::IMeshSceneNode* Player::getModelo(){
    return modelo;
}
